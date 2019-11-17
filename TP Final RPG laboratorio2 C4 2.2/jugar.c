#include "jugar.h"

void recompensa(usuario*jugador){
    jugador->vidaUsuario+=100;
}


int calculoDanio(int ataqueBase){
    int dados=rand () % (MAX_DADOS-MIN_DADOS+1) + MIN_DADOS;
    gotoxy(42,47);
    printf("El resultado de los dados es: %2d",dados);
    int total=dados*ataqueBase;
    gotoxy(42,49);
    printf("El danio total es: %3d",total);

    return total;
}

char pelear(usuario*jugador,nodoArbolDesa*desafio,int*turnos){
    //*turnos=0;
    int danio;
    char resultPelea=' ';
    int respuesta=0;
    int vidaInicialM = desafio->desafio.monstruo.vidaBaseMonstruo;

    if(desafio->desafio.idDesafio==4){
        gotoxy(0,15);
        dibujaGoblin();
    }


    while(resultPelea==' '){
        dibujaCaja(1,1,35,10);///caja de vida's
        dibujaCaja(1,45,35,55);///caja de opciones
        dibujaCaja(40,45,165,55);///caja de descripciones

        gotoxy(3,3);
        printf("Vida:%5d\n",jugador->vidaUsuario);
        gotoxy(3,5);
        printf("Vida %s: %3d\n",desafio->desafio.monstruo.nombreMonstruo,desafio->desafio.monstruo.vidaBaseMonstruo);
        gotoxy(3,47);
        printf("1.Atacar");
        gotoxy(3,49);
        printf("2.Huir");
        gotoxy(42,47);
        printf("Elige una accion: ");
        fflush(stdin);
        gotoxy(60,47);
        scanf("%d",&respuesta);
        if(respuesta==1){
            /// Ataca Jugador
            *turnos=*turnos+1;
            danio=calculoDanio(jugador->ataqueUsuario);
            desafio->desafio.monstruo.vidaBaseMonstruo=desafio->desafio.monstruo.vidaBaseMonstruo-danio;
            if(desafio->desafio.monstruo.vidaBaseMonstruo>0){
                gotoxy(42,51);
                printf("Es el turno de tu enemigo");
                gotoxy(42,53);
                system("pause");
                /// Ataca Enemigo
                danio=calculoDanio(desafio->desafio.monstruo.ataqueBaseMonstruo);
                gotoxy(42,51);
                printf("                           ");
                gotoxy(42,53);
                system("pause");
                jugador->vidaUsuario=jugador->vidaUsuario-danio;
            }
            if(desafio->desafio.monstruo.vidaBaseMonstruo<=0){
                resultPelea='V';    /// Salio Vivo de la pelea
                jugador->puntajeUsuario+=desafio->desafio.monstruo.puntosMonstruo;

                // dibujaCaja(40,50,195,60);///caja de descripciones
                gotoxy(42,51);
                printf("Eliminaste a tu enemigo, en este nivel ganaste: %d puntos",desafio->desafio.monstruo.puntosMonstruo);
                gotoxy(42,53);
                system("pause");

            }
            if(jugador->vidaUsuario<=0){
                resultPelea='M';    /// Salio Muerto de la pelea
            }
        }else{
            resultPelea='H';    /// Decidio Huir
            desafio->desafio.monstruo.vidaBaseMonstruo = vidaInicialM;
        }
    }
    return resultPelea;
}

int jugar(usuario*jugador,nodoArbolDesa*desafio, nodoArbolDesa* anterior, int*puntaje, int*turnosTotales){ ///Cuando es la primer llamada a anterior se pasa el arbol como a desafio
    int turnos=0;
    //int turnosTotales;s
    char resultPelea;
    int camino;
    int resultado=-1;
    if(desafio!=NULL){
        printf("---------------------------------------------------------\n");
        printf("%s\n",desafio->desafio.descripcionDesafio);
        printf("---------------------------------------------------------\n");
        system("pause");
        system("cls");
        switch(desafio->desafio.tipoDesafio){
            case 'P':       ///Pelea
                resultPelea=pelear(jugador,desafio,&turnos);
                *turnosTotales=*turnosTotales+turnos;
                system("cls");
                switch(resultPelea){
                    case 'V':    ///Salio vivo
                        if(desafio->derecha!=NULL || desafio->izquierda!=NULL){
                            anterior = desafio;
                            printf("%s\n",desafio->desafio.preguntaProxDesafio);
                            fflush(stdin);
                            scanf("%d",&camino);
                            if(camino==1){
                                resultado=jugar(jugador,desafio->derecha, anterior,puntaje,turnosTotales);
                            }else{
                                resultado=jugar(jugador,desafio->izquierda, anterior,puntaje,turnosTotales);
                            }
                        }else{
                            printf("\n\nSaliste del dungeon...\n\nTu puntuacion es: %d\n\n---------GANASTE---------\n\n",jugador->puntajeUsuario);
                            ///printf("\n\nSaliste del dungeon...\n\n---------GANASTE---------\n\n");
                            system("pause");
                            cargarPuntajes(jugador->nombreUsuario,jugador->puntajeUsuario);
                            resultado=1;    /// Gano
                        }
                        break;
                    case 'M':
                        printf("\nMORISTE\n");
                        dibujaPantallaMuerte();
                        system("pause");
                        cargarPuntajes(jugador->nombreUsuario,jugador->puntajeUsuario);
                        return;
                        resultado=0; /// Perdio
                        break;
                    case 'H':
                        printf("\nDecidiste huir!!! Volveras al desafio anterior y podras decidir de nuevo que camino tomar.\nSe te restaran 50 de tu puntuacion total.\n\n");
                        jugador->puntajeUsuario = jugador->puntajeUsuario - 50;
                        if(jugador->puntajeUsuario<0){
                            jugador->puntajeUsuario=0;  ///para que el puntaje no quede negativo
                        }
                        printf("%s\n",anterior->desafio.preguntaProxDesafio);
                        fflush(stdin);
                        scanf("%d",&camino);
                        if(camino==1){
                            resultado=jugar(jugador,anterior->derecha, anterior,puntaje,turnosTotales);
                        }else{
                            resultado=jugar(jugador,anterior->izquierda, anterior,puntaje,turnosTotales);
                        }
                        break;
                }
                break;
            case 'R':       ///Recompensa
                anterior = desafio;
                printf("---------------------------------------------------------\n");
                printf("%s\n",desafio->desafio.descripcionDesafio);
                recompensa(jugador);
                printf("Vida: %d\n",jugador->vidaUsuario);
                printf("---------------------------------------------------------\n");

                printf("%s\n",desafio->desafio.preguntaProxDesafio);
                fflush(stdin);
                scanf("%d",&camino);
                if(camino==1){
                    resultado=jugar(jugador,desafio->derecha, anterior,puntaje,turnosTotales);
                }else{
                    resultado=jugar(jugador,desafio->izquierda, anterior,puntaje,turnosTotales);
                }
                break;
        }
    }


    *puntaje=jugador->puntajeUsuario;
    return resultado;

}

