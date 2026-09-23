#ifndef PASO_HPP
#define PASO_HPP

#include <string>
#include <iostream>

class Paso {
private:
    int numero;
    std::string instruccion;

public:
    Paso() : numero(0), instruccion("") {}
    Paso(int num, std::string inst) : numero(num), instruccion(inst) {}

    int getNumero() const { 
        return numero; 
    }
    std::string getInstruccion() const { 
        return instruccion; 
    }

    void setNumero(int num) { 
        numero = num; 
    }
    void setInstruccion(std::string inst) { 
        instruccion = inst; 
    }

    bool operator==(const Paso& otro) const { 
        return numero == otro.numero; 
    }
    bool operator>(const Paso& otro) const { 
        return numero > otro.numero; 
    }
    bool operator<(const Paso& otro) const { 
        return numero < otro.numero; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Paso& p) {
        os << "Paso " << p.numero << ": " << p.instruccion;
        return os;
    }
};

#endif