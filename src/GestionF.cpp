#include "../include/GestionF.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

GestionF::GestionF()
{
    // ctor
}

GestionF::~GestionF()
{
    // dtor
}

bool GestionF::estavacio() const
{
    if (favoritos.empty())
    {
        return true;
    }

    return false;
}

bool GestionF::existeFavorito(const std::string &criterio)
{
    auto it = std::find_if(favoritos.begin(), favoritos.end(),
                           [&criterio](const Favoritos &fav)
                           {
                               return fav.getNombre() == criterio || fav.getUrl() == criterio;
                           });
    return it != favoritos.end();
}

bool GestionF::agregarFavorito(const std::string &url, const std::string &nombre, const std::string &carpeta)
{
    if (existeFavorito(nombre) || existeFavorito(url))
    {
        return false;
    }
    favoritos.push_back(Favoritos(url, nombre, carpeta));
    return true;
}

void GestionF::mostrarFavoritos() const
{
    if (favoritos.empty())
    {
        std::cout << "No hay favoritos registrados.\n";
        return;
    }

    std::cout << "============= LISTA DE FAVORITOS ================" << std::endl;
    for (const auto &fav : favoritos)
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nombre: " << fav.getNombre() << std::endl;
        std::cout << "Url: " << fav.getUrl() << std::endl;
        std::cout << "Carpeta: " << fav.getCarpeta() << std::endl;
    }
    std::cout << std::string(50, '-') << std::endl;
}

bool GestionF::eliminarFavorito(const std::string &criterio)
{
    auto it = std::find_if(favoritos.begin(), favoritos.end(),
                           [&criterio](const Favoritos &fav)
                           {
                               return fav.getNombre() == criterio || fav.getUrl() == criterio;
                           });

    if (it != favoritos.end())
    {

        eliminadosRecientes.push_back(*it);

        if (eliminadosRecientes.size() > 5)
        {
            eliminadosRecientes.pop_front();
        }

        favoritos.erase(it);
        return true;
    }
    return false;
}

bool GestionF::restaurarFavorito()
{
    if (eliminadosRecientes.empty())
        return false;

    Favoritos fav = eliminadosRecientes.back();
    eliminadosRecientes.pop_back();

    if (!existeFavorito(fav.getNombre()) && !existeFavorito(fav.getUrl()))
    {
        favoritos.push_back(fav);
        return true;
    }
    return false;
}

std::vector<Favoritos> GestionF::buscarPorNombre(const std::string &nombre) const
{
    std::vector<Favoritos> resultados;
    for (const auto &fav : favoritos)
    {
        if (fav.getNombre().find(nombre) != std::string::npos)
        {
            resultados.push_back(fav);
        }
    }
    return resultados;
}

std::vector<Favoritos> GestionF::buscarPorURL(const std::string &url) const
{
    std::vector<Favoritos> resultados;
    for (const auto &fav : favoritos)
    {
        if (fav.getUrl().find(url) != std::string::npos)
        {
            resultados.push_back(fav);
        }
    }
    return resultados;
}

std::vector<Favoritos> GestionF::buscarPorCarpeta(const std::string &carpeta) const
{
    std::vector<Favoritos> resultados;
    for (const auto &fav : favoritos)
    {
        if (fav.getCarpeta() == carpeta)
        {
            resultados.push_back(fav);
        }
    }
    return resultados;
}

std::vector<Favoritos> GestionF::obtenerTodos() const
{
    return favoritos;
}

std::deque<Favoritos> GestionF::obtenerEliminados() const
{
    return eliminadosRecientes;
}

bool GestionF::asignarCarpeta(const std::string &criterio, const std::string &carpeta)
{
    auto it = std::find_if(favoritos.begin(), favoritos.end(),
                           [&criterio](const Favoritos &fav)
                           {
                               return fav.getNombre() == criterio || fav.getUrl() == criterio;
                           });

    if (it != favoritos.end())
    {
        it->setCarpeta(carpeta);
        return true;
    }
    return false;
}

bool GestionF::cargarDesdeArchivo(const std::string &archivo)
{
    std::ifstream file(archivo);
    if (!file.is_open())
        return false;

    favoritos.clear();
    std::string linea;

    while (std::getline(file, linea))
    {
        std::istringstream ss(linea);
        std::string nombre, url, carpeta;

        if (std::getline(ss, nombre, ',') &&
            std::getline(ss, url, ',') &&
            std::getline(ss, carpeta))
        {

            favoritos.emplace_back(url, nombre, carpeta);
        }
    }
    file.close();
    return true;
}

bool GestionF::guardarEnArchivo(const std::string &archivo) const
{
    std::ofstream file(archivo);
    if (!file.is_open())
        return false;

    for (const auto &fav : favoritos)
    {
        file << fav.getNombre() << ','
             << fav.getUrl() << ','
             << fav.getCarpeta() << '\n';
    }
    file.close();
    return true;
}

std::vector<std::string> GestionF::obtenerCarpetasExistentes() const
{
    std::set<std::string> carpetasSet;

    for (const auto &fav : favoritos)
    {
        carpetasSet.insert(fav.getCarpeta());
    }

    return std::vector<std::string>(carpetasSet.begin(), carpetasSet.end());
}

void GestionF::mostrarFavorito(const std::string &criterio, const std::string &carpeta) const
{
    for (auto var : favoritos)
    {
        if ((var.getNombre() == criterio || var.getUrl() == criterio) && var.getCarpeta() == carpeta)
        {
            std::cout << "Nombre: " << var.getNombre() << std::endl;
            std::cout << "Url: " << var.getUrl() << std::endl;
            std::cout << "Carpeta: " << var.getCarpeta() << std::endl;
        }
    }
}

void GestionF::mostrarFavoritosPorCarpeta() const
{
    if (favoritos.empty())
    {
        std::cout << "No hay favoritos registrados.\n";
        return;
    }

    // Agrupar favoritos por carpeta
    std::map<std::string, std::vector<Favoritos>> favoritosPorCarpeta;

    for (const auto &fav : favoritos)
    {
        favoritosPorCarpeta[fav.getCarpeta()].push_back(fav);
    }

    // Ordenar las carpetas alfabéticamente
    std::vector<std::string> carpetas;
    for (const auto &par : favoritosPorCarpeta)
    {
        carpetas.push_back(par.first);
    }
    std::sort(carpetas.begin(), carpetas.end());

    std::cout << "============= FAVORITOS POR CARPETA =============" << std::endl;

    for (const auto &carpeta : carpetas)
    {
        std::cout << "\n--- CARPETA: " << carpeta << " ---" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        // Ordenar favoritos dentro de la carpeta por nombre
        auto &favoritosEnCarpeta = favoritosPorCarpeta[carpeta];
        std::sort(favoritosEnCarpeta.begin(), favoritosEnCarpeta.end(),
                  [](const Favoritos &a, const Favoritos &b)
                  {
                      return a.getNombre() < b.getNombre();
                  });

        for (const auto &fav : favoritosEnCarpeta)
        {
            std::cout << "Nombre: " << fav.getNombre() << std::endl;
            std::cout << "Url: " << fav.getUrl() << std::endl;
            std::cout << std::string(50, '-') << std::endl;
        }
    }
}

Favoritos GestionF::seleccionarFavorito(const std::vector<Favoritos> &opciones) const
{
    if (opciones.empty())
    {
        throw std::runtime_error("No hay opciones para seleccionar");
    }

    // Si solo hay una opción, devolverla directamente
    if (opciones.size() == 1)
    {
        return opciones[0];
    }

    // Mostrar encabezado de selección
    std::cout << "\n=== Seleccione un favorito ===\n";

    // Mostrar todas las opciones numeradas
    for (size_t i = 0; i < opciones.size(); ++i)
    {
        const auto &fav = opciones[i];
        std::cout << i + 1 << ". " << fav.getNombre()
                  << " (" << fav.getUrl() << ")"
                  << " - Carpeta: " << fav.getCarpeta() << "\n";
    }
    std::cout << "0. Cancelar búsqueda\n";

    // Manejar entrada del usuario
    int seleccion = -1;
    while (true)
    {
        std::cout << "\nIngrese el número de la opción (0 para cancelar): ";

        // Validar que la entrada sea un número
        if (!(std::cin >> seleccion))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor ingrese un número.\n";
            continue;
        }

        // Validar rango de selección
        if (seleccion == 0)
        {
            throw std::runtime_error("Búsqueda cancelada por el usuario");
        }
        if (seleccion < 1 || seleccion > static_cast<int>(opciones.size()))
        {
            std::cout << "Opción inválida. Por favor seleccione un número entre 1 y "
                      << opciones.size() << ".\n";
            continue;
        }

        break;
    }

    return opciones[seleccion - 1];
}