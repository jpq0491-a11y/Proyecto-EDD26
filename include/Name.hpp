#ifndef NAME_HPP
#define NAME_HPP

#include <string>
#include <iostream>

class Name {
private:
    std::string nombre;
    std::string apellido;

public:
    Name() : nombre(""), apellido("") {}
    Name(std::string n, std::string a) : nombre(n), apellido(a) {}

    std::string getNombre() const { 
        return nombre; 
    }
    std::string getApellido() const { 
        return apellido; 
    }

    void setNombre(std::string n) { 
        nombre = n; 
    }
    void setApellido(std::string a) { 
        apellido = a; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Name& n) {
        os << n.nombre << " " << n.apellido;
        return os;
    }
};

#endif