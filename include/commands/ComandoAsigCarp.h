#pragma once
#include "ICommand.h"
#include "../GestionF.h"
#include "../Favoritos.h"

#include <limits>

class ComandoAsigCarp : public ICommand
{
    GestionF &servicio;

public:
    explicit ComandoAsigCarp(GestionF &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};