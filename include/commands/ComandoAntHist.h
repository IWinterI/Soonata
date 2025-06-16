#pragma once
#include "ICommand.h"
#include "../Historial.h"

class ComandoAntHist : public ICommand
{
    Historial &servicio;

public:
    explicit ComandoAntHist(Historial &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};