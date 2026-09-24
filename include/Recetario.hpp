#ifndef RECETARIO_HPP
#define RECETARIO_HPP

#include <string>
#include "lista.hpp"
#include "Receta.hpp"

class Recetario {
private:
    List<Receta, 50> listaRecetas; // Tu lista estática principal

public:
    Recetario();

    bool agregarReceta(const Receta& nuevaReceta);
    void mostrarTodas() const;
    void filtrarPorCategoria(const std::string& categoria) const;
    int buscarPorNombre(const std::string& nombre) const;
    Receta obtenerReceta(int indice) const;
    void vaciarRecetario();
};

#endif