#ifndef FAVORITOS_H
#define FAVORITOS_H
#include <string>

class Favoritos
{
    public:
        Favoritos(const std::string& url, const std::string& nombre, const std::string& carpeta = "");


        virtual ~Favoritos();

        // Getters
        std::string getUrl() const;
        std::string getNombre() const;
        std::string getCarpeta() const;

        // Setters
        void setUrl(const std::string& url);
        void setNombre(const std::string& nombre);
        void setCarpeta(const std::string& carpeta);



    protected:

    private:
        std::string url;
        std::string nombre;
        std::string carpeta;

};

#endif // FAVORITOS_H
