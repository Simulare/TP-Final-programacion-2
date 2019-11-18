#ifndef PUNTAJES_H_INCLUDED
#define PUNTAJES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char nombre[30];
int puntaje;
}STpuntajes;

typedef struct{
STpuntajes puntajes;
struct nodoPuntajes * siguiente;
}nodoPuntajes;

nodoPuntajes * inicListaPuntajes();

nodoPuntajes * crearNodoPuntajes(int puntaje,char nombre[30]);

nodoPuntajes * acomodarPuntaje(nodoPuntajes * lista, nodoPuntajes * nuevo);

nodoPuntajes * abrirArchivoPuntajes();

void guardarArchivoPuntajes(nodoPuntajes * lista);

void recorreMostrarPuntajes();

void cargarPuntajes(char nombre[30],int puntaje);


#endif // PUNTAJES_H_INCLUDED
