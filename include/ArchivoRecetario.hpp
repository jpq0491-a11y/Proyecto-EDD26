#ifndef ARCHIVO_RECETARIO_HPP
#define ARCHIVO_RECETARIO_HPP

#include "Recetario.hpp"
#include <string>
#include <vector>

class ArchivoRecetario {
public:
    bool guardar(const Recetario& recetario, const std::string& nombreArchivo, std::string& mensaje) const;
    bool cargar(const std::string& nombreArchivo, Recetario& recetario, std::string& mensaje) const;
    std::vector<std::string> listarArchivos() const;
};

#endif
