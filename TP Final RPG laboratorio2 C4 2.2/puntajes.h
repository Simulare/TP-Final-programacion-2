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

nodoPuntajes * crearNodoPuntajes(char nombre[30],int puntaje);

nodoPuntajes*agregarPpio(nodoPuntajes*lista,nodoPuntajes*nuevo);

nodoPuntajes* acomodarPuntaje(nodoPuntajes* lista, nodoPuntajes* nuevo);

nodoPuntajes * abrirArchivoPuntajes();

void guardarArchivoPuntajes(nodoPuntajes * lista);

void mostrarPuntajes(STpuntajes puntaje,int posicion);

void recorreMostrarPuntajes();

void cargarPuntajes(char nombre[],int puntaje);

void mostrarListaPuntajes(nodoPuntajes*lista);


#endif // PUNTAJES_H_INCLUDED
