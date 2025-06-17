#include "ExpHTML.h"
#include <fstream>
#include <algorithm>



ExpHTML::ExpHTML()
{
    //ctor
}

ExpHTML::~ExpHTML()
{
    //dtor
}

void ExpHTML::agregarPagina(const std::string& carpeta,
                               const std::string& nombrePagina,
                               const std::string& url) {
    // Buscar si la carpeta ya existe
    auto it = std::find_if(datos.begin(), datos.end(),
        [&](const auto& par) { return par.first == carpeta; });

    if (it != datos.end()) {
        // Carpeta existe, agregar página
        it->second.push_back({nombrePagina, url});
    } else {
        // Crear nueva carpeta
        datos.push_back({carpeta, {{nombrePagina, url}}});
    }
}

void ExpHTML::generarArchivoHTML(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << generarHTML();
    }
}

std::string ExpHTML::generarHTML() {
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


    for (const auto& [carpeta, paginas] : datos) {
        html += "<div class='folder'>";
        html += "<div class='folder-header'>" + escapeHTML(carpeta) + "</div>";
        html += "<div class='pages'>";

        if (paginas.empty()) {
            html += "<div class='empty'>Esta carpeta está vacia</div>";
        } else {
            for (const auto& pagina : paginas) {
                html += "<div class='page-item'>";
                html += "<a href='" + escapeHTML(pagina.url) + "' class='page-link'>" +
                        escapeHTML(pagina.nombre) + "</a>";
                html += "<span class='page-url'>" + escapeHTML(pagina.url) + "</span>";
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

std::string ExpHTML::escapeHTML(const std::string& texto) {
    std::string result;
    for (char c : texto) {
        switch (c) {
            case '&':  result += "&amp;";  break;
            case '<':  result += "&lt;";   break;
            case '>':  result += "&gt;";   break;
            case '"':  result += "&quot;"; break;
            case '\'': result += "&#39;";  break;
            default:   result += c;        break;
        }
    }
    return result;
}
