#pragma once
#include "ICommand.h"
#include "../Historial.h"
#include "../GestionF.h"

#include <limits>

class ComandoAddFav : public ICommand
{
    GestionF &servicio;

public:
    explicit ComandoAddFav(GestionF &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};