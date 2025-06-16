// UI
#include "include/InterfazConsola.h"

// Servicios
#include "include/Historial.h"

// Comandos
#include "include/commands/ComandoNavegar.h"

int main()
{
    // Configurar interfaz
    InterfazConsola interfaz;

    // Crear servicios
    Historial historial;

    // Registrar comandos con sus dependencias
    interfaz.registrarComando(1, std::make_unique<ComandoNavegar>(historial));

    // Ejecutar
    interfaz.ejecutar();

    return 0;
}
