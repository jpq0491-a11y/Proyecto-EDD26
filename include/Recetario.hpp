#ifndef RECETARIO_HPP
#define RECETARIO_HPP

#include <iostream>
#include <string>
#include <fstream> 
#include "lista.hpp"
#include "Receta.hpp"

class Recetario {
private:
    List<Receta, 50> listaRecetas; 

public:
    Recetario() {}

    // --- PANTALLA 3: Agregar ---
    bool agregarReceta(const Receta& nuevaReceta) {
        // Se inserta en la siguiente posición disponible
        return listaRecetas.insert(nuevaReceta, listaRecetas.lastPos() + 1);
    }

    // --- PANTALLA 2.1: Mostrar todas ---
    void mostrarTodas() const {
        if (listaRecetas.isEmpty()) {
            std::cout << "El recetario esta vacio.\n";
            return;
        }
        std::cout << "No. | NOMBRE DE LA RECETA | CATEGORIA | TIEMPO\n";
        for (int i = 0; i <= listaRecetas.lastPos(); i++) {
            Receta r = listaRecetas.retrieve(i);
            std::cout << i + 1 << " | " << r.getNombre() << " | " 
                      << r.getCategoria() << " | " << r.getTiempoPreparacion() << " min\n";
        }
    }

    // --- PANTALLA 2.2: Filtrar ---
    void filtrarPorCategoria(const std::string& categoria) const {
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

    // --- PANTALLA 4.1: Buscar por nombre ---
    int buscarPorNombre(const std::string& nombre) const {
        for (int i = 0; i <= listaRecetas.lastPos(); i++) {
            Receta r = listaRecetas.retrieve(i);
            if (r.getNombre() == nombre) {
                return i;
            }
        }
        return -1;
    }
    Receta obtenerReceta(int indice) const {
        return listaRecetas.retrieve(indice);
    }

    // --- PANTALLA 5.4: Eliminar todas ---
    void vaciarRecetario() {
        listaRecetas.clear();
    }
};

#endif