#include "../include/commands/ComandoAntHist.h"

ComandoAntHist::ComandoAntHist(Historial &srv, Navegador &nav) : servicio(srv), navegador(nav) {}

std::string ComandoAntHist::nombre() const
{
    return "Navegar a la url anterior.";
}

void ComandoAntHist::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoAntHist::ejecutar()
{
    clearScreen();
    Encabezado();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Url anterior: " << servicio.get_actual() << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    servicio.anterior();
    std::cout << "Url actual: " << servicio.get_actual() << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    if (servicio.get_navegacion())
    {
        navegador.abrirURLOptimo(servicio.get_actual());
    }

    pausarConsola();
}