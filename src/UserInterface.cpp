#include "UserInterface.hpp"
#include <limits>

namespace {
bool leerEntero(int& valor) {
    if (std::cin >> valor) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Entrada invalida. Escribe un numero.\n";
    return false;
}

bool leerRespuestaSiNo(char& respuesta) {
    std::cin >> respuesta;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    respuesta = static_cast<char>(std::toupper(static_cast<unsigned char>(respuesta)));
    if (respuesta != 'S' && respuesta != 'N') {
        std::cout << "Respuesta invalida. Escribe S o N.\n";
        return false;
    }
    return true;
}

std::string leerTextoNoVacio(const std::string& mensaje) {
    std::string texto;
    do {
        std::cout << mensaje;
        std::getline(std::cin, texto);
        if (texto.empty()) std::cout << "Este dato no puede quedar vacio.\n";
    } while (texto.empty());
    return texto;
}

std::string seleccionarCategoria(bool permitirCancelar) {
    int opcion;
    do {
        std::cout << "[1] Desayuno\n[2] Comida\n[3] Cena\n[4] Navideño\n";
        if (permitirCancelar) std::cout << "[0] Regresar\n";
        std::cout << "> ";
        if (!leerEntero(opcion)) continue;
        switch (opcion) {
            case 1: return "Desayuno";
            case 2: return "Comida";
            case 3: return "Cena";
            case 4: return "Navideño";
            case 0: if (permitirCancelar) return ""; break;
        }
        std::cout << "Opcion invalida.\n";
    } while (true);
}

int seleccionarIndice(const Recetario& recetario, const std::string& mensaje) {
    if (recetario.estaVacio()) {
        std::cout << "El recetario esta vacio.\n";
        return -1;
    }
    recetario.mostrarTodas();
    int opcion;
    do {
        std::cout << mensaje << " (0 para regresar): ";
        if (!leerEntero(opcion)) continue;
        if (opcion == 0) return -1;
        if (opcion >= 1 && opcion <= recetario.cantidadRecetas()) return opcion - 1;
        std::cout << "Indice invalido.\n";
    } while (true);
}
}

UserInterface::UserInterface() {
    // Constructor vacío por el momento
}

void UserInterface::pausarPantalla() {
    std::cout << "\nPresiona Enter para continuar...";
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
        if (!leerEntero(opcion)) {
            pausarPantalla();
            continue;
        }

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
    int tiempo;
    limpiarPantalla();
    std::cout << "\n=== RECETARIO DIGITAL ===\n";
    std::cout << "== NUEVA RECETA ==\n";
    std::cout << "Datos de la receta:\n";
    
    nombreReceta = leerTextoNoVacio("Nombre del platillo:\n> ");
    limpiarPantalla();
    std::cout << "Categoria:\n";
    catStr = seleccionarCategoria(false);

    limpiarPantalla();
    std::cout << "===Autor===\n";
    autorNombre = leerTextoNoVacio("Nombres:\n> ");
    autorApellido = leerTextoNoVacio("Apellidos:\n> ");
    Name autor(autorNombre, autorApellido);

    limpiarPantalla();
    do {
        std::cout << "Tiempo de preparacion (minutos):\n> ";
    } while (!leerEntero(tiempo) || tiempo <= 0);

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
        if (!nuevaReceta.agregarIngrediente(ing)) {
            std::cout << "No se pueden agregar mas de 50 ingredientes.\n";
            break;
        }

        do {
            std::cout << "¿Agregar otro ingrediente? (S/N): ";
        } while (!leerRespuestaSiNo(respuesta));
    } while (respuesta == 'S');

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
        if (!nuevaReceta.agregarPaso(p)) {
            std::cout << "No se pueden agregar mas de 50 pasos.\n";
            break;
        }
        numPaso++;

        do {
            std::cout << "¿Agregar otro paso? (S/N): ";
        } while (!leerRespuestaSiNo(respuesta));
    } while (respuesta == 'S');

    int confirmacion;
    std::cout << "\n[1] Guardar receta\n[0] Cancelar\nSeleccione una opcion: ";
    while (!leerEntero(confirmacion) || (confirmacion != 0 && confirmacion != 1)) {
        std::cout << "Selecciona 1 para guardar o 0 para cancelar: ";
    }

    if (confirmacion == 1) {
        std::string mensaje;
        gestorRecetas.agregarReceta(nuevaReceta, mensaje);
        std::cout << "\n" << mensaje << "\n";
    } else {
        std::cout << "\nOperacion cancelada.\n";
    }
    
    pausarPantalla();
}

void UserInterface::mostrarRecetasYSeleccionar() {
    const Recetario& recetario = gestorRecetas.obtenerRecetario();
    int indice = seleccionarIndice(recetario, "Selecciona una receta para ver el detalle");
    if (indice != -1) recetario.obtenerReceta(indice).mostrarRecetaCompleta();
    pausarPantalla();
}

void UserInterface::menuVerRecetas() {
    int opcion;
    do {
        limpiarPantalla();
        std::cout << "=== RECETAS ===\n1. Mostrar todas\n2. Filtrar por categoria\n3. Ordenar por nombre\n4. Ordenar por tiempo\n0. Regresar\n> ";
        if (!leerEntero(opcion)) { pausarPantalla(); continue; }
        switch (opcion) {
            case 1: mostrarRecetasYSeleccionar(); break;
            case 2: {
                limpiarPantalla();
                std::cout << "Elige una categoria:\n";
                std::string categoria = seleccionarCategoria(true);
                if (!categoria.empty()) {
                    const Recetario& recetario = gestorRecetas.obtenerRecetario();
                    recetario.filtrarPorCategoria(categoria);
                    int indice = seleccionarIndice(recetario, "Selecciona una receta para ver el detalle");
                    if (indice != -1 && recetario.obtenerReceta(indice).getCategoria() == categoria) recetario.obtenerReceta(indice).mostrarRecetaCompleta();
                    pausarPantalla();
                }
                break;
            }
            case 3: gestorRecetas.ordenarPorNombre(); mostrarRecetasYSeleccionar(); break;
            case 4: gestorRecetas.ordenarPorTiempo(); mostrarRecetasYSeleccionar(); break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n"; pausarPantalla();
        }
    } while (opcion != 0);
}

void UserInterface::menuBuscarReceta() {
    int opcion;
    do {
        limpiarPantalla();
        std::cout << "=== BUSCAR RECETA ===\n1. Por nombre\n2. Por categoria\n0. Regresar\n> ";
        if (!leerEntero(opcion)) { pausarPantalla(); continue; }
        const Recetario& recetario = gestorRecetas.obtenerRecetario();
        if (opcion == 1) {
            std::string nombre = leerTextoNoVacio("Nombre de la receta:\n> ");
            int indice = recetario.buscarPorNombre(nombre);
            if (indice == -1) std::cout << "No se encontro una receta con ese nombre.\n";
            else recetario.obtenerReceta(indice).mostrarRecetaCompleta();
            pausarPantalla();
        } else if (opcion == 2) {
            std::cout << "Elige una categoria:\n";
            std::string categoria = seleccionarCategoria(true);
            if (!categoria.empty()) {
                recetario.filtrarPorCategoria(categoria);
                pausarPantalla();
            }
        } else if (opcion != 0) {
            std::cout << "Opcion invalida.\n";
            pausarPantalla();
        }
    } while (opcion != 0);
}

void UserInterface::modificarReceta(int indiceReceta) {
    Receta receta = gestorRecetas.obtenerRecetario().obtenerReceta(indiceReceta);
    int opcion;
    do {
        limpiarPantalla();
        receta.mostrarRecetaCompleta();
        std::cout << "\n1. Modificar nombre\n2. Modificar categoria\n3. Modificar autor\n4. Modificar tiempo\n5. Modificar procedimiento\n6. Guardar cambios\n0. Cancelar\n> ";
        if (!leerEntero(opcion)) { pausarPantalla(); continue; }
        if (opcion == 1) receta.setNombre(leerTextoNoVacio("Nuevo nombre:\n> "));
        else if (opcion == 2) { std::cout << "Nueva categoria:\n"; receta.setCategoria(seleccionarCategoria(false)); }
        else if (opcion == 3) receta.setAutor(Name(leerTextoNoVacio("Nombres:\n> "), leerTextoNoVacio("Apellidos:\n> ")));
        else if (opcion == 4) {
            int tiempo;
            do { std::cout << "Nuevo tiempo en minutos:\n> "; } while (!leerEntero(tiempo) || tiempo <= 0);
            receta.setTiempoPreparacion(tiempo);
        } else if (opcion == 5) {
            int accion;
            do {
                limpiarPantalla();
                receta.mostrarRecetaCompleta();
                std::cout << "\n1. Agregar paso\n2. Eliminar paso\n3. Modificar paso\n4. Eliminar todos los pasos\n0. Regresar\n> ";
                if (!leerEntero(accion)) continue;
                if (accion == 1) {
                    if (!receta.agregarPaso(Paso(receta.cantidadPasos() + 1, leerTextoNoVacio("Descripcion:\n> ")))) {
                        std::cout << "Se alcanzo el limite de 50 pasos.\n";
                        pausarPantalla();
                    }
                }
                else if (accion == 2 || accion == 3) {
                    int indice;
                    std::cout << "Numero de paso (0 para cancelar): ";
                    bool indiceLeido = leerEntero(indice);
                    if (indiceLeido && indice > 0 && indice <= receta.cantidadPasos()) {
                        if (accion == 2) receta.eliminarPaso(indice - 1);
                        else receta.modificarPaso(indice - 1, Paso(indice, leerTextoNoVacio("Nueva descripcion:\n> ")));
                    } else if (indiceLeido && indice != 0) std::cout << "Paso invalido.\n";
                } else if (accion == 4) {
                    char respuesta;
                    do { std::cout << "¿Eliminar todos los pasos? (S/N): "; } while (!leerRespuestaSiNo(respuesta));
                    if (respuesta == 'S') receta.vaciarPasos();
                }
            } while (accion != 0);
        } else if (opcion == 6) {
            std::string mensaje;
            gestorRecetas.reemplazarReceta(indiceReceta, receta, mensaje);
            std::cout << mensaje << "\n";
            pausarPantalla();
            return;
        } else if (opcion != 0) { std::cout << "Opcion invalida.\n"; pausarPantalla(); }
    } while (opcion != 0);
}

void UserInterface::administrarIngredientes(int indiceReceta) {
    Receta receta = gestorRecetas.obtenerRecetario().obtenerReceta(indiceReceta);
    int opcion;
    do {
        limpiarPantalla();
        std::cout << "=== INGREDIENTES DE " << receta.getNombre() << " ===\n";
        receta.mostrarIngredientes();
        std::cout << "\n1. Agregar ingrediente\n2. Eliminar ingrediente\n3. Eliminar todos\n4. Modificar cantidad\n0. Guardar y regresar\n> ";
        if (!leerEntero(opcion)) continue;
        if (opcion == 1) {
            Ingrediente ingrediente(leerTextoNoVacio("Ingrediente:\n> "), leerTextoNoVacio("Cantidad:\n> "));
            if (!receta.agregarIngrediente(ingrediente)) std::cout << "Se alcanzo el limite de 50 ingredientes.\n";
        } else if (opcion == 2 || opcion == 4) {
            int indice;
            std::cout << "Numero de ingrediente (0 para cancelar): ";
            bool indiceLeido = leerEntero(indice);
            if (indiceLeido && indice > 0 && indice <= receta.cantidadIngredientes()) {
                if (opcion == 2) receta.eliminarIngrediente(indice - 1);
                else {
                    Ingrediente anterior = receta.obtenerIngrediente(indice - 1);
                    receta.modificarIngrediente(indice - 1, Ingrediente(anterior.getNombre(), leerTextoNoVacio("Nueva cantidad:\n> ")));
                }
            } else if (indiceLeido && indice != 0) std::cout << "Ingrediente invalido.\n";
        } else if (opcion == 3) {
            char respuesta;
            do { std::cout << "¿Eliminar todos los ingredientes? (S/N): "; } while (!leerRespuestaSiNo(respuesta));
            if (respuesta == 'S') receta.vaciarIngredientes();
        } else if (opcion != 0) std::cout << "Opcion invalida.\n";
    } while (opcion != 0);
    std::string mensaje;
    gestorRecetas.reemplazarReceta(indiceReceta, receta, mensaje);
    std::cout << mensaje << "\n";
    pausarPantalla();
}

void UserInterface::menuAdministrarRecetas() {
    int opcion;
    do {
        limpiarPantalla();
        std::cout << "=== ADMINISTRAR RECETAS ===\n1. Modificar receta\n2. Eliminar receta\n3. Administrar ingredientes\n4. Eliminar todas las recetas\n0. Regresar\n> ";
        if (!leerEntero(opcion)) { pausarPantalla(); continue; }
        if (opcion >= 1 && opcion <= 3) {
            int indice = seleccionarIndice(gestorRecetas.obtenerRecetario(), "Selecciona una receta");
            if (indice == -1) { pausarPantalla(); continue; }
            if (opcion == 1) modificarReceta(indice);
            else if (opcion == 2) {
                char respuesta;
                do { std::cout << "¿Eliminar esta receta? (S/N): "; } while (!leerRespuestaSiNo(respuesta));
                if (respuesta == 'S') { std::string mensaje; gestorRecetas.eliminarReceta(indice, mensaje); std::cout << mensaje << "\n"; }
                pausarPantalla();
            } else administrarIngredientes(indice);
        } else if (opcion == 4) {
            char respuesta;
            do { std::cout << "Esta accion eliminara todo el recetario. ¿Continuar? (S/N): "; } while (!leerRespuestaSiNo(respuesta));
            if (respuesta == 'S') { gestorRecetas.vaciarRecetario(); std::cout << "Recetario eliminado.\n"; }
            pausarPantalla();
        } else if (opcion != 0) { std::cout << "Opcion invalida.\n"; pausarPantalla(); }
    } while (opcion != 0);
}

void UserInterface::menuGuardarRecetario() {
    limpiarPantalla();
    int cantidad = gestorRecetas.obtenerRecetario().cantidadRecetas();
    std::cout << "Se guardaran " << cantidad << " recetas.\n";
    std::string nombre = leerTextoNoVacio("Nombre del archivo:\n> ");
    char respuesta;
    do { std::cout << "¿Guardar recetario? (S/N): "; } while (!leerRespuestaSiNo(respuesta));
    if (respuesta == 'S') { std::string mensaje; gestorRecetas.guardar(nombre, mensaje); std::cout << mensaje << "\n"; }
    else std::cout << "Operacion cancelada.\n";
    pausarPantalla();
}

void UserInterface::menuCargarRecetario() {
    limpiarPantalla();
    std::vector<std::string> archivos = gestorRecetas.archivosDisponibles();
    if (archivos.empty()) { std::cout << "No hay archivos de recetario disponibles.\n"; pausarPantalla(); return; }
    std::cout << "=== RECETARIOS DISPONIBLES ===\n";
    for (std::size_t i = 0; i < archivos.size(); ++i) std::cout << i + 1 << ". " << archivos[i] << "\n";
    int opcion;
    do { std::cout << "Selecciona un archivo (0 para cancelar): "; } while (!leerEntero(opcion) || opcion < 0 || opcion > static_cast<int>(archivos.size()));
    if (opcion == 0) return;
    char respuesta;
    do { std::cout << "Cargar este recetario reemplazara el actual. ¿Continuar? (S/N): "; } while (!leerRespuestaSiNo(respuesta));
    if (respuesta == 'S') { std::string mensaje; gestorRecetas.cargar(archivos[opcion - 1], mensaje); std::cout << mensaje << "\n"; }
    else std::cout << "Operacion cancelada.\n";
    pausarPantalla();
}

void UserInterface::limpiarPantalla() {
    std::cout << "\x1B[2J\x1B[H";
}
