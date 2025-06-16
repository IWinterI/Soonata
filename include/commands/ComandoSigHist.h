#pragma once
#include "ICommand.h"
#include "../Historial.h"

class ComandoSigHist : public ICommand
{
    Historial &servicio;

public:
    explicit ComandoSigHist(Historial &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};