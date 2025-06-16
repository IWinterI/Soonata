#pragma once
#include "ICommand.h"
#include "../Historial.h"

class ComandoNavegar : public ICommand
{
    Historial &servicio;

public:
    explicit ComandoNavegar(Historial &srv);

    void ejecutar() override;
    std::string obtenerNombre() const override;
};