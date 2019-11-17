#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "desafios.h"
#include "usuarios.h"
#include "historialDeJugadas.h"
#include <locale.h>


void nuevoUsuario(nodoArbolDesa* arbol, nodoMonstruo* listaMonstruos);

void logInUser(nodoArbolDesa* arbol, nodoMonstruo* listaMonstruos);

void pantallaPrincipal();

void menuPrincipal(nodoArbolDesa* arbol, nodoMonstruo* listaMonstruos);

void menuUsuario(usuario aux, nodoArbolDesa* arbol, nodoMonstruo* listaMonstruos);

void ABMLmonstruos(nodoMonstruo* listaMonstruos);

void modificarMonstruo (nodoMonstruo* listaMonstruos, nodoMonstruo* aModificar);

void getfechayhora(char fechayhora[20]);

void iniciarPrograma();

void administrarUsuarios ();

#endif // MENU_H_INCLUDED
