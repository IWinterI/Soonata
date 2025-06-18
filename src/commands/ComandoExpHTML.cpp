#include "../include/commands/ComandoExpHTML.h"

ComandoExpHTML::ComandoExpHTML(ExpHTML &srv, GestionF &arch) : servicio(srv), archivo(arch) {}

std::string ComandoExpHTML::nombre() const
{
    return "Exportar favoritos a HTML.";
}

void ComandoExpHTML::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoExpHTML::ejecutar()
{
    clearScreen();
    Encabezado();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Archivo generado." << std::endl;
    servicio.generarArchivoHTML("Favoritos.html", archivo.obtenerTodos());
    std::cout << std::string(50, '=') << std::endl;
    pausarConsola();
}