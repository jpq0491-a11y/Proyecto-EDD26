#ifndef SERVICIO_RECETARIO_HPP
#define SERVICIO_RECETARIO_HPP

#include "ArchivoRecetario.hpp"

class ServicioRecetario {
private:
    Recetario recetario;
    ArchivoRecetario archivo;

public:
    const Recetario& obtenerRecetario() const;
    bool agregarReceta(const Receta& receta, std::string& mensaje);
    bool reemplazarReceta(int indice, const Receta& receta, std::string& mensaje);
    bool eliminarReceta(int indice, std::string& mensaje);
    bool guardar(const std::string& nombreArchivo, std::string& mensaje) const;
    bool cargar(const std::string& nombreArchivo, std::string& mensaje);
    std::vector<std::string> archivosDisponibles() const;
    void ordenarPorNombre();
    void ordenarPorTiempo();
    void vaciarRecetario();
};

#endif
