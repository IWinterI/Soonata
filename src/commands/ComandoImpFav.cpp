#include "../include/commands/ComandoImpFav.h"

ComandoImpFav::ComandoImpFav(GestionF &srv) : servicio(srv) {}

std::string ComandoImpFav::nombre() const
{
    return "Imprimir lista de favoritos.";
}

void ComandoImpFav::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoImpFav::ejecutar()
{
    clearScreen();
    Encabezado();

    std::cout << std::string(50, '=') << std::endl;
    servicio.mostrarFavoritos();
    std::cout << std::string(50, '=') << std::endl;

    pausarConsola();
}