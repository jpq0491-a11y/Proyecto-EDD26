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

    // Operadores de comparacion usados por List (busqueda y ordenamiento)
    bool operator==(const Ingrediente& otro) const;
    bool operator<(const Ingrediente& otro) const;
    bool operator>(const Ingrediente& otro) const;

    friend std::ostream& operator<<(std::ostream& os, const Ingrediente& i);
    // Deserializacion: lee "nombre" "cantidad" (formato del archivo de recetario)
    friend std::istream& operator>>(std::istream& is, Ingrediente& i);
};

#endif
