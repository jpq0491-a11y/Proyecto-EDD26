#include "Receta.hpp"

// Constructores
Receta::Receta() : nombre(""), categoria(""), tiempoPreparacion(0) {}

Receta::Receta(std::string n, std::string cat, Name aut, int tiempo) 
    : nombre(n), categoria(cat), autor(aut), tiempoPreparacion(tiempo) {}

// Getters
std::string Receta::getNombre() const { return nombre; }
std::string Receta::getCategoria() const { return categoria; }
Name Receta::getAutor() const { return autor; }
int Receta::getTiempoPreparacion() const { return tiempoPreparacion; }

// Setters
void Receta::setNombre(std::string n) { nombre = n; }
void Receta::setCategoria(std::string cat) { categoria = cat; }
void Receta::setAutor(Name aut) { autor = aut; }
void Receta::setTiempoPreparacion(int tiempo) { tiempoPreparacion = tiempo; }

// Administración de listas
bool Receta::agregarIngrediente(const Ingrediente& ing) {
    return listaIngredientes.insert(ing, listaIngredientes.lastPos() + 1);
}

bool Receta::agregarPaso(const Paso& paso) {
    return procedimiento.insert(paso, procedimiento.lastPos() + 1);
}

// IMPLEMENTACIÓN QUE SOLUCIONA TU ERROR
void Receta::mostrarIngredientes() const {
    if (listaIngredientes.isEmpty()) {
        std::cout << "  No hay ingredientes agregados.\n";
        return;
    }
    // Iteramos sobre la lista de ingredientes usando la lógica de lista_2.hpp
    for (int i = 0; i <= listaIngredientes.lastPos(); i++) {
        // Al imprimir "listaIngredientes.retrieve(i)", se invoca automáticamente 
        // la sobrecarga operator<< de tu clase Ingrediente
        std::cout << i + 1 << ". " << listaIngredientes.retrieve(i) << "\n";
    }
}

void Receta::mostrarRecetaCompleta() const {
    std::cout << "\n=== " << nombre << " ===\n";
    std::cout << "Categoria: " << categoria << " | Autor: " << autor 
              << " | Tiempo: " << tiempoPreparacion << " min\n";
    
    std::cout << "\nIngredientes:\n";
    mostrarIngredientes();

    std::cout << "\nProcedimiento:\n";
    for (int i = 0; i <= procedimiento.lastPos(); i++) {
        std::cout << procedimiento.retrieve(i) << "\n";
    }
}

// Sobrecargas
bool Receta::operator==(const Receta& otra) const { return nombre == otra.nombre; }
bool Receta::operator<(const Receta& otra) const { return nombre < otra.nombre; }
bool Receta::operator>(const Receta& otra) const { return nombre > otra.nombre; }