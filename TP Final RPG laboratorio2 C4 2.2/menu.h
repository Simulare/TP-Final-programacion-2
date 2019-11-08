#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "desafios.h"
#include "historialDeJugadas.h"
#include "usuarios.h"
#include <locale.h>


void nuevoUsuario();

void logInUser(arbol);

void pantallaPrincipal();

void menuPrincipal(nodoArbolDesa* arbol);

void menuUsuario(usuario aux, nodoArbolDesa* arbol);

void iniciarPrograma();

#endif // MENU_H_INCLUDED
