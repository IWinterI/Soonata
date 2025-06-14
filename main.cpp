#include <iostream>
#include "Favoritos.h"
#include "GestionF.h"
#include <iostream>
using namespace std;

int main()
{
    GestionF gestor;

    // 1. Prueba de agregar favoritos
    std::cout << "=== Agregando favoritos ===\n";
    bool agregado1 = gestor.agregarFavorito("https://github.com", "GitHub", "Desarrollo");
    bool agregado2 = gestor.agregarFavorito("https://google.com", "Google", "Busqueda");
    bool agregado3 = gestor.agregarFavorito("https://stackoverflow.com", "Stack Overflow", "Desarrollo");
    bool agregado4 = gestor.agregarFavorito("https://youtube.com", "YouTube", "Entretenimiento");
    bool duplicado = gestor.agregarFavorito("https://github.com", "GitHub Duplicado", "Desarrollo");  // Debe fallar

    std::cout << "Agregados: "
              << agregado1 << ", " << agregado2 << ", "
              << agregado3 << ", " << agregado4 << "\n";
    std::cout << "Duplicado: " << duplicado << " (debe ser 0)\n\n";

    // 2. Mostrar todos los favoritos
    std::cout << "=== Mostrando todos los favoritos ===\n";
    gestor.mostrarFavoritos();
    std::cout << "\n";

    // 3. Búsquedas
    std::cout << "=== Buscando por nombre (Stack) ===\n";
    auto resultadosNombre = gestor.buscarPorNombre("Stack");
    for (const auto& fav : resultadosNombre) {
        std::cout << "Encontrado: " << fav.getNombre() << " - " << fav.getUrl() << "\n";
    }

    std::cout << "\n=== Buscando por URL (google) ===\n";
    auto resultadosURL = gestor.buscarPorURL("google");
    for (const auto& fav : resultadosURL) {
        std::cout << "Encontrado: " << fav.getNombre() << " - " << fav.getUrl() << "\n";
    }

    std::cout << "\n=== Buscando por carpeta (Desarrollo) ===\n";
    auto resultadosCarpeta = gestor.buscarPorCarpeta("Desarrollo");
    for (const auto& fav : resultadosCarpeta) {
        std::cout << "Encontrado: " << fav.getNombre() << " - " << fav.getUrl() << "\n";
    }
    std::cout << "\n";

    // 4. Eliminar favoritos
    std::cout << "=== Eliminando favoritos ===\n";
    bool eliminado1 = gestor.eliminarFavorito("Google");
    bool eliminado2 = gestor.eliminarFavorito("https://stackoverflow.com");
    bool noExistente = gestor.eliminarFavorito("No existe");

    std::cout << "Eliminados: " << eliminado1 << ", " << eliminado2 << "\n";
    std::cout << "Eliminado no existente: " << noExistente << " (debe ser 0)\n";

    std::cout << "\n=== Estado después de eliminar ===\n";
    gestor.mostrarFavoritos();
    std::cout << "\n";

    // 5. Restaurar favoritos
    std::cout << "=== Restaurando favoritos ===\n";
    bool restaurado1 = gestor.restaurarFavorito();  // Debe restaurar Stack Overflow
    bool restaurado2 = gestor.restaurarFavorito();  // Debe restaurar Google
    bool sinRestaurar = gestor.restaurarFavorito(); // No debería restaurar (cola vacía)

    std::cout << "Restaurados: " << restaurado1 << ", " << restaurado2 << "\n";
    std::cout << "Restauración fallida: " << sinRestaurar << " (debe ser 0)\n";

    std::cout << "\n=== Estado después de restaurar ===\n";
    gestor.mostrarFavoritos();
    std::cout << "\n";

    // 6. Asignar nueva carpeta
    std::cout << "=== Asignando nueva carpeta ===\n";
    bool asignado = gestor.asignarCarpeta("GitHub", "Programacion");
    bool noAsignado = gestor.asignarCarpeta("No existe", "Programacion");

    std::cout << "Asignado: " << asignado << "\n";
    std::cout << "No asignado: " << noAsignado << " (debe ser 0)\n";

    std::cout << "\n=== Estado después de reasignar carpeta ===\n";
    gestor.mostrarFavoritos();
    std::cout << "\n";

    // 7. Guardar en archivo
    std::cout << "=== Guardando en archivo ===\n";
    bool guardado = gestor.guardarEnArchivo("favoritos.txt");
    std::cout << "Guardado: " << guardado << "\n\n";

    // 8. Cargar desde archivo
    std::cout << "=== Cargando desde archivo ===\n";
    GestionF gestor2;
    bool cargado = gestor2.cargarDesdeArchivo("favoritos.txt");
    std::cout << "Cargado: " << cargado << "\n";

    std::cout << "\n=== Contenido cargado desde archivo ===\n";
    gestor2.mostrarFavoritos();

    // 9. Obtener todos los favoritos
    std::cout << "\n=== Obteniendo todos los favoritos (vector) ===\n";
    auto todos = gestor.obtenerTodos();
    std::cout << "Total de favoritos: " << todos.size() << "\n";


    return 0;
}
