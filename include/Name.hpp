#ifndef NAME_HPP
#define NAME_HPP

#include <string>
#include <iostream>

class Name {
private:
    std::string nombre;
    std::string apellido;

public:
    Name();
    Name(std::string n, std::string a);

    std::string getNombre() const;
    std::string getApellido() const;

    void setNombre(std::string n);
    void setApellido(std::string a);

    // Sobrecarga para imprimir directamente con cout
    friend std::ostream& operator<<(std::ostream& os, const Name& n);
    // Deserializacion: lee "nombre" "apellido" (formato del archivo de recetario)
    friend std::istream& operator>>(std::istream& is, Name& n);
};

#endif
