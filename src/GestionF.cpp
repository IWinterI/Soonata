#include "GestionF.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

GestionF::GestionF()
{
    //ctor
}

GestionF::~GestionF()
{
    //dtor
}



bool GestionF::existeFavorito(const std::string& criterio) {
    auto it = std::find_if(favoritos.begin(), favoritos.end(),
        [&criterio](const Favoritos& fav) {
            return fav.getNombre() == criterio || fav.getUrl() == criterio;
        });
    return it != favoritos.end();
}


bool GestionF::agregarFavorito(const std::string& url, const std::string& nombre, const std::string& carpeta) {
    if (existeFavorito(nombre) || existeFavorito(url)) {
        return false;
    }
    favoritos.push_back(Favoritos(url, nombre, carpeta));
    return true;
}

void GestionF::mostrarFavoritos() const {
        if (favoritos.empty()) {
            std::cout << "No hay favoritos registrados.\n";
            return;
        }

        std::cout << "=== LISTA DE FAVORITOS ===\n";
        for (const auto& fav : favoritos) {
            std::cout << "Nombre: " << fav.getNombre() << "\n"
                      << "URL: " << fav.getUrl() << "\n"
                      << "Carpeta: " << fav.getCarpeta() << "\n"
                      << "-------------------------\n";
        }
    }


bool GestionF::eliminarFavorito(const std::string& criterio) {
    auto it = std::find_if(favoritos.begin(), favoritos.end(),
        [&criterio](const Favoritos& fav) {
            return fav.getNombre() == criterio || fav.getUrl() == criterio;
        });

    if (it != favoritos.end()) {

        eliminadosRecientes.push_back(*it);


        if (eliminadosRecientes.size() > 5) {
            eliminadosRecientes.pop_front();
        }

        favoritos.erase(it);
        return true;
    }
    return false;
}


bool GestionF::restaurarFavorito() {
    if (eliminadosRecientes.empty()) return false;

    Favoritos fav = eliminadosRecientes.back();
    eliminadosRecientes.pop_back();


    if (!existeFavorito(fav.getNombre()) && !existeFavorito(fav.getUrl())) {
        favoritos.push_back(fav);
        return true;
    }
    return false;
}


std::vector<Favoritos> GestionF::buscarPorNombre(const std::string& nombre) const {
    std::vector<Favoritos> resultados;
    for (const auto& fav : favoritos) {
        if (fav.getNombre().find(nombre) != std::string::npos) {
            resultados.push_back(fav);
        }
    }
    return resultados;
}

std::vector<Favoritos> GestionF::buscarPorURL(const std::string& url) const {
    std::vector<Favoritos> resultados;
    for (const auto& fav : favoritos) {
        if (fav.getUrl().find(url) != std::string::npos) {
            resultados.push_back(fav);
        }
    }
    return resultados;
}

std::vector<Favoritos> GestionF::buscarPorCarpeta(const std::string& carpeta) const {
    std::vector<Favoritos> resultados;
    for (const auto& fav : favoritos) {
        if (fav.getCarpeta() == carpeta) {
            resultados.push_back(fav);
        }
    }
    return resultados;
}

std::vector<Favoritos> GestionF::obtenerTodos() const {
    return favoritos;
}


bool GestionF::asignarCarpeta(const std::string& criterio, const std::string& carpeta) {
    auto it = std::find_if(favoritos.begin(), favoritos.end(),
        [&criterio](const Favoritos& fav) {
            return fav.getNombre() == criterio || fav.getUrl() == criterio;
        });

    if (it != favoritos.end()) {
        it->setCarpeta(carpeta);
        return true;
    }
    return false;
}


bool GestionF::cargarDesdeArchivo(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) return false;

    favoritos.clear();
    std::string linea;

    while (std::getline(file, linea)) {
        std::istringstream ss(linea);
        std::string nombre, url, carpeta;

        if (std::getline(ss, nombre, ',') &&
            std::getline(ss, url, ',') &&
            std::getline(ss, carpeta)) {

            favoritos.emplace_back(url, nombre, carpeta);
        }
    }
    file.close();
    return true;
}

bool GestionF::guardarEnArchivo(const std::string& archivo) const {
    std::ofstream file(archivo);
    if (!file.is_open()) return false;

    for (const auto& fav : favoritos) {
        file << fav.getNombre() << ','
             << fav.getUrl() << ','
             << fav.getCarpeta() << '\n';
    }
    file.close();
    return true;
}

