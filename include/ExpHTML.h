#ifndef EXPHTML_H
#define EXPHTML_H

#include <vector>
#include <string>
#include "Favoritos.h"

class ExpHTML
{
public:
    ExpHTML();
    ~ExpHTML();

    void generarArchivoHTML(const std::string &nombreArchivo, const std::vector<Favoritos> &favoritos);

private:
    std::string generarHTML(const std::vector<Favoritos> &favoritos);
    std::string escapeHTML(const std::string &texto);
};

#endif // EXPHTML_H