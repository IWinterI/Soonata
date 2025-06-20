#pragma once
#include "ICommand.h"
#include "../Historial.h"
#include "../Navegador.h"

class ComandoSigHist : public ICommand
{
    Historial &servicio;
    Navegador &navegador;

public:
    explicit ComandoSigHist(Historial &srv, Navegador &nav);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};