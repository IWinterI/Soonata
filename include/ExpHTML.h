#ifndef EXPHTML_H
#define EXPHTML_H
#include <string>
#include <vector>

struct Pagina {
    std::string nombre;
    std::string url;
};

class ExpHTML
{
    public:
        ExpHTML();
        virtual ~ExpHTML();
        void agregarPagina(const std::string& carpeta,
                      const std::string& nombrePagina,
                      const std::string& url);

        void generarArchivoHTML(const std::string& nombreArchivo);

    protected:

    private:
        std::string generarHTML();
        std::string escapeHTML(const std::string& texto);

        // Estructura: carpeta -> lista de páginas
        std::vector<std::pair<std::string, std::vector<Pagina>>> datos;
};

#endif // EXPHTML_H
