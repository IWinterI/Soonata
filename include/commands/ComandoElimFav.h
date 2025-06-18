#pragma once
#include "ICommand.h"
#include "../Historial.h"
#include "../GestionF.h"

#include <limits>

class ComandoElimFav : public ICommand
{
    GestionF &servicio;

public:
    explicit ComandoElimFav(GestionF &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};