#include "../include/commands/ComandoSigHist.h"

ComandoSigHist::ComandoSigHist(Historial &srv, Navegador &nav) : servicio(srv), navegador(nav) {}

std::string ComandoSigHist::nombre() const
{
    return "Navegar a la siguiente url.";
}

void ComandoSigHist::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoSigHist::ejecutar()
{
    clearScreen();
    Encabezado();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Url anterior: " << servicio.get_actual() << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    servicio.siguiente();
    std::cout << "Url actual: " << servicio.get_actual() << std::endl;
    if (servicio.get_navegacion())
    {
        navegador.abrirURLOptimo(servicio.get_actual());
    }

    std::cout << std::string(50, '=') << std::endl;
    pausarConsola();
}