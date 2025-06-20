#include "../include/commands/ComandoHabNav.h"

ComandoHabNav::ComandoHabNav(Historial &srv) : servicio(srv) {}

std::string ComandoHabNav::nombre() const
{
    return "Habilitar navegacion web.";
}

void ComandoHabNav::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoHabNav::ejecutar()
{
    clearScreen();
    Encabezado();

    std::cout << std::string(50, '=') << std::endl;
    if (!servicio.get_navegacion())
    {
        servicio.hab_navegacion();

        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Navegacion web habilitada." << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        pausarConsola();
        return;
    }

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Navegacion web ya habilitada." << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    pausarConsola();
}