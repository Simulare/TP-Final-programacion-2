#include "menu.h"

usuario nuevoUsuario(nodoListaUsu* lista, nodoArbolDesa* arbol){
    usuario aux;
    char nombre[30];
    printf("\nNombre:");
    fflush(stdin);
    gets(nombre);
    if (buscarUsuarioPorNombre(lista, nombre) != NULL){
        printf("\n\nYa existe un usuario registrado con el nombre ingresado.\n\n");
        menuPrincipal(lista, arbol);
    }else{
        printf("\nContraseña (Máx. 15 caracteres) :");
        fflush(stdin);
        gets(aux.contraUsuario);
        aux.puntajeUsuario = 0;
        aux.ataqueUsuario = ATQ_BASE_USER;
        aux.vidaUsuario = HP_BASE_USER;
        aux.usuarioEliminado = 0;
        if (lista == NULL){ ///El primer usuario a registrar en la lista vacía es admin
            aux.categoriaUsuario = 'A';
        }else{
            aux.categoriaUsuario = 'J';
        }
    }

    return aux;
}

nodoListaUsu* logInUser (nodoListaUsu* lista, nodoArbolDesa* arbol){ ///Retorna el nodo del Usuario que se logeo
    char nombre[30];
    nodoListaUsu* nodo;
    printf("\nNombre: ");
    fflush(stdin);
    gets(nombre);
    nodo = buscarUsuarioPorNombre(lista, nombre);
    if (nodo == NULL){
        printf("\n\n----No existe ningún usuario registrado con el nombre ingresado.----\n\n");
        system("pause");
        menuPrincipal(lista, arbol);
    }else{
        char pass[15];
        printf("\nContraseña: ");
        fflush(stdin);
        gets(pass);
        if (strcmp(nodo->usuario.contraUsuario, pass) == 0){
            ///Menu para jugador.
        }else{
            printf("\n\n----Contraseña incorrecta.----\n\n");
            system("pause");
            menuPrincipal(lista, arbol);
        }
    }
    return nodo;
}

void pantallaPrincipal(){
    ///Pantalla titulo
    system("pause");
}

void menuPrincipal (nodoListaUsu* lista, nodoArbolDesa* arbol){
    system("cls");
    int op;
    printf("\nIngrese a su cuenta, si no tiene una registrese:\n\n\n1.Registrarse.\n2.Ingresar.\n3.Volver");
    fflush(stdin);
    scanf("%i", &op);
    usuario nuevo;
    system("cls");
    switch (op){
        case 1: ///Se carga a la lista y se guarda en el archivo.
            nuevo = nuevoUsuario(lista, arbol);
            agregarPpioUsuarioToLista(lista, crearNodoListaUsu(nuevo));
            guardarNuevoUsuArchivo(nuevo);
            printf("\n\n¡Su cuenta ha sido creada con éxito! Ingrese a su cuenta desde el menu principal\n\n");
            system ("pause");
            menuPrincipal(lista, arbol);
            break;
        case 2: ///Se loguea
            printf("\n\nIngrese los datos para acceder a su usuario:\n\n");
            nodoListaUsu* nodoUsuario = logInUser(lista, arbol);
            menuUsuario(lista, nodoUsuario, arbol);
            break;
        case 3: ///Volver
            pantallaPrincipal();
            break;
        default:
            printf("\n\nOpción incorrecta, intente de nuevo. \n\n\n");
            system("pause");
            menuPrincipal(lista, arbol);
            break;
    }
}

void menuUsuario (nodoListaUsu* lista, nodoListaUsu* nodoUsuario, nodoArbolDesa* arbol){  ///Hay que modificar si agregamos más
    system("cls");
    printf("\n\n1.Jugar.\n2.Ver ranking de puntajes.\n3.Salir del usuario\n");
    int op;
    fflush(stdin);
    scanf("%i", &op);
    switch (op){
    case 1:
        ///Función inicJuego (nodoListaUsu* nodoUsuario, nodoArbolDesa* arbol)
        break;
    case 2:
        ///Función mostrarUsuariosPorPuntaje
        break;
    case 3:
        menuPrincipal(lista, arbol);
        break;
        }
        ///MOSTRAR LAS OPCIONES QUE SALEN SI ES USUARIO ADMIN--------
}

void iniciarPrograma (){ ///Hay que cargar las estructuras desde los archivos cuando se inicia
    nodoListaUsu* lista = inicListaUsu();
    lista = pasarUsuariosArchivoToLista(lista);
    nodoArbolDesa* arbol = inicArbolDesafio();
    arbol = pasarDesafiosArchivoToArbol(arbol);
    pantallaPrincipal();
    menuPrincipal(lista, arbol);
}
