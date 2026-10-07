#include "Receta.hpp"
#include <iomanip>

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

bool Receta::eliminarIngrediente(int indice) { return listaIngredientes.remove(indice); }
bool Receta::eliminarPaso(int indice) { return procedimiento.remove(indice); }

bool Receta::modificarIngrediente(int indice, const Ingrediente& ingrediente) {
    if (indice < 0 || indice >= cantidadIngredientes()) return false;
    listaIngredientes.remove(indice);
    return listaIngredientes.insert(ingrediente, indice);
}

bool Receta::modificarPaso(int indice, const Paso& paso) {
    if (indice < 0 || indice >= cantidadPasos()) return false;
    procedimiento.remove(indice);
    return procedimiento.insert(paso, indice);
}

void Receta::vaciarIngredientes() { listaIngredientes.clear(); }
void Receta::vaciarPasos() { procedimiento.clear(); }
int Receta::cantidadIngredientes() const { return listaIngredientes.lastPos() + 1; }
int Receta::cantidadPasos() const { return procedimiento.lastPos() + 1; }
Ingrediente Receta::obtenerIngrediente(int indice) const { return listaIngredientes.retrieve(indice); }
Paso Receta::obtenerPaso(int indice) const { return procedimiento.retrieve(indice); }

// Muestra los ingredientes numerados desde 1
void Receta::mostrarIngredientes() const {
    if (listaIngredientes.isEmpty()) {
        std::cout << "  No hay ingredientes agregados.\n";
        return;
    }
    for (int i = 0; i <= listaIngredientes.lastPos(); i++) {
        // Usa la sobrecarga operator<< de Ingrediente
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
    if (procedimiento.isEmpty()) {
        std::cout << "  No hay pasos agregados.\n";
        return;
    }
    for (int i = 0; i <= procedimiento.lastPos(); i++) {
        std::cout << i + 1 << ". " << procedimiento.retrieve(i) << "\n";
    }
}

// Sobrecargas
bool Receta::operator==(const Receta& otra) const { return nombre == otra.nombre; }
bool Receta::operator<(const Receta& otra) const { return nombre < otra.nombre; }
bool Receta::operator>(const Receta& otra) const { return nombre > otra.nombre; }


// Deserializacion: la receta solo se modifica si se leyo completa y valida
std::istream& operator>>(std::istream& is, Receta& r) {
    std::string nombre, categoria;
    Name autor;
    int tiempo, totalIngredientes, totalPasos;
    if (!(is >> std::quoted(nombre) >> std::quoted(categoria) >> autor >> tiempo >> totalIngredientes) ||
        tiempo <= 0 || totalIngredientes < 0 || totalIngredientes > 50) {
        is.setstate(std::ios::failbit);
        return is;
    }
    Receta leida(nombre, categoria, autor, tiempo);
    for (int j = 0; j < totalIngredientes; ++j) {
        Ingrediente ingrediente;
        if (!(is >> ingrediente) || !leida.agregarIngrediente(ingrediente)) {
            is.setstate(std::ios::failbit);
            return is;
        }
    }
    if (!(is >> totalPasos) || totalPasos < 0 || totalPasos > 50) {
        is.setstate(std::ios::failbit);
        return is;
    }
    for (int j = 0; j < totalPasos; ++j) {
        Paso paso;
        if (!(is >> paso) || !leida.agregarPaso(paso)) {
            is.setstate(std::ios::failbit);
            return is;
        }
    }
    r = leida;
    return is;
}