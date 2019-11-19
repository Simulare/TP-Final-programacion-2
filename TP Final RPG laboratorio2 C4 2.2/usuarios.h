#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USUARIOS "usuarios.dat"
#define HP_BASE_USER 150
#define ATQ_BASE_USER 10


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


void mostrarUsuario (usuario aux);

void guardarNuevoUsuArchivo(usuario nuevo);

void mostrarArchivoUsu ();

int posUsuarioNombreEnArchivo (char nombre[]);

usuario usuarioPorRegistro (int posRegistro);

int cantUsuariosEnArchivo();

void convertirJugadorToAdmin(char nombre[]);

void bajaUsuario (char nombre[]);

#endif // USUARIOS_H_INCLUDED
