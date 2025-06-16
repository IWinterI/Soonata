#include "../include/InterfazConsola.h"

InterfazConsola::InterfazConsola()
{
    // ctor
}

InterfazConsola::~InterfazConsola()
{
    // dtor
}

void InterfazConsola::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void InterfazConsola::printCentered(const std::string &text, int width)
{
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding > 0)
        std::cout << std::string(padding, ' ');
    std::cout << text << std::endl;
}

void InterfazConsola::workinprogrece(int opcion)
{
    clearScreen();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Se ha seleccionado la opcion numero " << opcion << std::endl;
    std::cout << "Funcion aun no implementada" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void InterfazConsola::MostrarEncabezado()
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered("Bienvenido a Soonata");
    printCentered("El navegador numero uno y de mayor confianza");
    std::cout << std::string(50, '=') << std::endl;
}

void InterfazConsola::MostrarMenu()
{
    std::cout << "===Menu Principal===" << std::endl;
    std::cout << "1.-Navegar a una pagina web." << std::endl;
    std::cout << "2.-Navegar a una pagina web de favoritos." << std::endl;
    std::cout << "3.-Navegar hacia adelante." << std::endl;
    std::cout << "4.-Navegar hacia atras." << std::endl;
    std::cout << "5.-Guardar en favoritos." << std::endl;
    std::cout << "6.-Elimar favorito." << std::endl;
    std::cout << "7.-Resturar favoritos." << std::endl;
    std::cout << "8.-Organizar favoritos." << std::endl;
    std::cout << "9.-Exportar a HTML." << std::endl;
    std::cout << "0.-Salir." << std::endl;
    std::cout << "" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Seleccione una accion: ";
}

void InterfazConsola::registrarComando(int opcion, std::unique_ptr<ICommand> comando)
{
    comandos_[opcion] = std::move(comando);
}

void InterfazConsola::ejecutar()
{
    int opcion;
    do
    {
        clearScreen();
        MostrarEncabezado();
        MostrarMenu();

        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 0)
            break;

        if (comandos_.count(opcion))
        {
            comandos_[opcion]->ejecutar();
        }
        else
        {
            std::cout << "Opción inválida\n";
        }
    } while (true);
}