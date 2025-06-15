#ifndef INTERFAZCONSOLA_H
#define INTERFAZCONSOLA_H

#include <iostream>

class InterfazConsola
{
public:
    InterfazConsola();
    virtual ~InterfazConsola();

    void MostrarEncabezado();
    void MostrarMenu();
    bool ProcesarOpcion(int opcion);
    void workinprogrece(int opcion);

protected:
private:
    void clearScreen();
    void printCentered(const std::string &text, int width = 50);
};

#endif // INTERFAZCONSOLA_H
