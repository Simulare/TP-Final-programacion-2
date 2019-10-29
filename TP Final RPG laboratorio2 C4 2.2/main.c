#include <stdio.h>
#include <stdlib.h>
#include "jugar.h"
#include "usuarios.h"

int main()
{
    srand(time(NULL));  /// planto semilla para los dados.
    usuario user;

    STdesafio desafio;
    nodoArbolDesa*arbolDesa=inicArbolDesafio();  ///arbol desafio

    nodoListaUsu*listaUsu=inicListaUsu();


    /// --- OJOOO, usuario harcodeado -----
    user.idUsuario=1;
    strcpy(user.nombreUsuario,"user1");
    strcpy(user.contraUsuario,"contra1");
    user.vidaUsuario=1000;
    user.ataqueUsuario=10;
    user.puntajeUsuario=0;
    user.usuarioEliminado=0;

    nodoListaUsu*nodoUsu=crearNodoListaUsu(user);


    /// --- OJOOO, desafios harcodeados -----
    desafio.idDesafio=4;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te toca pelear contra el socialismo...\n");
    desafio.puntosDesafio=50;
    desafio.vidaBase=200;
    desafio.ataqueBase=10;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=2;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te toca pelear contra el comunismo...\n");
    desafio.puntosDesafio=50;
    desafio.vidaBase=200;
    desafio.ataqueBase=10;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=1;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te toca pelear contra Carlos Menem (Final Boss)...\n");
    desafio.puntosDesafio=50;
    desafio.vidaBase=500;
    desafio.ataqueBase=15;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=3;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te toca pelear contra Carlos Menem (Final Boss)...\n");
    desafio.puntosDesafio=50;
    desafio.vidaBase=500;
    desafio.ataqueBase=15;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=6;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te toca pelear contra el comunismo...\n");
    desafio.puntosDesafio=50;
    desafio.vidaBase=200;
    desafio.ataqueBase=10;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=5;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te toca pelear contra Carlos Menem (Final Boss)...\n");
    desafio.puntosDesafio=50;
    desafio.vidaBase=500;
    desafio.ataqueBase=15;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=7;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te toca pelear contra Carlos Menem (Final Boss)...\n");
    desafio.puntosDesafio=50;
    desafio.vidaBase=500;
    desafio.ataqueBase=15;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    ///listarArbolDesafio(arbolDesa);

    /// ------------------------------------------------------


//    char respuestaPelea=pelear(user,arbolDesa);
//    printf("%c",respuestaPelea);

    jugar(nodoUsu,arbolDesa);
    return 0;

}
