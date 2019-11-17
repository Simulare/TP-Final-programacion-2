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
    int op;
    if (jugador.categoriaUsuario == 'J'){
        printf("\n\n1.Jugar.\n2.Ver ranking de puntajes.\n3.Salir del usuario\n");
        fflush(stdin);
        scanf("%i", &op);
        switch (op){
            case 1:

                mostrarUsuario(jugador);
                jugar(&jugador,arbolDesafios, arbolDesafios);
                mostrarUsuario(jugador);
                break;
            case 2:
                ///Función mostrarUsuariosPorPuntaje
                break;
            case 3:
                menuPrincipal(arbolDesafios);
                break;
            default:
                printf("\n\nOPCIÓN INCORRECTA. Intente de nuevo.\n\n\n"):
                system("pause");
                menuUsuario(jugador, arbolDesafios);
        }
    }else{ ///El usuario es admin
        printf("\n\n1.Jugar.\n2.Ver ranking de puntajes.\n3.Asignar administrador.\n4.Desafios ABL\n");
        fflush(stdin);
        switch (op){
            case 1:

                mostrarUsuario(jugador);
                jugar(&jugador,arbolDesafios, arbolDesafios);
                mostrarUsuario(jugador);
                break;
            case 2:
                ///Función mostrarUsuariosPorPuntaje
                break;
            case 3:
                menuPrincipal(arbolDesafios);
                break;
            case 4:
                char nombre[30];
                printf("\n\nPara asignar la categoría de administrador recuerde que el usuario ya debe estar registrado. Ingrese el nombre del usuario:\n\n");
                fflush(stdin);
                gets(nombre);
                int pos = posUsuarioNombreEnArchivo(nombre);
                if (pos == -1){
                    printf("\n\nEl usuario ingresado no se encuentra ingresado, será enviado al menú anterior.\n\n");
                    system("pause");
                    menuUsuario(jugador, arbolDesafios);
                }else{

                }
            default:
                printf("\n\nOPCIÓN INCORRECTA. Intente de nuevo.\n\n\n"):
                system("pause");
                menuUsuario(jugador, arbolDesafios);
        }
    }
}
void menuAdmin (usuario jugador){
    nodoArbolDesa*
}


void iniciarPrograma (){ ///Hay que cargar las estructuras desde los archivos cuando se inicia
    ///char string[30];
    ///sprintf(string, "mode con: cols=%d lines=%d", 45,45);
    ///system(string);
    nodoArbolDesa* arbol = inicArbolDesafio();
    arbol = pasarDesafiosArchivoToArbol(arbol);
    pantallaPrincipal();
    menuPrincipal(arbol);

}

