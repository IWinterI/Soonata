// UI
#include "include/InterfazConsola.h"

// Servicios
#include "include/Historial.h"
#include "include/GestionF.h"

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

int main()
{
    // Configurar interfaz
    InterfazConsola interfaz;

    // Crear servicios
    Historial historial;
    GestionF gestionf;

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

    // Ejecutar
    interfaz.ejecutar();

    return 0;
}
