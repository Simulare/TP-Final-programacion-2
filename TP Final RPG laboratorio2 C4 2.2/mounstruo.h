#ifndef MOUNSTRUO_H_INCLUDED
#define MOUNSTRUO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define MONSTRUOS "monstruos.dat"
#define MODIF_LVL2 15
#define MODIF_LVL3 25

typedef struct{
    int idMonstruo;
	char nombreMonstruo[30];
	int vidaBaseMonstruo;
    int ataqueBaseMonstruo;
    int puntosMonstruo;
}STmonstruo;

typedef struct{
    STmonstruo monstruo;
    struct nodoMonstruo* sig;
    struct nodoMostruo* ante;
}nodoMonstruo;

nodoMonstruo * iniclista();

STmonstruo cargarMonstruo();

void agregarMonstruoArchivo (STmonstruo aux);

nodoMonstruo * cargarListaMonstruos(nodoMonstruo* lista);

nodoMonstruo * crearNodoMonstruo(STmonstruo monstruo);

void mostrarMonstruo(STmonstruo aux);

 void mostrarListaMonstruo(nodoMonstruo * listaMonstruos);

nodoMonstruo* agregarFinal(nodoMonstruo* listaMonstruos, nodoMonstruo * nuevoMonstruo);

nodoMonstruo * buscarUltimo(nodoMonstruo * listaMonstruos);

nodoMonstruo* buscarMonstruoNombre (nodoMonstruo* lista, char nombre[]);

STmonstruo ponerMonstruo (nodoMonstruo* nodo, int dificultad);

STmonstruo monstruoVacio();

nodoMonstruo* bajaMonstruo(nodoMonstruo* lista, char nombre[]);


#endif // MOUNSTRUO_H_INCLUDED
