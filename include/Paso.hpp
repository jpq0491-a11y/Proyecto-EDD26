#ifndef PASO_HPP
#define PASO_HPP

#include <string>
#include <iostream>

class Paso {
private:
    int numero;
    std::string instruccion;

public:
    Paso();
    Paso(int num, std::string inst);

    int getNumero() const;
    std::string getInstruccion() const;

    void setNumero(int num);
    void setInstruccion(std::string inst);

    // Operadores requeridos por lista_2.hpp
    bool operator==(const Paso& otro) const;
    bool operator<(const Paso& otro) const;
    bool operator>(const Paso& otro) const;

    friend std::ostream& operator<<(std::ostream& os, const Paso& p);
};

#endif