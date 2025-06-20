#ifndef EXPJSON_H
#define EXPJSON_H

#include "Favoritos.h"
#include <vector>
#include <string>

class ExpJSON
{
public:
    void exportarFavoritos(const std::string &nombreArchivo, const std::vector<Favoritos> &favoritos);
    std::vector<Favoritos> importarFavoritos(const std::string &nombreArchivo);

private:
    std::string escapeJSON(const std::string &texto);
    std::string unescapeJSON(const std::string &texto);
};

#endif // EXPJSON_H