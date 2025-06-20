#include "../include/ExpJSON.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <iomanip>

void ExpJSON::exportarFavoritos(const std::string &nombreArchivo, const std::vector<Favoritos> &favoritos)
{
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
        return;

    archivo << "[\n";
    for (size_t i = 0; i < favoritos.size(); ++i)
    {
        const auto &fav = favoritos[i];
        archivo << "  {\n";
        archivo << "    \"url\": \"" << escapeJSON(fav.getUrl()) << "\",\n";
        archivo << "    \"nombre\": \"" << escapeJSON(fav.getNombre()) << "\",\n";
        archivo << "    \"carpeta\": \"" << escapeJSON(fav.getCarpeta()) << "\"\n";
        archivo << "  }";

        if (i < favoritos.size() - 1)
        {
            archivo << ",";
        }
        archivo << "\n";
    }
    archivo << "]\n";
}

std::vector<Favoritos> ExpJSON::importarFavoritos(const std::string &nombreArchivo)
{
    std::vector<Favoritos> favoritos;
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
        return favoritos;

    // Leer todo el contenido
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string contenido = buffer.str();
    archivo.close();

    // Analizar JSON manualmente
    size_t pos = 0;
    while ((pos = contenido.find('{', pos)) != std::string::npos)
    {
        std::string url, nombre, carpeta;

        // Buscar URL
        size_t urlStart = contenido.find("\"url\":", pos);
        if (urlStart == std::string::npos)
            break;
        urlStart = contenido.find('\"', urlStart + 6) + 1;
        size_t urlEnd = contenido.find('\"', urlStart);
        if (urlEnd == std::string::npos)
            break;
        url = unescapeJSON(contenido.substr(urlStart, urlEnd - urlStart));

        // Buscar nombre
        size_t nombreStart = contenido.find("\"nombre\":", urlEnd);
        if (nombreStart == std::string::npos)
            break;
        nombreStart = contenido.find('\"', nombreStart + 9) + 1;
        size_t nombreEnd = contenido.find('\"', nombreStart);
        if (nombreEnd == std::string::npos)
            break;
        nombre = unescapeJSON(contenido.substr(nombreStart, nombreEnd - nombreStart));

        // Buscar carpeta
        size_t carpetaStart = contenido.find("\"carpeta\":", nombreEnd);
        if (carpetaStart == std::string::npos)
            break;
        carpetaStart = contenido.find('\"', carpetaStart + 10) + 1;
        size_t carpetaEnd = contenido.find('\"', carpetaStart);
        if (carpetaEnd == std::string::npos)
            break;
        carpeta = unescapeJSON(contenido.substr(carpetaStart, carpetaEnd - carpetaStart));

        // Crear objeto Favoritos
        favoritos.push_back(Favoritos(url, nombre, carpeta));

        // Mover al siguiente objeto
        pos = contenido.find('}', carpetaEnd);
        if (pos == std::string::npos)
            break;
    }

    return favoritos;
}

std::string ExpJSON::escapeJSON(const std::string &texto)
{
    std::string result;
    for (char c : texto)
    {
        switch (c)
        {
        case '\"':
            result += "\\\"";
            break;
        case '\\':
            result += "\\\\";
            break;
        case '\b':
            result += "\\b";
            break;
        case '\f':
            result += "\\f";
            break;
        case '\n':
            result += "\\n";
            break;
        case '\r':
            result += "\\r";
            break;
        case '\t':
            result += "\\t";
            break;
        default:
            if (c >= 0 && c <= 0x1F)
            {
                // Caracteres de control - escapar como Unicode
                char buf[7];
                snprintf(buf, sizeof(buf), "\\u%04X", c);
                result += buf;
            }
            else
            {
                result += c;
            }
            break;
        }
    }
    return result;
}

std::string ExpJSON::unescapeJSON(const std::string &texto)
{
    std::string result;
    for (size_t i = 0; i < texto.size(); ++i)
    {
        if (texto[i] == '\\' && i + 1 < texto.size())
        {
            switch (texto[i + 1])
            {
            case '\"':
                result += '\"';
                i++;
                break;
            case '\\':
                result += '\\';
                i++;
                break;
            case '/':
                result += '/';
                i++;
                break;
            case 'b':
                result += '\b';
                i++;
                break;
            case 'f':
                result += '\f';
                i++;
                break;
            case 'n':
                result += '\n';
                i++;
                break;
            case 'r':
                result += '\r';
                i++;
                break;
            case 't':
                result += '\t';
                i++;
                break;
            case 'u':
                if (i + 5 < texto.size())
                {
                    // Escapado Unicode
                    std::string hexStr = texto.substr(i + 2, 4);
                    try
                    {
                        int unicode = std::stoi(hexStr, nullptr, 16);
                        result += static_cast<char>(unicode);
                        i += 5;
                    }
                    catch (...)
                    {
                        result += "\\u";
                        i++;
                    }
                }
                else
                {
                    result += "\\u";
                    i++;
                }
                break;
            default:
                result += texto[i];
                break;
            }
        }
        else
        {
            result += texto[i];
        }
    }
    return result;
}