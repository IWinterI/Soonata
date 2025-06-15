#include "Favoritos.h"


Favoritos::Favoritos(const std::string& url, const std::string& nombre, const std::string& carpeta) : url(url), nombre(nombre), carpeta(carpeta)
{
    //ctor
}


std::string Favoritos::getUrl() const {
    return url;
}

std::string Favoritos::getNombre() const {
    return nombre;
}

std::string Favoritos::getCarpeta() const {
    return carpeta;
}


void Favoritos::setUrl(const std::string& url) {
    this->url = url;
}

void Favoritos::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Favoritos::setCarpeta(const std::string& carpeta) {
    this->carpeta = carpeta;
}

Favoritos::~Favoritos()
{
    //dtor
}
