#include "Name.hpp"
#include <iomanip>

Name::Name() : nombre(""), apellido("") {}

Name::Name(std::string n, std::string a) : nombre(n), apellido(a) {}

std::string Name::getNombre() const { return nombre; }
std::string Name::getApellido() const { return apellido; }

void Name::setNombre(std::string n) { nombre = n; }
void Name::setApellido(std::string a) { apellido = a; }

std::ostream& operator<<(std::ostream& os, const Name& n) {
    os << n.nombre << " " << n.apellido;
    return os;
}

void Name::serializar(std::ostream& os) const {
    os << std::quoted(nombre) << ' ' << std::quoted(apellido);
}

std::istream& operator>>(std::istream& is, Name& n) {
    std::string nombre, apellido;
    if (is >> std::quoted(nombre) >> std::quoted(apellido)) {
        n.nombre = nombre;
        n.apellido = apellido;
    }
    return is;
}
