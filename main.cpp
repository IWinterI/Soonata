// UI
#include "include/InterfazConsola.h"

// Servicios
#include "include/Historial.h"

// Comandos
#include "include/commands/ComandoNavegar.h"
#include "include/commands/ComandoImpHist.h"
#include "include/commands/ComandoAntHist.h"
#include "include/commands/ComandoSigHist.h"

#include "ExpHTML.h"

int main()
{
    // Configurar interfaz
    InterfazConsola interfaz;
    ExpHTML html;
    // Agregar páginas a diferentes carpetas
    html.agregarPagina("Redes Sociales", "Facebook", "https://facebook.com");
    html.agregarPagina("Redes Sociales", "Twitter", "https://twitter.com");
    html.agregarPagina("Redes Sociales", "Instagram", "https://instagram.com");

    html.agregarPagina("Buscadores", "Google", "https://google.com");
    html.agregarPagina("Buscadores", "Bing", "https://bing.com");

    html.agregarPagina("Noticias", "BBC", "https://bbc.com");
    html.agregarPagina("Noticias", "CNN", "https://cnn.com");



    // Generar el archivo HTML final
    html.generarArchivoHTML("explorador.html");
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
