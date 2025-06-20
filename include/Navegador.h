#ifndef NAVEGADOR_H
#define NAVEGADOR_H

#include <string>

class Navegador
{
public:
    /**
     * Verifica si el navegador predeterminado está actualmente en ejecución
     * @return true si el navegador está abierto, false en caso contrario
     */
    static bool estaNavegadorAbierto();

    /**
     * Abre una URL en el navegador predeterminado
     * @param url La URL a abrir
     * @return true si tuvo éxito, false si hubo error
     */
    static bool abrirURL(const std::string &url);

    /**
     * Abre una URL en una nueva pestaña del navegador predeterminado
     * @param url La URL a abrir
     * @return true si tuvo éxito, false si hubo error
     */
    static bool abrirURLNuevaPestana(const std::string &url);

    /**
     * Abre una URL usando la estrategia óptima (nueva ventana o pestaña)
     * @param url La URL a abrir
     * @return true si tuvo éxito, false si hubo error
     */
    static bool abrirURLOptimo(const std::string &url);
};

#endif // NAVEGADOR_H