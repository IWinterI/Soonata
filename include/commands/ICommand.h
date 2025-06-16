#pragma once
#include <memory>
#include <limits>
#include <iostream>

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void ejecutar() = 0;
    virtual std::string obtenerNombre() const = 0;

    void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pausarConsola()
    {
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get(); // Espera a que se presione Enter
    }
};

using ComandoPtr = std::unique_ptr<ICommand>;