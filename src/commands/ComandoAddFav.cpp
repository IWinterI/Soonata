#include "../include/commands/ComandoAddFav.h"

ComandoAddFav::ComandoAddFav(GestionF &srv) : servicio(srv) {}

std::string ComandoAddFav::nombre() const
{
    return "Agregar un favorito.";
}

void ComandoAddFav::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoAddFav::ejecutar()
{
    std::string url, nombre, carpeta;

    do
    {
        clearScreen();
        Encabezado();

        std::cout << std::string(50, '=') << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Ingrese una URL: ";
        std::getline(std::cin, url);

        if (Historial::url_valida(url))
        {
            break;
        }

        std::cout << std::string(50, '-') << std::endl;
        std::cout << "URL inválida: " << url << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        pausarConsola();
    } while (true);

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Ingrese un nombre: ";
    std::getline(std::cin, nombre);

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Ingrese carpeta: ";
    std::getline(std::cin, carpeta);
    std::cout << std::string(50, '-') << std::endl;

    if (servicio.agregarFavorito(url, nombre, carpeta))
    {
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "Exito: Se agrego '" << nombre << "' a favoritos" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    }
    else
    {
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "Error: El favorito ya existe" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    }

    std::cout << std::string(50, '=') << std::endl;
    pausarConsola();
}