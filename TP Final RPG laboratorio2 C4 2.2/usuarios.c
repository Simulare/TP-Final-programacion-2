#include "usuarios.h"

nodoListaUsu* buscarUsuarioPorNombre (nodoListaUsu* lista, char nombre[]){
    nodoListaUsu* rta = NULL;
    while (lista != NULL && rta == NULL){
        if (strcmpi(lista->usuario.nombreUsuario, nombre) == 0){
            rta = lista;
        }
        lista = lista->sig;
    }
    return rta;
}

nodoListaUsu* inicListaUsu (){
    return NULL;
}

nodoListaUsu* crearNodoListaUsu (usuario usu){
    nodoListaUsu* nodo = (nodoListaUsu*)malloc(sizeof(nodoListaUsu));
    nodo->usuario = usu;
    nodo->sig = NULL;

    return nodo;
}

nodoListaUsu* agregarPpioUsuarioToLista (nodoListaUsu* lista, nodoListaUsu* nuevo){
    if (lista == NULL){
        lista = nuevo;
    }else{
        nuevo->sig = lista;
        lista = nuevo;
    }
    return lista;
}

void mostrarUsuario (usuario aux){
    printf("\n--------------");
    printf("\nNombre: %s", aux.nombreUsuario);
    printf("\nCategoria: %c", aux.categoriaUsuario);
    printf("\nPuntaje: %i", aux.puntajeUsuario);
    if (aux.categoriaUsuario == 'A'){
        printf("\nId : %d", aux.idUsuario);
        printf("\nContrase\xA4a: %s", aux.contraUsuario);
        printf("\nEstado (0 Alta/ 2 Eliminado): %i", aux.usuarioEliminado);
    }
    printf("\n--------------\n");
}

void guardarNuevoUsuArchivo (usuario nuevo){
    FILE* archi = fopen(USUARIOS, "ab");
    fwrite(&nuevo, sizeof(usuario), 1, archi);
    fclose(archi);
}

void mostrarListaUsu (nodoListaUsu* lista){
    while(lista != NULL){
        mostrarUsuario(lista->usuario);
        lista = lista->sig;
    }
}

void pasarUsuariosListaToArchivo (nodoListaUsu* lista){ ///Para pruebas.
    FILE* archi = fopen(USUARIOS, "wb");
    while (lista != NULL){
        fwrite(&lista->usuario, sizeof(usuario), 1, archi);
        lista= lista->sig;
    }
    fclose(archi);
}

nodoListaUsu* pasarUsuariosArchivoToLista (nodoListaUsu* lista){
    FILE* archi = fopen(USUARIOS, "rb");
    usuario aux;
    while (fread(&aux, sizeof(usuario), 1, archi) > 0 ){
        nodoListaUsu* nuevo = crearNodoListaUsu(aux);
        lista = agregarPpioUsuarioToLista(lista, nuevo);
    }
    fclose(archi);

    return lista;
}

void mostrarArchivoUsu (){
    FILE* archi = fopen(USUARIOS, "rb");
    usuario aux;
    while (fread(&aux, sizeof(usuario), 1, archi) > 0){
        mostrarUsuario(aux);
    }
    fclose(archi);
}

int ExisteUsuarioNombreEnArchivo (char nombre[]){
    usuario aux;
    int flag = 0;
    FILE* archi = fopen(USUARIOS, "rb");
    while (fread(&aux, sizeof(usuario), 1, archi) > 0 && flag != 1){
        if (strcmpi(aux.nombreUsuario, nombre) == 0){
            flag = 1;
        }
    }
    return flag; //aux;
}

