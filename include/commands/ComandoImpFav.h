#pragma once
#include "ICommand.h"
#include "../Historial.h"
#include "../GestionF.h"

class ComandoImpFav : public ICommand
{
    GestionF &servicio;

public:
    explicit ComandoImpFav(GestionF &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};