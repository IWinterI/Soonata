#pragma once
#include <memory>
#include <limits>
#include <iostream>
#include <string>

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void ejecutar() = 0;
    virtual void Encabezado() = 0;
    virtual std::string nombre() const = 0;

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

    void printCentered(const std::string &text, int width = 50)
    {
        int padding = (width - static_cast<int>(text.length())) / 2;
        if (padding > 0)
            std::cout << std::string(padding, ' ');
        std::cout << text << std::endl;
    }
};

using ComandoPtr = std::unique_ptr<ICommand>;