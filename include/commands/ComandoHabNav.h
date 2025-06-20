#pragma once
#include "ICommand.h"
#include "../Historial.h"

class ComandoHabNav : public ICommand
{
    Historial &servicio;

public:
    explicit ComandoHabNav(Historial &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};