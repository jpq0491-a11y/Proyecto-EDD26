#include "Name.hpp"

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