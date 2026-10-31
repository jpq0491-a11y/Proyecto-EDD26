#include "ServicioRecetario.hpp"

const Recetario& ServicioRecetario::obtenerRecetario() const { return recetario; }

bool ServicioRecetario::agregarReceta(const Receta& receta, std::string& mensaje) {
    if (recetario.buscarPorNombre(receta.getNombre()) != -1) {
        mensaje = "Ya existe una receta con ese nombre.";
        return false;
    }
    if (!recetario.agregarReceta(receta)) {
        mensaje = "No hay memoria suficiente para guardar la receta.";
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
