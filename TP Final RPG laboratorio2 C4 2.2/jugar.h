#ifndef JUGAR_H_INCLUDED
#define JUGAR_H_INCLUDED
#define MIN_DADOS 2
#define MAX_DADOS 12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "desafios.h"
#include "Pantallas.h"
#include "puntajes.h"


int calculoDanio(int ataqueBase);
char pelear(usuario*jugador,nodoArbolDesa*desafio,int*turnosTotales);
int jugar(usuario*jugador,nodoArbolDesa*desafio, nodoArbolDesa* anterior, int*puntaje, int*turnos);


#endif // JUGAR_H_INCLUDED
