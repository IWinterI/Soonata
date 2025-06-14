#ifndef GESTIONF_H
#define GESTIONF_H
#include "Favoritos.h"
#include <vector>
#include <deque>
#include <string>

class GestionF
{
    public:
        GestionF();
        virtual ~GestionF();

        bool agregarFavorito(const std::string& url, const std::string& nombre, const std::string& carpeta = "");
        bool eliminarFavorito(const std::string& criterio);
        bool restaurarFavorito();


        std::vector<Favoritos> buscarPorNombre(const std::string& nombre) const;
        std::vector<Favoritos> buscarPorURL(const std::string& url) const;
        std::vector<Favoritos> buscarPorCarpeta(const std::string& carpeta) const;
        std::vector<Favoritos> obtenerTodos() const;


        bool asignarCarpeta(const std::string& criterio, const std::string& carpeta);


        bool cargarDesdeArchivo(const std::string& archivo);
        bool guardarEnArchivo(const std::string& archivo) const;

        void mostrarFavoritos() const;

    protected:

    private:
        std::vector<Favoritos> favoritos;
        std::deque<Favoritos> eliminadosRecientes;


        bool existeFavorito(const std::string& criterio);
};

#endif // GESTIONF_H
