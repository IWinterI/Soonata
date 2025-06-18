#pragma once
#include "ICommand.h"
#include "../ExpHTML.h"
#include "../GestionF.h"

class ComandoExpHTML : public ICommand
{
    ExpHTML &servicio;
    GestionF &archivo;

public:
    explicit ComandoExpHTML(ExpHTML &srv, GestionF &arch);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};