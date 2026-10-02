#include "UserInterface.hpp"
#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    // Los textos del programa estan en UTF-8: la consola de Windows debe usar la misma
    // codificacion para mostrar bien la ñ y los acentos, tanto al imprimir como al leer.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    UserInterface menuPrincipal;
    menuPrincipal.iniciarPrograma();
    return 0;
}
