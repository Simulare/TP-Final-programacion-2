#include "menu.h"


void nuevoUsuario (nodoArbolDesa* arbol){ ///Nuevo usuario, versión archivos
    usuario nuevo;
    char nombre[30];
    printf("\nNombre: ");
    fflush(stdin);
    gets(nombre);
    int pos = posUsuarioNombreEnArchivo(nombre);
    if (pos != -1){
        printf("\n\nYa existe un usuario registrado con el nombre ingresado.\n\n");
        system("pause");
        menuPrincipal(arbol);
    }else{
        strcpy(nuevo.nombreUsuario, nombre);
        printf("\nContrase\xa4\x61 : ");
        fflush(stdin);
        gets(nuevo.contraUsuario);
        nuevo.puntajeUsuario = 0;
        nuevo.ataqueUsuario = ATQ_BASE_USER;
        nuevo.vidaUsuario = HP_BASE_USER;
        nuevo.usuarioEliminado = 0;
        nuevo.idUsuario = cantUsuariosEnArchivo() + 1;
        if (nuevo.idUsuario == 1){ ///El primer usuario a registrar es admin
            nuevo.categoriaUsuario = 'A';
        }else{
            nuevo.categoriaUsuario = 'J';
        }
    }
    guardarNuevoUsuArchivo(nuevo);
}


void logInUser (nodoArbolDesa* arbol){
    char nombre[30];
    printf("\nNombre: ");
    fflush(stdin);
    gets(nombre);
    int pos = posUsuarioNombreEnArchivo(nombre);
    if (pos == -1){ ///No existe usuario con ese nombre
        printf("\n\n----No existe ningún usuario registrado con el nombre ingresado.----\n\n");
        system("pause");
        menuPrincipal(arbol);
    }else{ ///Existe
        usuario aux = usuarioPorRegistro(pos-1);
        char pass[15];
        printf("\nContrase\xa4\x61 : ");
        fflush(stdin);
        gets(pass);

        if (strcmp(aux.contraUsuario, pass) == 0){ ///Ingresa al menu usuario
            menuUsuario(aux, arbol);
        }else{
            printf("\n\n----Contrase\xa4\x61 incorrecta.----\n\n");
            system("pause");
            menuPrincipal(arbol);
        }

    }
}

void pantallaPrincipal(){
    ///Pantalla titulo
    system("pause");
}

void menuPrincipal (nodoArbolDesa* arbol){
    system("cls");
    int op;
    printf("\nIngrese a su cuenta, si no tiene una registrese:\n\n\n1.Registrarse.\n2.Ingresar.\n3.Volver\n");
    fflush(stdin);
    scanf("%i", &op);
    usuario nuevo;
    system("cls");
    switch (op){
        case 1: ///Se guarda en el archivo.
            nuevoUsuario(arbol);
            printf("\n\n¡Su cuenta ha sido creada con éxito! Ingrese a su cuenta desde el menu principal\n\n");
            system ("pause");
            menuPrincipal(arbol);
            break;
        case 2: ///Se loguea
            printf("\n\nIngrese los datos para acceder a su usuario:\n\n");
            logInUser(arbol);
            break;
        case 3: ///Volver
            pantallaPrincipal();
            break;
        default:
            printf("\n\nOpcion incorrecta, intente de nuevo. \n\n\n");
            system("pause");
            menuPrincipal(arbol);
            break;
    }
}

void menuUsuario (usuario jugador, nodoArbolDesa* arbolDesafios){  ///Hay que modificar si agregamos más
    ///usuario jugador;
    system("cls");
    printf("\n\n1.Jugar.\n2.Ver ranking de puntajes.\n3.Salir del usuario\n");
    int op;
    fflush(stdin);
    scanf("%i", &op);
    switch (op){
    case 1:
        /**
        ///Función inicJuego (nodoListaUsu* nodoUsuario, nodoArbolDesa* arbol)

        /// OJOOO, quitar despues de cambiar la lista de usuarios
        jugador.idUsuario=nodoUsuario->usuario.idUsuario;
        strcpy(jugador.nombreUsuario,nodoUsuario->usuario.nombreUsuario);
        strcpy(jugador.contraUsuario,nodoUsuario->usuario.contraUsuario);
        jugador.categoriaUsuario=nodoUsuario->usuario.categoriaUsuario;
        jugador.vidaUsuario  =1000 ;///  nodoUsuario->usuario.vidaUsuario;
        jugador.ataqueUsuario=10;   ///  nodoUsuario->usuario.ataqueUsuario;
        jugador.puntajeUsuario=nodoUsuario->usuario.puntajeUsuario;
        jugador.usuarioEliminado=nodoUsuario->usuario.usuarioEliminado;
        */
        mostrarUsuario(jugador);

        /// ------------------------------------------------------

        jugar(&jugador,arbolDesafios, arbolDesafios);

        mostrarUsuario(jugador);
        break;
    case 2:
        ///Función mostrarUsuariosPorPuntaje
        break;
    case 3:
        menuPrincipal(arbolDesafios);
        break;
        }
        ///MOSTRAR LAS OPCIONES QUE SALEN SI ES USUARIO ADMIN--------
}

void iniciarPrograma (){ ///Hay que cargar las estructuras desde los archivos cuando se inicia
char string[30];
    nodoArbolDesa* arbol = inicArbolDesafio();
    arbol = pasarDesafiosArchivoToArbol(arbol);
    sprintf(string, "mode con: cols=%d lines=%d", 45,45);
    system(string);
    pantallaPrincipal();
    menuPrincipal(arbol);
}

