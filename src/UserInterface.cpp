#include "UserInterface.hpp"

UserInterface::UserInterface() {
    // Constructor vacío por el momento
}

void UserInterface::pausarPantalla() {
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void UserInterface::iniciarPrograma() {
    std::setlocale(LC_ALL, ""); 
    int opcion;
    do {
        limpiarPantalla();
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
        std::cin.ignore(256, '\n'); 

        switch (opcion) {
            case 1: menuVerRecetas(); break;
            case 2: menuAgregarReceta(); break;
            case 3: menuBuscarReceta(); break;
            case 4: menuAdministrarRecetas(); break;
            case 5: menuGuardarRecetario(); break;
            case 6: menuCargarRecetario(); break;
            case 0: std::cout << "Saliendo del programa...\n"; break;
            default: std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
}

void UserInterface::menuAgregarReceta() {
    std::setlocale(LC_ALL, ""); 
    std::string nombreReceta, autorNombre, autorApellido, catStr;
    int categoriaOpcion, tiempo;
    limpiarPantalla();
    std::cout << "\nRECETARIO DIGITAL\n";
    std::cout << "NUEVA RECETA\n";
    std::cout << "DATOS DE LA RECETA\n";
    
    std::cout << "Nombre del platillo:\n> ";
    std::getline(std::cin, nombreReceta);
    limpiarPantalla();
    std::cout << "Categoria:\n";
    std::cout << "[1] Desayuno\n[2] Comida\n[3] Cena\n[4] Navideño\n> ";
    std::cin >> categoriaOpcion;
    std::cin.ignore(256, '\n'); 
    switch(categoriaOpcion) {
        case 1: catStr = "Desayuno"; break;
        case 2: catStr = "Comida"; break;
        case 3: catStr = "Cena"; break;
        case 4: catStr = "Navideño"; break;
        default: catStr = "Sin Categoria"; break;
    }

    limpiarPantalla();
    std::cout << "===Autor===\n";
    std::cout << "Nombres:\n> ";
    std::getline(std::cin, autorNombre);
    std::cout << "Apellidos:\n> ";
    std::getline(std::cin, autorApellido);
    Name autor(autorNombre, autorApellido);

    limpiarPantalla();
    std::cout << "Tiempo de preparacion (minutos):\n> ";
    std::cin >> tiempo;
    std::cin.ignore(256, '\n');

    Receta nuevaReceta(nombreReceta, catStr, autor, tiempo);

    limpiarPantalla();
    std::cout << "\nINGREDIENTES\n";
    char respuesta;
    do {
        std::string nomIng, cantIng;
        std::cout << "Ingrediente:\n> ";
        std::getline(std::cin, nomIng);
        std::cout << "Cantidad:\n> ";
        std::getline(std::cin, cantIng);

        Ingrediente ing(nomIng, cantIng);
        nuevaReceta.agregarIngrediente(ing); 

        std::cout << "¿Agregar otro ingrediente? (S/N): ";
        std::cin >> respuesta;
        std::cin.ignore(256, '\n');
    } while (toupper(respuesta) == 'S');

    std::cout << "\nIngredientes agregados:\n";
    nuevaReceta.mostrarIngredientes(); 

    limpiarPantalla();
    std::cout << "\nPROCEDIMIENTO\n";
    int numPaso = 1;
    do {
        std::string descPaso;
        std::cout << "Paso " << numPaso << ":\n> ";
        std::getline(std::cin, descPaso);

        Paso p(numPaso, descPaso);
        nuevaReceta.agregarPaso(p);
        numPaso++;

        std::cout << "¿Agregar otro paso? (S/N): ";
        std::cin >> respuesta;
        std::cin.ignore(256, '\n');
    } while (toupper(respuesta) == 'S');

    int confirmacion;
    std::cout << "\n[1] Guardar receta\n[0] Cancelar\nSeleccione una opcion: ";
    std::cin >> confirmacion;
    std::cin.ignore(256, '\n');

    if (confirmacion == 1) {
        gestorRecetas.agregarReceta(nuevaReceta);
        std::cout << "\n¡Receta guardada con exito!\n";
    } else {
        std::cout << "\nOperacion cancelada.\n";
    }
    
    pausarPantalla();
}

// Métodos pendientes por desarrollar
void UserInterface::menuVerRecetas() { std::cout << "En construccion...\n"; pausarPantalla(); }
void UserInterface::menuBuscarReceta() { std::cout << "En construccion...\n"; pausarPantalla(); }
void UserInterface::menuAdministrarRecetas() { std::cout << "En construccion...\n"; pausarPantalla(); }
void UserInterface::menuGuardarRecetario() { std::cout << "En construccion...\n"; pausarPantalla(); }
void UserInterface::menuCargarRecetario() { std::cout << "En construccion...\n"; pausarPantalla(); }

void UserInterface::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}