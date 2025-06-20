#ifndef GESTIONF_H
#define GESTIONF_H
#include "../include/Favoritos.h"
#include "../include/Historial.h"
#include <vector>
#include <deque>
#include <string>
#include <set>
#include <map>
#include <limits>

class GestionF
{
public:
    GestionF();
    virtual ~GestionF();

    bool estavacio() const;
    bool agregarFavorito(const std::string &url, const std::string &nombre, const std::string &carpeta = "");
    bool eliminarFavorito(const std::string &criterio);
    bool restaurarFavorito();

    std::vector<Favoritos> buscarPorNombre(const std::string &nombre) const;
    std::vector<Favoritos> buscarPorURL(const std::string &url) const;
    std::vector<Favoritos> buscarPorCarpeta(const std::string &carpeta) const;
    std::vector<Favoritos> buscarPorCriterio(const std::string &criterio) const;

    std::vector<Favoritos> obtenerTodos() const;
    std::deque<Favoritos> obtenerEliminados() const;
    std::vector<std::string> obtenerCarpetasExistentes() const;

    bool asignarCarpeta(const std::string &criterio, const std::string &carpeta);

    bool cargarDesdeArchivo(const std::string &archivo);
    bool guardarEnArchivo(const std::string &archivo) const;

    void mostrarFavoritos() const;
    void mostrarFavoritosPorCarpeta() const;
    void mostrarFavorito(const std::string &criterio, const std::string &carpeta) const;
    Favoritos seleccionarFavorito(const std::vector<Favoritos> &opciones) const;

protected:
private:
    std::vector<Favoritos> favoritos;
    std::deque<Favoritos> eliminadosRecientes;

    bool existeFavorito(const std::string &criterio);
};

#endif // GESTIONF_H
