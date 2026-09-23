#ifndef RECETA_HPP
#define RECETA_HPP

#include <string>
#include <iostream>
#include "lista.hpp"
#include "Ingrediente.hpp"
#include "Paso.hpp"
#include "Name.hpp"

class Receta {
private:
    std::string nombre;
    std::string categoria;
    Name autor;
    int tiempoPreparacion;
    List<Ingrediente, 50> listaIngredientes; // Uso de la plantilla estática
    List<Paso, 50> procedimiento;            // Procedimiento estructurado en pasos

public:
    Receta() : nombre(""), categoria(""), tiempoPreparacion(0) {}
    
    Receta(std::string n, std::string cat, Name aut, int tiempo) 
        : nombre(n), categoria(cat), autor(aut), tiempoPreparacion(tiempo) {}

    std::string getNombre() const { return nombre; }
    std::string getCategoria() const { return categoria; }
    Name getAutor() const { return autor; }
    int getTiempoPreparacion() const { return tiempoPreparacion; }

    void setNombre(std::string n) { nombre = n; }
    void setCategoria(std::string cat) { categoria = cat; }
    void setAutor(Name aut) { autor = aut; }
    void setTiempoPreparacion(int tiempo) { tiempoPreparacion = tiempo; }

    // Métodos para administrar ingredientes delegando a la lista
    bool agregarIngrediente(const Ingrediente& ing) {
        return listaIngredientes.insert(ing, listaIngredientes.lastPos() + 1);
    }
    
    // Métodos para administrar el procedimiento
    bool agregarPaso(const Paso& paso) {
        return procedimiento.insert(paso, procedimiento.lastPos() + 1);
    }

    void mostrarRecetaCompleta() const {
        std::cout << "\n=== " << nombre << " ===\n";
        std::cout << "Categoria: " << categoria << " | Autor: " << autor 
                  << " | Tiempo: " << tiempoPreparacion << " min\n";
        
        std::cout << "\nIngredientes:\n";
        for (int i = 0; i <= listaIngredientes.lastPos(); i++) {
            std::cout << listaIngredientes.retrieve(i) << "\n";
        }

        std::cout << "\nProcedimiento:\n";
        for (int i = 0; i <= procedimiento.lastPos(); i++) {
            std::cout << procedimiento.retrieve(i) << "\n";
        }
    }

    // Sobrecargas para permitir ordenamiento y búsqueda en el Recetario general
    bool operator==(const Receta& otra) const { return nombre == otra.nombre; }
    bool operator<(const Receta& otra) const { return nombre < otra.nombre; }
    bool operator>(const Receta& otra) const { return nombre > otra.nombre; }
};

#endif