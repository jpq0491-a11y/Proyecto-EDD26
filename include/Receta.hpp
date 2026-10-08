#ifndef RECETA_HPP
#define RECETA_HPP

#include <string>
#include "lista.hpp"
#include "Ingrediente.hpp"
#include "Paso.hpp"
#include "Name.hpp"
#include <iostream>

class Receta {
private:
    std::string nombre;
    std::string categoria;
    Name autor;
    int tiempoPreparacion;
    List<Ingrediente, 50> listaIngredientes; // Plantilla de ingredientes
    List<Paso, 50> procedimiento;            // Plantilla de pasos

public:
    // Constructores
    Receta();
    Receta(std::string n, std::string cat, Name aut, int tiempo);

    // Getters y Setters
    std::string getNombre() const;
    std::string getCategoria() const;
    Name getAutor() const;
    int getTiempoPreparacion() const;

    void setNombre(std::string n);
    void setCategoria(std::string cat);
    void setAutor(Name aut);
    void setTiempoPreparacion(int tiempo);

    // Métodos para interactuar con las listas
    bool agregarIngrediente(const Ingrediente& ing);
    bool agregarPaso(const Paso& paso);
    bool eliminarIngrediente(int indice);
    bool eliminarPaso(int indice);
    bool modificarIngrediente(int indice, const Ingrediente& ingrediente);
    bool modificarPaso(int indice, const Paso& paso);
    void vaciarIngredientes();
    void vaciarPasos();
    int cantidadIngredientes() const;
    int cantidadPasos() const;
    Ingrediente obtenerIngrediente(int indice) const;
    Paso obtenerPaso(int indice) const;

    // Visualización
    void mostrarIngredientes() const;

    void mostrarRecetaCompleta() const;

    // Sobrecargas para ordenamientos
    bool operator==(const Receta& otra) const;
    bool operator<(const Receta& otra) const;
    bool operator>(const Receta& otra) const;

    // Deserializacion: lee una receta completa (datos, ingredientes y pasos)
    // en el formato del archivo de recetario. Si los datos son invalidos, activa failbit.
    friend std::istream& operator>>(std::istream& is, Receta& r);
};

#endif
