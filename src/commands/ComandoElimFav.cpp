#include "../include/commands/ComandoElimFav.h"

ComandoElimFav::ComandoElimFav(GestionF &srv) : servicio(srv) {}

std::string ComandoElimFav::nombre() const
{
    return "Eliminar un favorito.";
}

void ComandoElimFav::Encabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(nombre());
    std::cout << std::string(50, '=') << std::endl;
}

void ComandoElimFav::ejecutar()
{
    std::string criterio;
    bool eliminado = false;

    do
    {
        clearScreen();
        Encabezado();

        if (!servicio.estavacio())
        {
            std::cout << std::string(50, '=') << std::endl;
            servicio.mostrarFavoritos();
            std::cout << std::string(50, '=') << std::endl;

            std::cout << "Ingrese el nombre o URL del favorito: ";
            std::getline(std::cin, criterio);

            eliminado = servicio.eliminarFavorito(criterio);

            if (eliminado)
            {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Exito se elimino: " << criterio << std::endl;
                std::cout << std::string(50, '-') << std::endl;
                std::cout << std::string(50, '=') << std::endl;
                pausarConsola();
                break;

                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Error: No se encontró '" << criterio << "'" << std::endl;
                std::cout << std::string(50, '-') << std::endl;

                std::cout << std::string(50, '=') << std::endl;
                std::cout << "Desea intentar con otro criterio? (s/n): ";
                char opcion;
                std::cin >> opcion;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << std::string(50, '=') << std::endl;

                if (tolower(opcion) != 's')
                {
                    break;
                }
            }
        }
        else
        {
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "No hay favoritos añadidos." << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            pausarConsola();
            break;
        }
    } while (true);
}