#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <iostream>
#include <string>
// #include "Recetario.hpp" // Aquí incluiremos tu gestor cuando esté listo

class UserInterface {
private:
    void pausarPantalla();
    // Pantalla 2
    void menuVerRecetas();
    // Pantalla 3
    void menuAgregarReceta(); 
    // Pantalla 4
    void menuBuscarReceta();
    // Pantalla 5
    void menuAdministrarRecetas();
    // Pantalla 6
    void menuGuardarRecetario();
    // Pantalla 7
    void menuCargarRecetario();
    
public:
    // Pantalla 1 (Flujo Principal)
    void iniciarPrograma();
};

void UserInterface::pausarPantalla() {
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();    
}

void UserInterface::menuVerRecetas() {
        std::cout << "\n--- RECETAS ---\n";
        std::cout << "[1] Mostrar todas las recetas\n";
        std::cout << "[2] Filtrar por categoria\n";
        std::cout << "[3] Ordenar por nombre\n";
        std::cout << "[4] Ordenar por tiempo de preparacion\n";
        std::cout << "[0] Regresar al menu principal\n";
        // Aquí irá el sub-switch para esta pantalla
}

void UserInterface::menuAgregarReceta(){
    std::cout << "\n--- NUEVA RECETA ---\n";
    // Lógica para pedir datos, ingredientes y procedimiento
}

void UserInterface::menuBuscarReceta(){
    std::cout << "\n--- BUSCAR RECETA ---\n";
    std::cout << "¿Como desea buscar la receta?\n";
    std::cout << "[1] Buscar por nombre\n";
    std::cout << "[2] Buscar por categoria\n";
    std::cout << "[0] Regresar al menu principal\n";
        // Aquí irá el sub-switch para búsquedas
}

void UserInterface::menuAdministrarRecetas(){
    std::cout << "\n--- ADMINISTRAR RECETAS ---\n";
    std::cout << "[1] Modificar receta\n";
    std::cout << "[2] Eliminar receta\n";
    std::cout << "[3] Administrar ingredientes\n";
    std::cout << "[4] Eliminar todas las recetas\n";
    std::cout << "[0] Regresar al menu principal\n";
    // Aquí irá el sub-switch de administración
}

void UserInterface::menuGuardarRecetario(){
    std::cout << "\n--- GUARDAR RECETARIO ---\n";
    // Lógica para pedir nombre de archivo y guardar
}

void UserInterface::menuCargarRecetario(){
    std::cout << "\n--- CARGAR RECETARIO ---\n";
    // Lógica para mostrar archivos del directorio y cargar
}

void UserInterface::iniciarPrograma(){
    int opcion;
        do {
            std::cout << "\n=== RECETARIO DIGITAL ===\n";
            std::cout << "MENU PRINCIPAL\n";
            std::cout << "1. Ver recetas\n";
            std::cout << "2. Agregar receta\n";
            std::cout << "3. Buscar receta\n";
            std::cout << "4. Administrar recetas\n";
            std::cout << "5. Guardar recetario\n";
            std::cout << "6. Cargar recetario\n";
            std::cout << "0. Salir\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;

            // Limpiar el buffer después de leer el número para evitar saltos en los getline posteriores
            std::cin.ignore(256, '\n'); 

            switch (opcion) {
                case 1: 
                    menuVerRecetas(); 
                    break;
                case 2: 
                    menuAgregarReceta(); 
                    break;
                case 3: 
                    menuBuscarReceta(); 
                    break;
                case 4: 
                    menuAdministrarRecetas(); 
                    break;
                case 5: 
                    menuGuardarRecetario(); 
                    break;
                case 6: 
                    menuCargarRecetario(); 
                    break;
                case 0: 
                    std::cout << "Saliendo del programa...\n"; 
                    break;
                default: 
                    std::cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (opcion != 0);
}



#endif