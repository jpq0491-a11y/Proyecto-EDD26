#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "ServicioRecetario.hpp"
#include "Name.hpp"
#include "Ingrediente.hpp"
#include "Paso.hpp"
#include <iostream>
#include <string>
#include <cctype> // Para la función toupper()
#include <locale> // Para la función setlocale()

class UserInterface {
private:
    ServicioRecetario gestorRecetas;

    // Métodos privados para uso interno de la interfaz
    void pausarPantalla();
    void menuVerRecetas();
    void menuAgregarReceta();
    void menuBuscarReceta();
    void menuAdministrarRecetas();
    void menuGuardarRecetario();
    void menuCargarRecetario();
    void mostrarRecetasYSeleccionar();
    void administrarIngredientes(int indiceReceta);
    void modificarReceta(int indiceReceta);
    void limpiarPantalla();

public:
    UserInterface(); // Constructor
    void iniciarPrograma(); // Único método público para arrancar desde el main
};

#endif
