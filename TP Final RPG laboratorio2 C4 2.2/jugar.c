#include "jugar.h"

int calculoDanio(int ataqueBase){
    int dados=rand () % (MAX_DADOS-MIN_DADOS+1) + MIN_DADOS;
    printf("\nEl resultado de los dados es: %d\n",dados);
    int total=dados*ataqueBase;
    printf("El danio total es: %d\n\n",total);
    return total;
}

char pelear(nodoListaUsu*jugador,nodoArbolDesa*desafio){ ///al usuario jugador hay que cambiarlo por nodo*jugador
    int danio;
    char resultPelea=' ';
    int respuesta=0;
    printf("---------------------------------------------------------\n");
    printf("%s\n\n",desafio->desafio.descripcionDesafio);
    printf("---------------------------------------------------------\n");
    while(resultPelea==' '){
        printf("Vida: %d\n",jugador->usuario.vidaUsuario);
        printf("Vida Enemigo: %d\n",desafio->desafio.vidaBase);
        printf("\n1.Atacar\n2.Huir\nElige una accion: ");
        fflush(stdin);
        scanf("%d",&respuesta);
        if(respuesta==1){
            /// Ataca Jugador
            danio=calculoDanio(jugador->usuario.ataqueUsuario);
            desafio->desafio.vidaBase=desafio->desafio.vidaBase-danio;
            if(desafio->desafio.vidaBase>0){
                printf("\nEs el turno de tu enemigo\n");
                system("pause");
                /// Ataca Enemigo
                danio=calculoDanio(desafio->desafio.ataqueBase);
                jugador->usuario.vidaUsuario=jugador->usuario.vidaUsuario-danio;
            }
            if(desafio->desafio.vidaBase<=0){
                resultPelea='V';    /// Salio Vivo de la pelea
            }
            if(jugador->usuario.vidaUsuario<=0){
                resultPelea='M';    /// Salio Muerto de la paelea
            }
        }else{
            resultPelea='H';    /// Decidio Huir
        }
    }
    return resultPelea;
}

void jugar(nodoListaUsu*jugador,nodoArbolDesa*desafio){
    char resultPelea;
    int camino;
    if(desafio!=NULL){
        switch(desafio->desafio.tipoDesafio){
            case 'P':       ///Pelea
                resultPelea=pelear(jugador,desafio);
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
                printf("Recibiste una recompensa");
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
