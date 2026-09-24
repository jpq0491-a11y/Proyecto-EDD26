#include "Ingrediente.hpp"

Ingrediente::Ingrediente() : nombre(""), cantidad("") {}

Ingrediente::Ingrediente(std::string n, std::string c) : nombre(n), cantidad(c) {}

std::string Ingrediente::getNombre() const { return nombre; }
std::string Ingrediente::getCantidad() const { return cantidad; }

void Ingrediente::setNombre(std::string n) { nombre = n; }
void Ingrediente::setCantidad(std::string c) { cantidad = c; }

bool Ingrediente::operator==(const Ingrediente& otro) const { 
    return nombre == otro.nombre; 
}
bool Ingrediente::operator<(const Ingrediente& otro) const { 
    return nombre < otro.nombre; 
}
bool Ingrediente::operator>(const Ingrediente& otro) const { 
    return nombre > otro.nombre; 
}

std::ostream& operator<<(std::ostream& os, const Ingrediente& i) {
    os << i.nombre << ": " << i.cantidad;
    return os;
}