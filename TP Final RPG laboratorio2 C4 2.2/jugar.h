#ifndef JUGAR_H_INCLUDED
#define JUGAR_H_INCLUDED
#define MIN_DADOS 2
#define MAX_DADOS 12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "desafios.h"

int calculoDanio(int ataqueBase);
char pelear(nodoListaUsu*jugador,nodoArbolDesa*desafio);
void jugar(nodoListaUsu*jugador,nodoArbolDesa*desafio);


#endif // JUGAR_H_INCLUDED
