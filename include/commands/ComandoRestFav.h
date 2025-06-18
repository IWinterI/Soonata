#pragma once
#include "ICommand.h"
#include "../GestionF.h"
#include "../Favoritos.h"

class ComandoRestFav : public ICommand
{
    GestionF &servicio;

public:
    explicit ComandoRestFav(GestionF &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
};