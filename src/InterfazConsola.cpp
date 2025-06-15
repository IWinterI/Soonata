#include "InterfazConsola.h"

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

bool InterfazConsola::ProcesarOpcion(int opcion)
{
    switch (opcion)
    {
    case 0:
        std::cout << std::string(50, '=') << std::endl;
        printCentered("Gracias por visitarnos.");
        printCentered("Vuelva pronto.");
        std::cout << std::string(50, '=') << std::endl;
        return false;
        break;
    case 1:
        workinprogrece(opcion);
        return true;
        break;
    case 2:
        workinprogrece(opcion);
        return true;
        break;
    case 3:
        workinprogrece(opcion);
        return true;
        break;
    case 4:
        workinprogrece(opcion);
        return true;
        break;
    case 5:
        workinprogrece(opcion);
        return true;
        break;
    case 6:
        workinprogrece(opcion);
        return true;
        break;
    case 7:
        workinprogrece(opcion);
        return true;
        break;
    case 8:
        workinprogrece(opcion);
        return true;
        break;
    case 9:
        workinprogrece(opcion);
        return true;
        break;
    default:
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "Error: opcion invalida" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        break;
    }
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