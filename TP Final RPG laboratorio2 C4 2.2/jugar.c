#include "jugar.h"
#include "Pantallas.h"

void recompensa(usuario*jugador){
    jugador->vidaUsuario+=100;
}


int calculoDanio(int ataqueBase){
    int dados=rand () % (MAX_DADOS-MIN_DADOS+1) + MIN_DADOS;
    gotoxy(42,52);
    printf("El resultado de los dados es: %2d",dados);
    int total=dados*ataqueBase;
    gotoxy(42,54);
    printf("El danio total es: %3d",total);

    return total;
}

char pelear(usuario*jugador,nodoArbolDesa*desafio){ ///al usuario jugador hay que cambiarlo por nodo*jugador
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
        dibujaCaja(1,50,35,60);///caja de aopciones
        dibujaCaja(40,50,195,60);///caja de descripciones

        gotoxy(3,3);
        printf("Vida:%5d\n",jugador->vidaUsuario);
        gotoxy(3,5);
        printf("Vida %s: %3d\n",desafio->desafio.monstruo.nombreMonstruo,desafio->desafio.monstruo.vidaBaseMonstruo);
        gotoxy(3,52);
        printf("1.Atacar");
        gotoxy(3,54);
        printf("2.Huir");
        gotoxy(42,52);
        printf("Elige una accion: ");
        fflush(stdin);
        gotoxy(60,52);
        scanf("%d",&respuesta);
        if(respuesta==1){
            /// Ataca Jugador
            danio=calculoDanio(jugador->ataqueUsuario);
            desafio->desafio.monstruo.vidaBaseMonstruo=desafio->desafio.monstruo.vidaBaseMonstruo-danio;
            if(desafio->desafio.monstruo.vidaBaseMonstruo>0){
                gotoxy(42,56);
                printf("Es el turno de tu enemigo");
                gotoxy(42,58);
                system("pause");
                /// Ataca Enemigo
                danio=calculoDanio(desafio->desafio.monstruo.ataqueBaseMonstruo);
                gotoxy(42,56);
                printf("                           ");
                gotoxy(42,58);
                system("pause");
                jugador->vidaUsuario=jugador->vidaUsuario-danio;
            }
            if(desafio->desafio.monstruo.vidaBaseMonstruo<=0){
                resultPelea='V';    /// Salio Vivo de la pelea
                jugador->puntajeUsuario+=desafio->desafio.monstruo.puntosMonstruo;

                // dibujaCaja(40,50,195,60);///caja de descripciones
                gotoxy(42,56);
                printf("Eliminaste a tu enemigo, en este nivel ganaste: %d puntos",desafio->desafio.monstruo.puntosMonstruo);
                gotoxy(42,58);
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

void jugar(usuario*jugador,nodoArbolDesa*desafio, nodoArbolDesa* anterior){ ///Cuando es la primer llamada a anterior se pasa el arbol como a desafio
    char resultPelea;
    int camino;
    if(desafio!=NULL){
        printf("---------------------------------------------------------\n");
        printf("%s\n",desafio->desafio.descripcionDesafio);
        printf("---------------------------------------------------------\n");
        system("pause");
        system("cls");
        switch(desafio->desafio.tipoDesafio){
            case 'P':       ///Pelea
                resultPelea=pelear(jugador,desafio);
                system("cls");
                switch(resultPelea){
                    case 'V':    ///Salio vivo
                        if(desafio->derecha!=NULL || desafio->izquierda!=NULL){
                            anterior = desafio;
                            printf("%s\n",desafio->desafio.preguntaProxDesafio);
                            fflush(stdin);
                            scanf("%d",&camino);
                            if(camino==1){
                                jugar(jugador,desafio->derecha, anterior);
                            }else{
                                jugar(jugador,desafio->izquierda, anterior);
                            }
                        }else{
                            printf("\n\nSaliste del dungeon...\n\nTu puntuacion es: %d\n\n---------GANASTE---------\n\n",jugador->puntajeUsuario);
                            ///printf("\n\nSaliste del dungeon...\n\n---------GANASTE---------\n\n");
                        }
                        break;
                    case 'M':
                        printf("\nMORISTE\n");
                        dibujaPantallaMuerte();
                        return;
                        break;
                    case 'H':
                        printf("\n¡Decidiste huir! Volves al desafío anterior y podes decidir de nuevo que camino tomar.\n\n");
                        printf("%s\n",anterior->desafio.preguntaProxDesafio);
                        fflush(stdin);
                        scanf("%d",&camino);
                        if(camino==1){
                            jugar(jugador,anterior->derecha, anterior);
                        }else{
                            jugar(jugador,anterior->izquierda, anterior);
                        }
                        return;
                        break;
                }
                break;
            case 'R':
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
                    jugar(jugador,desafio->derecha, anterior);
                }else{
                    jugar(jugador,desafio->izquierda, anterior);
                }
                break;
        }
    }
}

