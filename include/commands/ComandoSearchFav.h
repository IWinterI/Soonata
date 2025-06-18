#pragma once
#include "ICommand.h"
#include "../GestionF.h"
#include "../Favoritos.h"

class ComandoSearchFav : public ICommand
{
    GestionF &servicio;

public:
    explicit ComandoSearchFav(GestionF &srv);

    void ejecutar() override;
    std::string nombre() const override;
    void Encabezado() override;
    void imprimir(std::vector<Favoritos> resultados);
};