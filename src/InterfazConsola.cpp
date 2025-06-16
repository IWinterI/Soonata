#include "../include/InterfazConsola.h"

InterfazConsola::InterfazConsola()
{
    // ctor
}

InterfazConsola::~InterfazConsola()
{
    // dtor
}

void InterfazConsola::pausarConsola()
{
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "\nPresione Enter para continuar...";
    std::cout << std::string(50, '-') << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Espera a que se presione Enter
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
    printCentered("================= Menu principal =================");
    for (const auto &par : comandos_)
    {
        std::cout << par.first << ".-" << par.second->nombre() << std::endl;
    }
    std::cout << "0.-Salir del navegador." << std::endl;
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
        std::cout << std::string(50, '=') << std::endl;

        if (opcion == 0)
        {
            std::cout << std::string(50, '=') << std::endl;
            printCentered("Saliendo del navegador.");
            printCentered("Vuelva pronto");
            std::cout << std::string(50, '=') << std::endl;
            break;
        }

        if (comandos_.count(opcion))
        {
            comandos_[opcion]->ejecutar();
        }
        else
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Opción inválida" << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            pausarConsola();
        }
    } while (true);
}