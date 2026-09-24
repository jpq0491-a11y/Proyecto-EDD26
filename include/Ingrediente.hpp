#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <string>
#include <iostream>

class Ingrediente {
private:
    std::string nombre;
    std::string cantidad;

public:
    Ingrediente();
    Ingrediente(std::string n, std::string c);

    std::string getNombre() const;
    std::string getCantidad() const;

    void setNombre(std::string n);
    void setCantidad(std::string c);

    // Operadores requeridos por lista_2.hpp
    bool operator==(const Ingrediente& otro) const;
    bool operator<(const Ingrediente& otro) const;
    bool operator>(const Ingrediente& otro) const;

    friend std::ostream& operator<<(std::ostream& os, const Ingrediente& i);
};

#endif