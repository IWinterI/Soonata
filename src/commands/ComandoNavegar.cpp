#include "../include/commands/ComandoNavegar.h"

ComandoNavegar::ComandoNavegar(Historial &srv) : servicio(srv) {}

std::string ComandoNavegar::obtenerNombre() const
{
    std::string mensaje;
    mensaje += std::string(50, '-') + "\n";
    mensaje += "Ejecutando acción: Navegar a URL\n";
    mensaje += std::string(50, '-') + "\n";
    return mensaje;
}

void ComandoNavegar::ejecutar()
{
    std::string url;

    while (true)
    {
        clearScreen();
        obtenerNombre();
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Por favor ingrece una url: ";
        std::cin >> url;
        if (servicio.visitar(url))
        {
            pausarConsola();
            break;
        }
        else
        {
            std::cout << std::string(50, '=') << std::endl;
            std::cout << url << std::endl;
            std::cout << "Error: Url invalida." << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            pausarConsola();
        }
    }
}