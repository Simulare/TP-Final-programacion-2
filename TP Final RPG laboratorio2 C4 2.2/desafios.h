#ifndef DESAFIOS_H_INCLUDED
#define DESAFIOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DESAFIOS "desafios.dat"
#include "mounstruo.h"

typedef struct{
    int idDesafio;
    char tipoDesafio;   /// P=Pelea , R=Recompensa
    char descripcionDesafio[500];
    int dificultadDesafio; 	/// 1-2-3 (Facil-Medio-Dificil )
    STmonstruo monstruo;
    char preguntaProxDesafio[500];
    int desafioEliminado;
}STdesafio;

typedef struct{
    int idDesafio;
    char tipoDesafio;
    char descripcionDesafio[500];
    int dificultadDesafio; 	/// 1-2-3 (Facil-Medio-Dificil )
    int idMonstruo;
    char preguntaProxDesafio[500];
    int desafioEliminado;
}REGdesafio;


typedef struct{
    STdesafio desafio;
    struct nodoArbolDesa*izquierda;
    struct nodoArbolDesa*derecha;
}nodoArbolDesa;

typedef struct{
    int dificultad;
    nodoArbolDesa*arbol;
}celda;



nodoArbolDesa*inicArbolDesafio();
nodoArbolDesa*crearNodoArbolDesafio(STdesafio desafio);
nodoArbolDesa*insertarNodoArbolDesafio(nodoArbolDesa*arbol,STdesafio desafio);
void mostrarNodoArbolDesafio(STdesafio);
void listarArbolDesafio(nodoArbolDesa*arbol);
void guardarDesafioEnArchivo (nodoArbolDesa* nuevo);
nodoArbolDesa* pasarDesafiosArbolToArbol(nodoArbolDesa* arbol);
void altaREGdesafio();
void muestraArchiDesafios();
nodoArbolDesa* buscarDesafioEnArbolID (nodoArbolDesa* arbol, int id);
REGdesafio REGparaReemplazar (int id);
void reemplazarNodoDesafio (nodoArbolDesa* nodo, REGdesafio desafio);
int existeREGDesafioID(int id);


#endif // DESAFIOS_H_INCLUDED
