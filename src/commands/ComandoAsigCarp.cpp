#include "../include/commands/ComandoAsigCarp.h"

ComandoAsigCarp::ComandoAsigCarp(GestionF &srv) : servicio(srv) {}

std::string ComandoAsigCarp::nombre() const
{
    return "Asignar favorito a una carpeta.";
}

void ComandoAsigCarp::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoAsigCarp::ejecutar()
{
    clearScreen();
    Encabezado();

    auto carpetas = servicio.obtenerCarpetasExistentes();

    if (!servicio.estavacio())
    {
        std::cout << "============== Carpetas existentes ==============" << std::endl;
        for (const auto &carp : carpetas)
        {
            std::cout << "- " << carp << std::endl;
        }
        std::cout << std::string(50, '-') << std::endl;

        std::string carpeta, criterio;
        std::cout << "Ingrese carpeta (nueva o existente): ";
        std::getline(std::cin, carpeta);
        std::cout << std::string(50, '-') << std::endl;

        std::cout << std::string(50, '=') << std::endl;
        servicio.mostrarFavoritos();
        std::cout << std::string(50, '=') << std::endl;

        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Ingrese nombre/URL del favorito: ";
        std::getline(std::cin, criterio);

        if (servicio.asignarCarpeta(criterio, carpeta))
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Exito favorito actualizado:" << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            servicio.mostrarFavorito(criterio, carpeta);
            std::cout << std::string(50, '-') << std::endl;
        }
        else
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Error: No se encontro '" << criterio << "'" << std::endl;
            std::cout << std::string(50, '-') << std::endl;
        }

        std::cout << std::string(50, '=') << std::endl;
        pausarConsola();
    }
    else
    {
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "Error: no hay favoritos registrados" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        pausarConsola();
    }
}