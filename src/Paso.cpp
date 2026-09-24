#include "Paso.hpp"

Paso::Paso() : numero(0), instruccion("") {}

Paso::Paso(int num, std::string inst) : numero(num), instruccion(inst) {}

int Paso::getNumero() const { return numero; }
std::string Paso::getInstruccion() const { return instruccion; }

void Paso::setNumero(int num) { numero = num; }
void Paso::setInstruccion(std::string inst) { instruccion = inst; }

bool Paso::operator==(const Paso& otro) const { return numero == otro.numero; }
bool Paso::operator<(const Paso& otro) const { return numero < otro.numero; }
bool Paso::operator>(const Paso& otro) const { return numero > otro.numero; }

std::ostream& operator<<(std::ostream& os, const Paso& p) {
    os << p.instruccion; // Imprime solo la instrucción, el número ya se maneja en el formato
    return os;
}