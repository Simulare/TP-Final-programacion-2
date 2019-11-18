#include "menu.h"
#include <time.h>
#include "historialDeJugadas.h"


void nuevoUsuario (nodoArbolDesa* arbol, nodoMonstruo* listaMonstruos){ ///Nuevo usuario, versión archivos
    usuario nuevo;
    char nombre[30];
    printf("\nNombre: ");
    fflush(stdin);
    gets(nombre);
    int pos = posUsuarioNombreEnArchivo(nombre);
    if (pos != -1){
        printf("\n\nYa existe un usuario registrado con el nombre ingresado.\n\n");
        system("pause");
        menuPrincipal(arbol, listaMonstruos);
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


void logInUser (nodoArbolDesa* arbol, nodoMonstruo* listaMonstruos){
    char nombre[30];
    printf("\nNombre: ");
    fflush(stdin);
    gets(nombre);
    int pos = posUsuarioNombreEnArchivo(nombre);
    if (pos == -1){ ///No existe usuario con ese nombre
        printf("\n\n----No existe ningï¿½n usuario registrado con el nombre ingresado.----\n\n");
        system("pause");
        menuPrincipal(arbol, listaMonstruos);
    }else{ ///Existe
        usuario aux = usuarioPorRegistro(pos-1);
        char pass[15];
        printf("\nContrase\xa4\x61 : ");
        fflush(stdin);
        gets(pass);

        if (strcmp(aux.contraUsuario, pass) == 0){ ///Ingresa al menu usuario
            menuUsuario(aux, arbol, listaMonstruos);
        }else{
            printf("\n\n----Contrase\xa4\x61 incorrecta.----\n\n");
            system("pause");
            menuPrincipal(arbol, listaMonstruos);
        }

    }
}

void pantallaPrincipal(){
    ///Pantalla titulo
    system("pause");
}


void menuPrincipal (nodoArbolDesa* arbol, nodoMonstruo* listaMonstruos){
    int op = -1;
    while (op != 3){
        system("cls");
        printf("\nIngrese a su cuenta, si no tiene una registrese:\n\n\n[1]   Registrarse.\n[2]   Ingresar.\n[3]   Volver\n\n\n");
        printf("Ingrese una opción: ");
        fflush(stdin);
        scanf("%i", &op);
        usuario nuevo;
        system("cls");
        switch (op){
            case 1: ///Se guarda en el archivo.
                nuevoUsuario(arbol, listaMonstruos);
                printf("\n\n¡Su cuenta ha sido creada con éxito! Ingrese a su cuenta desde el menu principal\n\n");
                system ("pause");
                break;
            case 2: ///Se loguea
                printf("\n\nIngrese los datos para acceder a su usuario:\n\n");
                logInUser(arbol, listaMonstruos);
                break;
            case 3: ///Volver
                pantallaPrincipal();
                break;
            default:
                printf("\n\nOpcion incorrecta, intente de nuevo. \n\n\n");
                system("pause");
                break;
        }
    }
}

void menuUsuario (usuario jugador, nodoArbolDesa* arbolDesafios, nodoMonstruo* listaMonstruos){  ///Hay que modificar si agregamos más
    int op=-1;
    while(op!=0){
        ///usuario jugador;
        system("cls");
        printf("\n\n[0]   Salir del usuario.\n[1]   Jugar.\n[2]   Ver ranking de puntajes.\n[3]   Ver historial de jugadas.\n\n\n");
        printf("Ingrese una opción: ");
        if (jugador.categoriaUsuario == 'A'){
            printf("[4]   ABML Monstruos.\n[5]   ABML Desafíos.\n[6]   Administrar usuarios.\n\n");
        }
        fflush(stdin);
        scanf("%i", &op);
        if (jugador.categoriaUsuario == 'J' && op > 3){
            system("cls");
            printf("\n\nError. Las opciones son de 0 a 3.\n\n");
            system ("pause");
            op = -1;

        }
        switch (op){
        case 0:
            menuPrincipal(arbolDesafios, listaMonstruos);
            break;
        case 1:
            /**
            ///Funciï¿½n inicJuego (nodoListaUsu* nodoUsuario, nodoArbolDesa* arbol)

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
            ///Funciï¿½n mostrarUsuariosPorPuntaje
            break;
        case 3:
            system("cls");
            printf("\n");
            muestraHistorialJugadas(jugador.idUsuario);
            printf("\n");
            system("pause");

            break;
        case 4:
            ABMLmonstruos(listaMonstruos);
            break;
        case 5:
            ///ABML Desafíos
            break;
        case 6:
            administrarUsuarios();
        default:
            break;
            }
    }
}

void ABMLmonstruos(nodoMonstruo* listaMonstruos){
    STmonstruo aux;
    nodoMonstruo* nodoAux;
    char nombre[30];
    int op = -1;
    while(op != 5){
        system("cls");
        printf("\n------------------------------------------------------\n\nABML MONSTRUOS\n\n------------------------------------------------------\n\n\n");
        printf("[1]   Alta.\n[2]   Baja.\n[3]   Modificar.\n[4]   Listar.\n[5]   Volver\n\n\n");
        printf("Ingrese una opción: ");
        fflush(stdin);
        scanf("%i", &op);
        switch (op){
            case 1:
                system("cls");
                aux = cargarMonstruo();
                listaMonstruos = agregarFinal(listaMonstruos, crearNodoMonstruo(aux));
                agregarMonstruoArchivo(aux);
                printf("\n\nCargado exitosamente!!\n\n\n\n");
                system("pause");
                break;
        case 2:
            system("cls");
            printf("\nIngrese el nombre del monstruo para dar de baja: ");
            fflush(stdin);
            gets(nombre);
            if (buscarMonstruoNombre(listaMonstruos, nombre) == NULL){
                printf("\n\nNo existe ningun monstruo con el nombre ingresado.\n\n\n");
                system("pause");
            }else{
                listaMonstruos = bajaMonstruo(listaMonstruos, nombre);
                pasarListaMonstruoToArchivo(listaMonstruos); ///Guarda la nueva lista sin el nodo borrado
                printf("\n\nBaja exitosa!!\n\n\n");
                system("pause");
            }
            break;
        case 3:
                system("cls");
                printf("\n\nIngrese el nombre del monstruo a modificar: ");
                fflush(stdin);
                gets(nombre);
                nodoAux = buscarMonstruoNombre(listaMonstruos, nombre);
                if (nodoAux == NULL){
                    printf("\n\nNo existe ningun monstruo con el nombre ingresado, será enviado al menú anterior.\n\n");
                    system("pause");
                }else{
                    modificarMonstruo(listaMonstruos, nodoAux);
                }
            break;
        case 4:
            system("cls");
            mostrarListaMonstruo(listaMonstruos);
            system("pause");
            break;
        }
    }
}

void modificarMonstruo (nodoMonstruo* listaMonstruos, nodoMonstruo* aModificar){
    int op = -1;
    while (op != 4){
        system("cls");
        printf("\n[1]   Vida base.\n[2]   Ataque base.\n[3]   Puntos por derrota.\n[4]   Volver\n\n\n");
        printf("Ingrese una opción: ");
        fflush(stdin);
        scanf("%i", &op);
        if (op > 4){
            printf("Opción incorrecta, vuelva a intentar.\n\n");
            system("pause");
            op = -1;
        }
        switch (op){
            case 1:
                modificarVidaMonstruo(listaMonstruos, aModificar);
                system ("cls");
                mostrarMonstruo(aModificar->monstruo);
                printf("\nSe ha modificado la vida exitosamente!!\n\n\n");
                system("pause");
                break;
            case 2:
                modificarAtaqueMonstruo(listaMonstruos, aModificar);
                system("cls");
                mostrarMonstruo(aModificar->monstruo);
                printf("\nSe ha modificado el ataque exitosamente!!\n\n\n");
                system("pause");
                break;
            case 3:
                modificarPuntosMonstruo(listaMonstruos, aModificar);
                system("cls");
                mostrarMonstruo(aModificar->monstruo);
                printf("\nSe han modificado los puntos exitosamente!!\n\n\n");
                system("pause");
                break;
        }
    }
}

void administrarUsuarios (){
    int op = -1;
    char nombre[30];

    while (op != 4){
        system("cls");
        printf("\n[1]   Convertir a un usuario en administrador.\n[2]   Listar usuarios.\n[3]   Dar de baja usuario.\n[4]   Volver\n\n\n");
        printf("Ingrese una opción: ");
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
        case 1:
            system("cls");
            printf("\n\nIngrese el nombre del usuario a asignar: ");
            fflush(stdin);
            gets(nombre);
            convertirJugadorToAdmin(nombre);
            break;
        case 2:
            system("cls");
            mostrarArchivoUsu(0);
            system("pause");
            break;
        case 3:
            system("cls");
            printf("\nIngrese el nombre del usuario a dar de baja: ");
            fflush(stdin);
            gets(nombre);
            bajaUsuario(nombre);
            system("cls");
            printf("Baja exitosa!!\n\n\n");
            system("pause");
        }
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
    nodoMonstruo * listaMonstruos = iniclista();
    listaMonstruos = pasarArchivoMonstruosToLista(listaMonstruos);
    sprintf(string, "mode con: cols=%d lines=%d", 45,45);
    system(string);

    sprintf(string, "mode con: cols=%d lines=%d", 168,50);
    system(string);

    pantallaPrincipal();
    menuPrincipal(arbol, listaMonstruos);
}

