// UI
#include "include/InterfazConsola.h"

// Servicios
#include "include/Historial.h"
#include "include/GestionF.h"
#include "include/ExpHTML.h"

// Comandos
#include "include/commands/ComandoNavegar.h"
#include "include/commands/ComandoImpHist.h"
#include "include/commands/ComandoAntHist.h"
#include "include/commands/ComandoSigHist.h"
#include "include/commands/ComandoAddFav.h"
#include "include/commands/ComandoImpFav.h"
#include "include/commands/ComandoElimFav.h"
#include "include/commands/ComandoSearchFav.h"
#include "include/commands/ComandoRestFav.h"
#include "include/commands/ComandoAsigCarp.h"
#include "include/commands/ComandoExpHTML.h"

void pausarConsola()
{

    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Espera a que se presione Enter
}

int main()
{
    // Configurar interfaz
    InterfazConsola interfaz;

    // Crear servicios
    Historial historial;
    GestionF gestionf;
    ExpHTML html;

    // Cargar lista de favoritos
    std::vector<Favoritos> Favoritos;
    html.leerArchivoHTML("Favoritos.html", Favoritos);

    for (auto var : Favoritos)
    {
        std::cout << "Nombre: " << var.getNombre() << std::endl;
        std::cout << "URL: " << var.getUrl() << std::endl;
        std::cout << "Carpeta: " << var.getCarpeta() << std::endl;
    }

    pausarConsola();

    for (auto var : Favoritos)
    {
        gestionf.agregarFavorito(var.getUrl(), var.getNombre(), var.getCarpeta());
    }

    // Registrar comandos con sus dependencias
    interfaz.registrarComando(1, std::make_unique<ComandoNavegar>(historial));
    interfaz.registrarComando(2, std::make_unique<ComandoImpHist>(historial));
    interfaz.registrarComando(3, std::make_unique<ComandoAntHist>(historial));
    interfaz.registrarComando(4, std::make_unique<ComandoSigHist>(historial));
    interfaz.registrarComando(5, std::make_unique<ComandoAddFav>(gestionf));
    interfaz.registrarComando(6, std::make_unique<ComandoElimFav>(gestionf));
    interfaz.registrarComando(7, std::make_unique<ComandoImpFav>(gestionf));
    interfaz.registrarComando(8, std::make_unique<ComandoSearchFav>(gestionf));
    interfaz.registrarComando(9, std::make_unique<ComandoAsigCarp>(gestionf));
    interfaz.registrarComando(10, std::make_unique<ComandoRestFav>(gestionf));
    interfaz.registrarComando(11, std::make_unique<ComandoExpHTML>(html, gestionf));

    // Ejecutar
    interfaz.ejecutar();

    return 0;
}
