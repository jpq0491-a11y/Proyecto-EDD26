#include "Recetario.hpp"
#include <iostream>

Recetario::Recetario() {}

bool Recetario::agregarReceta(const Receta& nuevaReceta) {
    // Se inserta en la siguiente posición disponible
    return listaRecetas.insert(nuevaReceta, listaRecetas.lastPos() + 1);
}

void Recetario::mostrarTodas() const {
    if (listaRecetas.isEmpty()) {
        std::cout << "El recetario esta vacio.\n";
        return;
    }
    std::cout << "No. | NOMBRE DE LA RECETA | CATEGORIA | TIEMPO\n";
    for (int i = 0; i <= listaRecetas.lastPos(); i++) {
        Receta r = listaRecetas.retrieve(i);
        // Se imprime i+1 para que el usuario vea la lista iniciando en 1
        std::cout << i + 1 << " | " << r.getNombre() << " | " 
                  << r.getCategoria() << " | " << r.getTiempoPreparacion() << " min\n";
    }
}

void Recetario::filtrarPorCategoria(const std::string& categoria) const {
    bool encontrada = false;
    std::cout << "No. | NOMBRE DE LA RECETA | TIEMPO\n";
    for (int i = 0; i <= listaRecetas.lastPos(); i++) {
        Receta r = listaRecetas.retrieve(i);
        if (r.getCategoria() == categoria) {
            std::cout << i + 1 << " | " << r.getNombre() << " | " 
                      << r.getTiempoPreparacion() << " min\n";
            encontrada = true;
        }
    }
    if (!encontrada) {
        std::cout << "No hay recetas en esta categoria.\n";
    }
}

int Recetario::buscarPorNombre(const std::string& nombre) const {
    for (int i = 0; i <= listaRecetas.lastPos(); i++) {
        Receta r = listaRecetas.retrieve(i);
        if (r.getNombre() == nombre) {
            return i;
        }
    }
    return -1; // Retorna -1 si no la encuentra
}

Receta Recetario::obtenerReceta(int indice) const {
    return listaRecetas.retrieve(indice);
}

void Recetario::vaciarRecetario() {
    listaRecetas.clear();
}