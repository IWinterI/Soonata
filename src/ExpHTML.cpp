#include "../include/ExpHTML.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>

ExpHTML::ExpHTML()
{
    // ctor
}

ExpHTML::~ExpHTML()
{
    // dtor
}

void ExpHTML::generarArchivoHTML(const std::string &nombreArchivo,
                                 const std::vector<Favoritos> &favoritos)
{
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        archivo << generarHTML(favoritos);
    }
}

std::string ExpHTML::generarHTML(const std::vector<Favoritos> &favoritos)
{
    // Agrupar favoritos por carpeta
    std::map<std::string, std::vector<Favoritos>> grupos;
    for (const auto &fav : favoritos)
    {
        grupos[fav.getCarpeta()].push_back(fav);
    }

    std::string html = R"(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Carpetas de Favoritos</title>
    <style>
        * {
            box-sizing: border-box;
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        body {
            background-color: #f5f5f5;
            margin: 0;
            padding: 20px;
        }
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: white;
            border-radius: 8px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            overflow: hidden;
        }
        header {
            background: #2c3e50;
            color: white;
            padding: 15px 20px;
        }
        .folders {
            padding: 15px;
        }
        .folder {
            margin-bottom: 15px;
            border: 1px solid #e0e0e0;
            border-radius: 4px;
            overflow: hidden;
        }
        .folder-header {
            background-color: #f1f8ff;
            padding: 10px 15px;
            font-weight: bold;
            cursor: pointer;
            display: flex;
            align-items: center;
        }
        .folder-header::before {
            content: '📁 ';
            margin-right: 8px;
        }
        .pages {
            display: none;
            padding: 10px 15px;
            background-color: #f9f9f9;
        }
        .page-item {
            padding: 8px 0;
            border-bottom: 1px solid #eee;
            display: flex;
            align-items: center;
        }
        .page-item:last-child {
            border-bottom: none;
        }
        .page-item::before {
            content: '📄';
            margin-right: 10px;
            font-size: 1.2em;
        }
        .page-link {
            color: #3498db;
            text-decoration: none;
            flex-grow: 1;
        }
        .page-link:hover {
            text-decoration: underline;
        }
        .page-url {
            color: #95a5a6;
            font-size: 0.85em;
            margin-left: 10px;
        }
        .empty {
            color: #7f8c8d;
            text-align: center;
            padding: 20px;
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <h1>Carpetas de favoritos</h1>
        </header>
        <div class="folders">
)";

    for (const auto &[carpeta, paginas] : grupos)
    {
        html += "<div class='folder'>";
        html += "<div class='folder-header'>" + escapeHTML(carpeta) + "</div>";
        html += "<div class='pages'>";

        if (paginas.empty())
        {
            html += "<div class='empty'>Esta carpeta está vacia</div>";
        }
        else
        {
            for (const auto &pagina : paginas)
            {
                html += "<div class='page-item'>";
                html += "<a href='" + escapeHTML(pagina.getUrl()) + "' class='page-link'>" +
                        escapeHTML(pagina.getNombre()) + "</a>";
                html += "<span class='page-url'>" + escapeHTML(pagina.getUrl()) + "</span>";
                html += "</div>";
            }
        }

        html += "</div></div>";
    }

    // JavaScript para mostrar/ocultar páginas
    html += R"(
        </div>
    </div>
    <script>
        document.querySelectorAll('.folder-header').forEach(header => {
            header.addEventListener('click', () => {
                const pages = header.nextElementSibling;
                pages.style.display = pages.style.display === 'none' ||
                                     pages.style.display === '' ? 'block' : 'none';
            });
        });

        const firstFolder = document.querySelector('.pages');
        if (firstFolder) firstFolder.style.display = 'block';
    </script>
</body>
</html>
)";

    return html;
}

std::string ExpHTML::escapeHTML(const std::string &texto)
{
    std::string result;
    for (char c : texto)
    {
        switch (c)
        {
        case '&':
            result += "&amp;";
            break;
        case '<':
            result += "&lt;";
            break;
        case '>':
            result += "&gt;";
            break;
        case '"':
            result += "&quot;";
            break;
        case '\'':
            result += "&#39;";
            break;
        default:
            result += c;
            break;
        }
    }
    return result;
}

bool ExpHTML::leerArchivoHTML(const std::string &nombreArchivo,
                              std::vector<Favoritos> &favoritos)
{
    favoritos.clear();
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
        return false;

    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string contenido = buffer.str();
    archivo.close();

    size_t pos = 0;
    while ((pos = contenido.find("<div class='folder'>", pos)) != std::string::npos)
    {
        pos += 19; // Longitud de "<div class='folder'>"

        // Extraer nombre de carpeta
        size_t headerStart = contenido.find("<div class='folder-header'>", pos);
        if (headerStart == std::string::npos)
            break;
        headerStart += 27; // Longitud de "<div class='folder-header'>"

        size_t headerEnd = contenido.find("</div>", headerStart);
        if (headerEnd == std::string::npos)
            break;
        std::string carpeta = contenido.substr(headerStart, headerEnd - headerStart);
        carpeta = unescapeHTML(carpeta);

        // Buscar contenedor de páginas
        size_t pagesStart = contenido.find("<div class='pages'>", headerEnd);
        if (pagesStart == std::string::npos)
            break;
        pagesStart += 19; // Longitud de "<div class='pages'>"

        size_t pagesEnd = contenido.find("</div>", pagesStart);
        if (pagesEnd == std::string::npos)
            break;

        // Procesar TODOS los elementos dentro de la carpeta
        size_t itemPos = pagesStart;
        while ((itemPos = contenido.find("<div class='page-item'>", itemPos)) != std::string::npos)
        {
            if (itemPos > pagesEnd)
                break;

            itemPos += 23; // Longitud de "<div class='page-item'>"

            // Extraer URL
            size_t hrefStart = contenido.find("<a href='", itemPos);
            if (hrefStart == std::string::npos || hrefStart > pagesEnd)
                break;
            hrefStart += 9; // Longitud de "<a href='"

            size_t hrefEnd = contenido.find("'", hrefStart);
            if (hrefEnd == std::string::npos || hrefEnd > pagesEnd)
                break;
            std::string url = contenido.substr(hrefStart, hrefEnd - hrefStart);
            url = unescapeHTML(url);

            // Extraer nombre - BUSCAMOS DIRECTAMENTE LA CLASE
            size_t nameStart = contenido.find("class='page-link'>", hrefEnd);
            if (nameStart == std::string::npos || nameStart > pagesEnd)
                break;
            nameStart += 18; // Longitud de "class='page-link'>"

            size_t nameEnd = contenido.find("<", nameStart);
            if (nameEnd == std::string::npos || nameEnd > pagesEnd)
                break;
            std::string nombre = contenido.substr(nameStart, nameEnd - nameStart);
            nombre = unescapeHTML(nombre);

            // Añadir favorito
            favoritos.emplace_back(url, nombre, carpeta);

            // Avanzar al siguiente elemento
            itemPos = nameEnd + 1;
        }
        pos = pagesEnd;
    }
    return true;
}

std::string ExpHTML::unescapeHTML(const std::string &texto)
{
    std::string result;
    for (size_t i = 0; i < texto.size(); ++i)
    {
        if (texto[i] == '&')
        {
            if (texto.substr(i, 5) == "&amp;")
            {
                result += '&';
                i += 4;
            }
            else if (texto.substr(i, 4) == "&lt;")
            {
                result += '<';
                i += 3;
            }
            else if (texto.substr(i, 4) == "&gt;")
            {
                result += '>';
                i += 3;
            }
            else if (texto.substr(i, 6) == "&quot;")
            {
                result += '"';
                i += 5;
            }
            else if (texto.substr(i, 5) == "&#39;")
            {
                result += '\'';
                i += 4;
            }
            else
            {
                result += texto[i];
            }
        }
        else
        {
            result += texto[i];
        }
    }
    return result;
}