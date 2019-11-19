#include "menu.h"
#include <time.h>
#include "historialDeJugadas.h"


void nuevoUsuario (celda celdaArbolDesa[], nodoMonstruo* listaMonstruos){ ///Nuevo usuario, versión archivos
    usuario nuevo;
    char nombre[30];
    printf("\n       <<< REGISTRAR USUARIO >>>\n\n");
    printf("\nNombre: ");
    fflush(stdin);
    gets(nombre);
    int pos = posUsuarioNombreEnArchivo(nombre);
    if (pos != -1){
        printf("\n\nYa existe un usuario registrado con el nombre ingresado.\n\n");
        system("pause");
        menuPrincipal(celdaArbolDesa, listaMonstruos);
    }else{
        strcpy(nuevo.nombreUsuario, nombre);
        printf("\nContrase%ca : ", 164);
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


void logInUser (celda celdaArbolDesa[], nodoMonstruo* listaMonstruos){
    char nombre[30];
    printf("\nNombre: ");
    fflush(stdin);
    gets(nombre);
    int pos = posUsuarioNombreEnArchivo(nombre);
    if (pos == -1){ ///No existe usuario con ese nombre
        printf("\n\n----No existe ning%cn usuario registrado con el nombre ingresado.----\n\n", 163);
        system("pause");
        menuPrincipal(celdaArbolDesa, listaMonstruos);
    }else{ ///Existe
        usuario aux = usuarioPorRegistro(pos-1);
        char pass[15];
        printf("\nContrase%ca : ", 164);
        fflush(stdin);
        gets(pass);

        if (strcmp(aux.contraUsuario, pass) == 0){ ///Ingresa al menu usuario
            menuUsuario(aux, celdaArbolDesa, listaMonstruos);
        }else{
            printf("\n\n----Contrase%ca incorrecta.----\n\n", 164);
            system("pause");
            menuPrincipal(celdaArbolDesa, listaMonstruos);
        }

    }
}

void pantallaPrincipal(){
    int x=22;
    int y=10;

    char linea[114];

    FILE *archi= fopen("pantalla principal.txt","r");

    gotoxy(x,y);
    while(fgets(&linea,sizeof(linea),archi)>0){
        gotoxy(x,whereY());
        printf("%s",linea);
    }
    fclose(archi);
    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}


void menuPrincipal (celda celdaArbolDesa[], nodoMonstruo* listaMonstruos){
    int op = -1;
    while (op != 3){
        system("cls");
        printf("\n       <<< MENU PRINCIPAL >>>\n\n");
        printf("\nIngrese a su cuenta, si no tiene una registrese:\n\n\n[1]   Registrarse.\n[2]   Ingresar.\n[3]   Volver\n\n\n");
        printf("Ingrese una opci%cn: ", 162);
        fflush(stdin);
        scanf("%i", &op);
        usuario nuevo;
        system("cls");
        switch (op){
            case 1: ///Se guarda en el archivo.
                nuevoUsuario(celdaArbolDesa, listaMonstruos);
                printf("\n\n¡Su cuenta ha sido creada con %cxito! Ingrese a su cuenta desde el menu principal\n\n", 130);
                system ("pause");
                break;
            case 2: ///Se loguea
                printf("\n       <<< INGRESAR A USUARIO >>>\n\n");
                printf("\n\nIngrese los datos para acceder a su usuario:\n\n");
                logInUser(celdaArbolDesa, listaMonstruos);
                break;
            case 3: ///Volver
                pantallaPrincipal();
                break;
            default:
                printf("\n\nOpci%cn incorrecta, intente de nuevo. \n\n\n", 162);
                system("pause");
                break;
        }
    }
}

void menuUsuario (usuario jugador, celda celdaArbolDesa[], nodoMonstruo* listaMonstruos){  ///Hay que modificar si agregamos más
    int op=-1;
    int dificultadElegida;
    while(op!=0){
        ///usuario jugador;
        system("cls");
        printf("\n       <<< MENU DE USUARIO >>>\n\n");
        printf("\n\n[0]   Salir del usuario.\n[1]   Jugar.\n[2]   Ver ranking de puntajes.\n[3]   Ver historial de jugadas.\n");
        if (jugador.categoriaUsuario == 'A'){
            printf("[4]   ABML Monstruos.\n[5]   ABML Desaf%cos.\n[6]   Administrar usuarios.\n", 161);
        }
        printf("\n\n\nIngrese una opci%cn: ", 162);
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
            menuPrincipal(celdaArbolDesa, listaMonstruos);
            break;
        case 1:
            system("cls");
            printf("\nElija una dificultad para jugar:\n\n[1]   Facil.\n[2]   Medio.\n[3]   Dificil.\n\n");
            printf("\n\n\nIngrese una opci%cn: ", 162);
            fflush(stdin);
            scanf("%d",&dificultadElegida);
            if (dificultadElegida > 3){
                system("cls");
                printf("\n\nError. Las opciones son de 1 a 3.\n\n");
                system ("pause");
            }else{


                mostrarUsuario(jugador);

                /// ------------------------------------------------------
                int resultado=0;
                int puntaje=0;
                int turnos=0;

                /// OJOOO quitar
                jugador.ataqueUsuario=20;
                printf("Id: %d\n",jugador.idUsuario);
                /// OJOOO quitar

                jugador.puntajeUsuario=0; ///para asegurarnos que cada vez que empiece un juego nuevo el acumulador sea 0
                resultado=jugar(&jugador,celdaArbolDesa[dificultadElegida-1].arbol,celdaArbolDesa[dificultadElegida-1].arbol,&puntaje,&turnos);
                //printf("%d,%d,%d\n",resultado,puntaje,turnos);

                /// --- Guardo datos en Historico de Jugadas ---
                char fyh[20];
                getfechayhora(fyh);
                historialDeJugadas aux_his;

                aux_his.idUsuario=jugador.idUsuario;
                strcpy(aux_his.fechaHoraJugada,fyh);
                aux_his.dificultadJugada=dificultadElegida;
                aux_his.resultado=resultado;
                aux_his.turnosTotalesJugados=turnos;
                aux_his.puntosGanados=puntaje;

                guardarHitoricoJugadas(aux_his);

                printf("Se guardo la partida en el historial\n\n");

                cargarPuntajes(jugador.nombreUsuario,puntaje);

                /// ---------------------------------------------

            }
            break;
        case 2:

            recorreMostrarPuntajes();
            system ("pause");
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
            ABMLdesafios(celdaArbolDesa);
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
        printf("\n------------------------------------------------------\nABML MONSTRUOS\n------------------------------------------------------\n\n\n");
        printf("[1]   Alta.\n[2]   Baja.\n[3]   Modificar.\n[4]   Listar.\n[5]   Volver\n\n\n");
        printf("Ingrese una opci%cn: ", 162);
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
                printf("\n\nNo existe ning%cn monstruo con el nombre ingresado.\n\n\n", 163);
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
                    printf("\n\nNo existe ningun monstruo con el nombre ingresado, ser%c enviado al men%c anterior.\n\n", 160, 163);
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
        printf("\n       <<< MODIFICAR MONSTRUO >>>\n\n");
        printf("\n[1]   Vida base.\n[2]   Ataque base.\n[3]   Puntos por derrota.\n[4]   Volver\n\n\n");
        printf("Ingrese una opci%cn: ",162);
        fflush(stdin);
        scanf("%i", &op);
        if (op > 4){
            printf("Opci%cn incorrecta, vuelva a intentar.\n\n", 162);
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

void ABMLdesafios(celda celdaArbolDesa[]){
    int op = -1;
    char confirm;
    int id;
    REGdesafio reemplazo;
    while(op != 4){
        system("cls");
        printf("\------------------------------------------------------\n\nABML DESAFIOS\n\n------------------------------------------------------\n\n\n");
        printf("[1]   Alta.\n[2]   Modificar.\n[3]   Listar.\n[4]   Volver\n\n\n");
        printf("Ingrese una opci%cn: ", 162);
        fflush(stdin);
        scanf("%i", &op);
        switch (op){
            case 1:
                system("cls");
                altaREGdesafio();
                printf("\n\nCargado exitosamente!!\n\n\n\n");
                system("pause");
                break;

            case 2:
                system("cls");
                printf("\n\n Para modificar un desafio tenga en cuenta que:\n\n - La id del mismo no se puede modificar.\n - El desafio se modifica en todas las dificultades.\n\nPara continuar con la modificacion ingrese 's' de otra forma volvera al menu anterior.\n\n");
                fflush(stdin);
                scanf("%c", &confirm);
                if (confirm == 's'){
                    system("cls");
                    printf("\n\nIngrese la id del desafio a modificar: ");
                    fflush(stdin);
                    scanf("%i", &id);
                    if (existeREGDesafioID(id) == 1){
                        reemplazo = REGparaReemplazar(id);
                        ///Lo reemplazo en el archivo y en cada arbol de los niveles.
                        buscarYReemplazarREGDesafio(id, reemplazo);
                        muestraArchiDesafios();
                        system("pause");
                        reemplazarNodoDesafio(celdaArbolDesa[0].arbol, reemplazo);
                        reemplazarNodoDesafio(celdaArbolDesa[1].arbol, reemplazo);
                        reemplazarNodoDesafio(celdaArbolDesa[2].arbol, reemplazo);
                        system("cls");
                        printf("\n\nSe ha modificado el desafio con exito!!\n\n\n\n");
                        system("pause");
                    }else{
                        printf("\n\nLa id ingresada no existe.\n\n\n\n");
                        system("pause");
                    }
                }
                break;

            case 3:
                system("cls");
                printf("\n---- Celda 0 ----\n");
                listarArbolDesafio(celdaArbolDesa[0].arbol);
                //muestraArchiDesafios();
                //muestraArchiMonstruos();
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
        printf("\n       <<< ADMINISTRAR USUARIOS >>>\n\n");
        printf("\n[1]   Convertir a un usuario en administrador.\n[2]   Listar usuarios.\n[3]   Dar de baja usuario.\n[4]   Volver\n\n\n");
        printf("Ingrese una opci%cn: ", 162);
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

    celda celdaArbolDesa[3];
    pasarDesafiosArchivoToArbol(celdaArbolDesa);

    nodoMonstruo * listaMonstruos = iniclista();
    listaMonstruos = pasarArchivoMonstruosToLista(listaMonstruos);

    sprintf(string, "mode con: cols=%d lines=%d", 168,50);
    system(string);

    pantallaPrincipal();
    menuPrincipal(celdaArbolDesa, listaMonstruos);
}

