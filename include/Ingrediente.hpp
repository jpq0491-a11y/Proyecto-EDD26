#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <string>
#include <iostream>

class Ingrediente {
private:
    std::string nombre;
    std::string cantidad;

public:
    Ingrediente() : nombre(""), cantidad("") {}
    Ingrediente(std::string n, std::string c) : nombre(n), cantidad(c) {}

    std::string getNombre() const { return nombre; }
    std::string getCantidad() const { return cantidad; }

    void setNombre(std::string n) { nombre = n; }
    void setCantidad(std::string c) { cantidad = c; }

    bool operator==(const Ingrediente& otro) const {
        return nombre == otro.nombre;
    }
    bool operator<(const Ingrediente& otro) const {
        return nombre < otro.nombre;
    }
    bool operator>(const Ingrediente& otro) const {
        return nombre > otro.nombre;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ingrediente& i) {
        os << "- " << i.nombre << ": " << i.cantidad;
        return os;
    }
};

#endif