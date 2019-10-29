#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "desafios.h"
#include "historialDeJugadas.h"
#include "usuarios.h"

usuario nuevoUsuario(nodoListaUsu* lista, nodoArbolDesa* arbol);

nodoListaUsu* logInUser(nodoListaUsu* lista, nodoArbolDesa* arbol);

void pantallaPrincipal();

void menuPrincipal(nodoListaUsu* lista, nodoArbolDesa* arbol);

void menuUsuario(nodoListaUsu* lista, nodoListaUsu* nodoUsuario, nodoArbolDesa* arbol);

void iniciarPrograma();

#endif // MENU_H_INCLUDED
