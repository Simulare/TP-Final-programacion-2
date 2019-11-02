#include "jugar.h"

void recompensa(usuario**jugador){
    (*jugador)->vidaUsuario+=100;
}

int calculoDanio(int ataqueBase){
    int dados=rand () % (MAX_DADOS-MIN_DADOS+1) + MIN_DADOS;
    printf("\nEl resultado de los dados es: %d\n",dados);
    int total=dados*ataqueBase;
    printf("El danio total es: %d\n\n",total);
    return total;
}

char pelear(usuario**jugador,nodoArbolDesa*desafio){ ///al usuario jugador hay que cambiarlo por nodo*jugador
    int danio;
    char resultPelea=' ';
    int respuesta=0;

    printf("---------------------------------------------------------\n");
    printf("%s\n",desafio->desafio.descripcionDesafio);
    printf("Contra el monstruo: %s\n\n",desafio->desafio.monstruo.nombreMonstruo);
    printf("---------------------------------------------------------\n");
    while(resultPelea==' '){
        printf("Vida: %d\n",(*jugador)->vidaUsuario);
        printf("Vida %s: %d\n",desafio->desafio.monstruo.nombreMonstruo,desafio->desafio.monstruo.vidaBaseMonstruo);
        printf("\n1.Atacar\n2.Huir\nElige una accion: ");
        fflush(stdin);
        scanf("%d",&respuesta);
        if(respuesta==1){
            /// Ataca Jugador
            danio=calculoDanio((*jugador)->ataqueUsuario);
            desafio->desafio.monstruo.vidaBaseMonstruo=desafio->desafio.monstruo.vidaBaseMonstruo-danio;
            if(desafio->desafio.monstruo.vidaBaseMonstruo>0){
                printf("\nEs el turno de tu enemigo\n");
                system("pause");
                /// Ataca Enemigo
                danio=calculoDanio(desafio->desafio.monstruo.ataqueBaseMonstruo);
                (*jugador)->vidaUsuario=(*jugador)->vidaUsuario-danio;
            }
            if(desafio->desafio.monstruo.vidaBaseMonstruo<=0){
                resultPelea='V';    /// Salio Vivo de la pelea
                (*jugador)->puntajeUsuario+=desafio->desafio.monstruo.puntosMonstruo;
                printf("\nEn este nivel ganaste: %d puntos\n\n",desafio->desafio.monstruo.puntosMonstruo);
            }
            if((*jugador)->vidaUsuario<=0){
                resultPelea='M';    /// Salio Muerto de la pelea
            }
        }else{
            resultPelea='H';    /// Decidio Huir
        }
    }
    return resultPelea;
}

void jugar(usuario**jugador,nodoArbolDesa*desafio){
    char resultPelea;
    int camino;
    if(desafio!=NULL){
        switch(desafio->desafio.tipoDesafio){
            case 'P':       ///Pelea
                resultPelea=pelear(&jugador,desafio);
                switch(resultPelea){
                    case 'V':    ///Salio vivo
                        if(desafio->derecha!=NULL || desafio->izquierda!=NULL){
                            printf("%s\n",desafio->desafio.preguntaProxDesafio);
                            fflush(stdin);
                            scanf("%d",&camino);
                            if(camino==1){
                                jugar(jugador,desafio->derecha);
                            }else{
                                jugar(jugador,desafio->izquierda);
                            }
                        }else{
                            ///printf("\n\nSaliste del dungeon...\n\nTu puntuacion es: %d\n\n---------GANASTE---------\n\n",(*jugador)->puntajeUsuario);///se cuelga en la impresion de puntaje total
                            printf("\n\nSaliste del dungeon...\n\n---------GANASTE---------\n\n");
                        }
                        break;
                    case 'M':
                        printf("MORISTE\n");
                        return;
                        break;
                    case 'H':
                        printf("La partida a finalizado.\n");
                        return;
                        break;
                }
                break;
            case 'R':
                printf("---------------------------------------------------------\n");
                printf("%s\n",desafio->desafio.descripcionDesafio);
                ///printf("Vida: %d\n",(*jugador)->vidaUsuario); se cuelga cuando tiene que imprimir la vida luego de tomar la pocion
                printf("---------------------------------------------------------\n");
                recompensa(&jugador);
                printf("%s\n",desafio->desafio.preguntaProxDesafio);
                fflush(stdin);
                scanf("%d",&camino);
                if(camino==1){
                    jugar(jugador,desafio->derecha);
                }else{
                    jugar(jugador,desafio->izquierda);
                }
                break;
        }
    }
}

