#include "menu.h"
#include <time.h>

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
    int op=0;
    while(op!=4){
        ///usuario jugador;
        system("cls");
        printf("\n\n1.Jugar.\n2.Ver ranking de puntajes.\n3.Ver historial de jugadas.\n4.Salir del usuario.\n");
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
            int resultado=0;
            int puntaje=0;
            int turnos=0;

            /// OJOOO quitar
            jugador.ataqueUsuario=20;
            int dificultadJugada=1;
            printf("Id: %d\n",jugador.idUsuario);
            /// OJOOO quitar

            jugador.puntajeUsuario=0; ///para asegurarnos que cada vez que empiece un juego nuevo el acumulador sea 0
            resultado=jugar(&jugador,arbolDesafios,arbolDesafios,&puntaje,&turnos);
            //printf("%d,%d,%d\n",resultado,puntaje,turnos);

            /// --- Guardo datos en Historico de Jugadas ---
            char fyh[20];
            getfechayhora(fyh);
            historialDeJugadas aux_his;

            aux_his.idUsuario=jugador.idUsuario;
            strcpy(aux_his.fechaHoraJugada,fyh);
            aux_his.dificultadJugada=dificultadJugada;
            aux_his.resultado=resultado;
            aux_his.turnosTotalesJugados=turnos;
            aux_his.puntosGanados=puntaje;

            guardarHitoricoJugadas(aux_his);
            /// ---------------------------------------------


            break;
        case 2:
            ///Función mostrarUsuariosPorPuntaje
            break;
        case 3:
            system("cls");
            printf("\n");
            muestraHistorialJugadas(jugador.idUsuario);
            printf("\n");
            system("pause");

            break;
        case 4:
            menuPrincipal(arbolDesafios);
            break;
            }
            ///MOSTRAR LAS OPCIONES QUE SALEN SI ES USUARIO ADMIN--------
    }
}

void getfechayhora(char fechayhora[20]){
  time_t t;
  struct tm *tm;
  t=time(NULL);
  tm=localtime(&t);
  strftime(fechayhora, 20, "%d/%m/%y %H:%M:%S", tm);
}


void iniciarPrograma (){ ///Hay que cargar las estructuras desde los archivos cuando se inicia
    char string[30];
    nodoArbolDesa* arbol = inicArbolDesafio();
    arbol = pasarDesafiosArchivoToArbol(arbol);
<<<<<<< HEAD
    sprintf(string, "mode con: cols=%d lines=%d", 45,45);
    system(string);
=======

    sprintf(string, "mode con: cols=%d lines=%d", 168,57);
    system(string);

>>>>>>> eca058efa5aa99650ae63fe42df7a9efb57b71de
    pantallaPrincipal();
    menuPrincipal(arbol);
}

