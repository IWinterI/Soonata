#pragma once
#include "ICommand.h"
#include "../Historial.h"

class ComandoImpHist : public ICommand
{
    Historial &servicio;

public:
    explicit ComandoImpHist(Historial &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};