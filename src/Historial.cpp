#include "../include/Historial.h"

Historial::Historial()
{
    actual = historial.end();
    Navegacion = false;
}

Historial::~Historial()
{
    // dtor
}

bool Historial::url_valida(const std::string &url)
{
    // Patrón regex corregido y mejorado
    const std::regex patron(
        R"(^(https?|ftp):\/\/)"                           // Protocolo
        R"(([a-zA-Z0-9-]+\.)+)"                           // Subdominios
        R"([a-zA-Z]{2,})"                                 // Dominio principal
        R"((:\d+)?)"                                      // Puerto opcional
        R"((\/[a-zA-Z0-9-._~:\/\?#\[\]@!$&'()*+,;%=]*)?)" // Ruta/query/fragmento
        R"($)"                                            // Fin de cadena
    );

    return std::regex_match(url, patron);
}

bool Historial::visitar(const std::string &url)
{
    if (url_valida(url))
    {
        // Borramos el "futuro" si estamos en medio del historial
        if (actual != historial.end())
        {
            auto siguiente = actual;
            ++siguiente;
            historial.erase(siguiente, historial.end());
        }

        // Añadimos la nueva url
        historial.push_back(url);
        actual = --historial.end();

        return true;
    }
    else
    {
        return false;
    }
}

bool Historial::siguiente()
{
    if (!puede_avanzar())
        return false;

    ++actual;
    return true;
}

bool Historial::anterior()
{
    if (!puede_retroceder())
        return false;

    --actual;
    return true;
}

std::string Historial::get_actual() const
{
    return (actual != historial.end()) ? *actual : "(ninguna)";
}

void Historial::imprimir_historial()
{
    if (!historial.empty())
    {
        // Imprimir todas las url
        for (const auto &url : historial)
        {
            std::cout << "- " << url;

            // Marcar la URL actual
            if (actual != historial.end() && url == *actual)
            {
                std::cout << " <-- Actual";
            }
            std::cout << std::endl;
        }

        // Imprimir el url actual
        if (actual != historial.end())
        {
            std::cout << "\nURL actual: " << *actual << std::endl;
        }
        else
        {
            std::cout << "\nURL actual: Ninguna (iterador al final)" << std::endl;
        }
    }
    else
    {
        std::cout << "Historial vacio." << std::endl;
    }
}

bool Historial::puede_retroceder() const
{
    return actual != historial.begin() && !historial.empty();
}

bool Historial::puede_avanzar() const
{
    if (historial.empty())
        return false;
    auto temp = actual;
    return ++temp != historial.end();
}

void Historial::borrar_historial()
{
    historial.clear();
    actual = historial.end();
}

void Historial::hab_navegacion()
{
    Navegacion = true;
}

bool Historial::get_navegacion()
{
    return Navegacion;
}