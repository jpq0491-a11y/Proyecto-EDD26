#include "Recetario.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace {
std::string normalizar(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
        [](unsigned char caracter) { return std::tolower(caracter); });
    return resultado;
}
}

Recetario::Recetario() {}

bool Recetario::agregarReceta(const Receta& nuevaReceta) {
    if (listaRecetas.isFull() || buscarPorNombre(nuevaReceta.getNombre()) != -1) {
        return false;
    }
    return listaRecetas.insert(nuevaReceta, listaRecetas.lastPos() + 1);
}

bool Recetario::reemplazarReceta(int indice, const Receta& recetaActualizada) {
    if (indice < 0 || indice >= cantidadRecetas()) {
        return false;
    }

    for (int i = 0; i < cantidadRecetas(); ++i) {
        if (i != indice && normalizar(listaRecetas.retrieve(i).getNombre()) == normalizar(recetaActualizada.getNombre())) {
            return false;
        }
    }
    listaRecetas.remove(indice);
    return listaRecetas.insert(recetaActualizada, indice);
}

bool Recetario::eliminarReceta(int indice) { return listaRecetas.remove(indice); }

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
        if (normalizar(r.getCategoria()) == normalizar(categoria)) {
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
        if (normalizar(r.getNombre()) == normalizar(nombre)) {
            return i;
        }
    }
    return -1; // Retorna -1 si no la encuentra
}

Receta Recetario::obtenerReceta(int indice) const {
    return listaRecetas.retrieve(indice);
}

int Recetario::cantidadRecetas() const { return listaRecetas.lastPos() + 1; }
bool Recetario::estaVacio() const { return listaRecetas.isEmpty(); }
bool Recetario::estaLleno() const { return listaRecetas.isFull(); }

void Recetario::ordenarPorNombre() { listaRecetas.insertSort(); }

void Recetario::ordenarPorTiempo() {
    List<Receta, 50> ordenadas;
    for (int i = 0; i < cantidadRecetas(); ++i) {
        Receta actual = listaRecetas.retrieve(i);
        int posicion = ordenadas.lastPos() + 1;
        for (int j = ordenadas.first(); j != -1; j = ordenadas.next(j)) {
            Receta comparada = ordenadas.retrieve(j);
            if (actual.getTiempoPreparacion() < comparada.getTiempoPreparacion() ||
                (actual.getTiempoPreparacion() == comparada.getTiempoPreparacion() && actual < comparada)) {
                posicion = j;
                break;
            }
        }
        ordenadas.insert(actual, posicion);
    }
    listaRecetas = ordenadas;
}

void Recetario::vaciarRecetario() {
    listaRecetas.clear();
}
