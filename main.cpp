// Librerias
#include <iostream>
#include <limits>

// Encabezados
#include "include/InterfazConsola.h"

int main()
{
    int opcion = 0;
    InterfazConsola menu;

    while (true)
    {
        menu.MostrarEncabezado();
        menu.MostrarMenu();

        try
        {
            // Intentamos leer directamente un entero
            if (!(std::cin >> opcion))
            {
                // Si falla la lectura
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << std::string(50, '=') << std::endl;
                throw std::runtime_error("Entrada no válida. No es un número entero.");
                std::cout << std::string(50, '=') << std::endl;
            }

            // Verificamos si hay caracteres adicionales después del número
            char c;
            if (std::cin.get(c))
            {
                std::cin.putback(c); // Devolvemos el carácter si es un espacio en blanco
                if (c != '\n' && c != ' ')
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << std::string(50, '=') << std::endl;
                    throw std::runtime_error("Caracteres adicionales después del número.");
                    std::cout << std::string(50, '=') << std::endl;
                }
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cout << std::string(50, '=') << std::endl;
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "Por favor ingrese un número entero válido." << std::endl;
            std::cout << std::string(50, '=') << std::endl;
        }

        if (!menu.ProcesarOpcion(opcion))
        {
            break;
        }
    }

    return 0;
}
