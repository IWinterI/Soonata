#include "../include/commands/ComandoNavegar.h"

ComandoNavegar::ComandoNavegar(Historial &srv, Navegador &nav) : servicio(srv), navegador(nav) {}

std::string ComandoNavegar::nombre() const
{
    return "Navegar a una Url";
}

void ComandoNavegar::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoNavegar::ejecutar()
{
    std::string url;

    while (true)
    {
        clearScreen();
        Encabezado();
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Por favor ingrece una url: ";
        std::cin >> url;
        if (servicio.visitar(url))
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "Navegando a: " << url << std::endl;
            std::cout << "Se ha agregado la url al historial" << std::endl;
            std::cout << std::string(50, '=') << std::endl;

            if (servicio.get_navegacion())
            {
                navegador.abrirURLOptimo(url);
            }

            pausarConsola();
            break;
        }
        else
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Error: Url invalida." << std::endl;
            std::cout << url << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            pausarConsola();
        }
    }
}