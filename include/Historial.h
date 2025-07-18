#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <regex>

class Historial
{
public:
    Historial();
    virtual ~Historial();

    bool visitar(const std::string &url);
    bool siguiente();
    bool anterior();

    std::string get_actual() const;
    void imprimir_historial();
    void borrar_historial();
    bool puede_avanzar() const;
    bool puede_retroceder() const;
    static bool url_valida(const std::string &url);
    void hab_navegacion();
    bool get_navegacion();

protected:
private:
    bool Navegacion;
    std::list<std::string> historial;
    std::list<std::string>::iterator actual;
};

#endif // HISTORIAL_H
