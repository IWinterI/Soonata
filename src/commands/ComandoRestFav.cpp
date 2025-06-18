#include "../include/commands/ComandoRestFav.h"

ComandoRestFav::ComandoRestFav(GestionF &srv) : servicio(srv) {}

std::string ComandoRestFav::nombre() const
{
    return "Restaurar favoritos eliminados.";
}

void ComandoRestFav::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoRestFav::ejecutar()
{
    clearScreen();
    Encabezado();

    auto eliminados = servicio.obtenerEliminados();

    if (!servicio.restaurarFavorito())
    {
        std::cout << std::string(50, '=') << std::endl;

        if (!eliminados.empty())
        {
            std::cout << "Error desconocido." << std::endl;
            std::cout << std::string(50, '=') << std::endl;
        }

        std::cout << "Error: no hay favoritos elimanos." << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        pausarConsola();
        return;
    }

    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "============= Favoritos restaurados =============" << std::endl;
    for (auto var : eliminados)
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nombre: " << var.getNombre() << std::endl;
        std::cout << "Url: " << var.getUrl() << std::endl;
        std::cout << "Carpeta: " << var.getCarpeta() << std::endl;
    }
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    pausarConsola();
}