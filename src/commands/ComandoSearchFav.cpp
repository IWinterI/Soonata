#include "../include/commands/ComandoSearchFav.h"

ComandoSearchFav::ComandoSearchFav(GestionF &srv) : servicio(srv) {}

std::string ComandoSearchFav::nombre() const
{
    return "Buscar un favorito.";
}

void ComandoSearchFav::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoSearchFav::imprimir(std::vector<Favoritos> resultados)
{
    for (auto var : resultados)
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nombre: " << var.getNombre() << std::endl;
        std::cout << "Url: " << var.getUrl() << std::endl;
        std::cout << "Carpeta: " << var.getCarpeta() << std::endl;
    }
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoSearchFav::ejecutar()
{
    clearScreen();
    Encabezado();

    std::string criterio;

    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Ingrese el nombre/url/carpeta del favorito que desea buscar: " << std::endl;
    std::getline(std::cin, criterio);
    std::cout << std::string(50, '-') << std::endl;

    auto resultados = servicio.buscarPorNombre(criterio);
    if (!resultados.empty())
    {
        std::cout << "============ Coincidencias por Nombre ===========" << std::endl;
        imprimir(resultados);
    }

    resultados = servicio.buscarPorURL(criterio);
    if (!resultados.empty())
    {
        std::cout << "============= Coincidencias por URL =============" << std::endl;
        imprimir(resultados);
    }

    resultados = servicio.buscarPorCarpeta(criterio);
    if (!resultados.empty())
    {
        std::cout << "=========== Coincidencias por Carpetas ==========" << std::endl;
        imprimir(resultados);
    }

    pausarConsola();
}