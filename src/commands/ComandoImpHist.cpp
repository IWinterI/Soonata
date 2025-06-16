#include "../include/commands/ComandoImpHist.h"

ComandoImpHist::ComandoImpHist(Historial &srv) : servicio(srv) {}

std::string ComandoImpHist::nombre() const
{
    return "Imprimir historial de navegacion.";
}

void ComandoImpHist::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoImpHist::ejecutar()
{
    clearScreen();
    Encabezado();
    std::cout << std::string(50, '-') << std::endl;
    servicio.imprimir_historial();
    std::cout << std::string(50, '-') << std::endl;
    pausarConsola();
}