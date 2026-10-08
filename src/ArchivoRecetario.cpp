#include "ArchivoRecetario.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>

namespace {
const std::filesystem::path DIRECTORIO_RECETARIOS = "recetarios";

bool nombreValido(const std::string& nombre) {
    return !nombre.empty() && nombre.find_first_of("\\/:*?\"<>|") == std::string::npos;
}

std::filesystem::path rutaArchivo(const std::string& nombre) {
    std::string archivo = nombre;
    if (std::filesystem::path(archivo).extension() != ".txt") {
        archivo += ".txt";
    }
    return DIRECTORIO_RECETARIOS / archivo;
}
}

bool ArchivoRecetario::guardar(const Recetario& recetario, const std::string& nombreArchivo, std::string& mensaje) const {
    if (!nombreValido(nombreArchivo)) {
        mensaje = "El nombre del archivo no es valido.";
        return false;
    }
    std::error_code error;
    std::filesystem::create_directories(DIRECTORIO_RECETARIOS, error);
    if (error) {
        mensaje = "No se pudo crear el directorio de recetarios.";
        return false;
    }

    std::filesystem::path ruta = rutaArchivo(nombreArchivo);
    std::ofstream salida(ruta);
    if (!salida) {
        mensaje = "No se pudo abrir el archivo para escritura.";
        return false;
    }

    salida << "RECETARIO_V1\n" << recetario.cantidadRecetas() << '\n';
    for (int i = 0; i < recetario.cantidadRecetas(); ++i) {
        recetario.obtenerReceta(i).serializar(salida);
    }
    if (!salida) {
        mensaje = "Ocurrio un error al escribir el recetario.";
        return false;
    }
    mensaje = "Recetario guardado en " + ruta.string() + ".";
    return true;
}

bool ArchivoRecetario::cargar(const std::string& nombreArchivo, Recetario& recetario, std::string& mensaje) const {
    if (!nombreValido(nombreArchivo)) {
        mensaje = "El nombre del archivo no es valido.";
        return false;
    }
    std::ifstream entrada(rutaArchivo(nombreArchivo));
    std::string encabezado;
    int totalRecetas;
    if (!entrada || !(entrada >> encabezado >> totalRecetas) || encabezado != "RECETARIO_V1" || totalRecetas < 0 || totalRecetas > 50) {
        mensaje = "El archivo no tiene un formato de recetario valido.";
        return false;
    }

    Recetario cargado;
    for (int i = 0; i < totalRecetas; ++i) {
        Receta receta;
        if (!(entrada >> receta)) {
            mensaje = "El archivo contiene datos de receta invalidos.";
            return false;
        }
        if (!cargado.agregarReceta(receta)) {
            mensaje = "El archivo contiene recetas duplicadas.";
            return false;
        }
    }
    recetario = cargado;
    mensaje = "Recetario cargado correctamente.";
    return true;
}

std::vector<std::string> ArchivoRecetario::listarArchivos() const {
    std::vector<std::string> archivos;
    std::error_code error;
    if (!std::filesystem::exists(DIRECTORIO_RECETARIOS, error)) {
        return archivos;
    }
    for (const auto& entrada : std::filesystem::directory_iterator(DIRECTORIO_RECETARIOS, error)) {
        if (!error && entrada.is_regular_file() && entrada.path().extension() == ".txt") {
            archivos.push_back(entrada.path().filename().string());
        }
    }
    return archivos;
}
