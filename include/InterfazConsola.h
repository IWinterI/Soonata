#ifndef INTERFAZCONSOLA_H
#define INTERFAZCONSOLA_H

// Librerias
#include <iostream>
#include <map>
#include <memory>

// Encabezados
#include "../include/commands/ICommand.h"

class InterfazConsola
{
public:
    InterfazConsola();
    virtual ~InterfazConsola();

    void MostrarEncabezado();
    void MostrarMenu();
    void workinprogrece(int opcion);

    void registrarComando(int opcion, std::unique_ptr<ICommand> comando);
    void ejecutar();

protected:
private:
    std::map<int, std::unique_ptr<ICommand>> comandos_;
    void clearScreen();
    void printCentered(const std::string &text, int width = 50);
};

#endif // INTERFAZCONSOLA_H
