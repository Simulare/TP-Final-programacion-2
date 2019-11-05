#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USUARIOS "usuarios.dat"
#define HP_BASE_USER 1000
#define ATQ_BASE_USER 10
#define ADMIN_PASS "colador"

typedef struct{
    int idUsuario;
    char nombreUsuario[30];
    char contraUsuario[15];
    char categoriaUsuario;
    int vidaUsuario;
    int ataqueUsuario;
    int puntajeUsuario;
    int usuarioEliminado; //0 Alta; 1 Baja
}usuario;

typedef struct{
    usuario usuario;
    struct nodoListaUsu* sig;
}nodoListaUsu;

nodoListaUsu* inicListaUsu();

nodoListaUsu* buscarUsuarioPorNombre(nodoListaUsu* lista, char nombre[]);

nodoListaUsu* crearNodoListaUsu(usuario usu);

nodoListaUsu* agregarPpioUsuarioToLista (nodoListaUsu* lista, nodoListaUsu* nuevo);

void mostrarUsuario (usuario aux);

void mostrarListaUsu (nodoListaUsu* lista);

void pasarUsuariosListaToArchivo (nodoListaUsu* lista); ///Para pruebas.

nodoListaUsu* pasarUsuariosArchivoToLista(nodoListaUsu* lista);

void guardarNuevoUsuArchivo(usuario nuevo);

void mostrarArchivoUsu ();

int posUsuarioNombreEnArchivo (char nombre[]);

usuario usuarioPorRegistro (int posRegistro);

int cantUsuariosEnArchivo();


#endif // USUARIOS_H_INCLUDED
