// UI
#include "include/InterfazConsola.h"

// Servicios
#include "include/Historial.h"

// Comandos
#include "include/commands/ComandoNavegar.h"
#include "include/commands/ComandoImpHist.h"
#include "include/commands/ComandoAntHist.h"
#include "include/commands/ComandoSigHist.h"

int main()
{
    // Configurar interfaz
    InterfazConsola interfaz;

    // Crear servicios
    Historial historial;

    // Registrar comandos con sus dependencias
    interfaz.registrarComando(1, std::make_unique<ComandoNavegar>(historial));
    interfaz.registrarComando(2, std::make_unique<ComandoImpHist>(historial));
    interfaz.registrarComando(3, std::make_unique<ComandoAntHist>(historial));
    interfaz.registrarComando(4, std::make_unique<ComandoSigHist>(historial));

    // Ejecutar
    interfaz.ejecutar();

    return 0;
}
