#include "ServicioRecetario.hpp"

const Recetario& ServicioRecetario::obtenerRecetario() const { return recetario; }

bool ServicioRecetario::agregarReceta(const Receta& receta, std::string& mensaje) {
    if (recetario.estaLleno()) {
        mensaje = "El recetario alcanzo su capacidad maxima de 50 recetas.";
        return false;
    }
    if (!recetario.agregarReceta(receta)) {
        mensaje = "Ya existe una receta con ese nombre.";
        return false;
    }
    mensaje = "Receta guardada con exito.";
    return true;
}

bool ServicioRecetario::reemplazarReceta(int indice, const Receta& receta, std::string& mensaje) {
    if (!recetario.reemplazarReceta(indice, receta)) {
        mensaje = "No se pudo actualizar: indice invalido o nombre duplicado.";
        return false;
    }
    mensaje = "Receta actualizada con exito.";
    return true;
}

bool ServicioRecetario::eliminarReceta(int indice, std::string& mensaje) {
    if (!recetario.eliminarReceta(indice)) {
        mensaje = "La receta seleccionada no existe.";
        return false;
    }
    mensaje = "Receta eliminada con exito.";
    return true;
}

bool ServicioRecetario::guardar(const std::string& nombreArchivo, std::string& mensaje) const {
    return archivo.guardar(recetario, nombreArchivo, mensaje);
}

bool ServicioRecetario::cargar(const std::string& nombreArchivo, std::string& mensaje) {
    return archivo.cargar(nombreArchivo, recetario, mensaje);
}

std::vector<std::string> ServicioRecetario::archivosDisponibles() const { return archivo.listarArchivos(); }
void ServicioRecetario::ordenarPorNombre() { recetario.ordenarPorNombre(); }
void ServicioRecetario::ordenarPorTiempo() { recetario.ordenarPorTiempo(); }
void ServicioRecetario::vaciarRecetario() { recetario.vaciarRecetario(); }
