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
    printf("\nId : %d", aux.idUsuario);
    printf("\nContrase\xA4a: %s", aux.contraUsuario);
    printf("\nEstado (0 Alta/ 2 Eliminado): %i", aux.usuarioEliminado);
    printf("\n--------------\n");
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


///---------------------Pasando funciones de usuarioLista a usuarioArchivo ------------------------


void guardarNuevoUsuArchivo (usuario nuevo){
    FILE* archi = fopen(USUARIOS, "ab");
    fwrite(&nuevo, sizeof(usuario), 1, archi);
    fclose(archi);
}

void mostrarArchivoUsu (int modo){ ///0 = todos; 1 = solo jugadores; 2 = solo admins
    FILE* archi = fopen(USUARIOS, "rb");
    usuario aux;
    while (fread(&aux, sizeof(usuario), 1, archi) > 0){
        switch (modo){
            case 0:
                mostrarUsuario(aux);
                break;
            case 1:
                if (aux.categoriaUsuario == 'J'){
                    mostrarUsuario(aux);
                }
                break;
            case 2:
                if (aux.categoriaUsuario == 'A'){
                    mostrarUsuario(aux);
                }
                break;
            default:
                break;
        }
    }
    fclose(archi);
}


int posUsuarioNombreEnArchivo (char nombre[]){ ///Devuelve -1 si no existe el usuario en el archivo
    int cont = 0;
    int flag = 0;
    usuario aux;
    FILE* archi = fopen(USUARIOS, "rb");
    while (fread(&aux, sizeof(usuario), 1, archi) > 0 && flag == 0){
        if (strcmpi(aux.nombreUsuario, nombre) == 0){
            flag = 1;
        }
        cont++;
    }
    fclose(archi);
    if (flag == 1){
        return cont;
    }else{
        return -1;
    }
}

usuario usuarioPorRegistro (int posRegistro){ ///pos-1
    usuario aux;
    FILE* archi = fopen(USUARIOS, "rb");
    fseek(archi, sizeof(usuario)*posRegistro, SEEK_SET);
    fread(&aux, sizeof(usuario), 1, archi);
    fclose(archi);
    return aux;
}

int cantUsuariosEnArchivo(){
    int registros = 0;
    FILE* archi = fopen(USUARIOS, "rb");
    if (archi != NULL){
        fseek(archi, 0, SEEK_END);
        registros = ftell(archi)/sizeof(usuario);
        fclose(archi);
    }
    return registros;
}

void convertirJugadorToAdmin (char nombre[]){ ///Cuando va en el menú abajo va la función menuJugador.
    int pos = posUsuarioNombreEnArchivo(nombre);
    if (pos == -1){
        printf("\n\nNo existe un usuario registrado con el nombre ingresado.");
    }else{
        char op;
        usuario jugador = usuarioPorRegistro(pos-1);
        printf("\n\nSi confirma cambiar la categoría a admin del siguiente jugador ingrese 's', sino pulse cualquier otra tecla.\n\n");
        mostrarUsuario(jugador);
        fflush(stdin);
        scanf("%c", &op);
        if (op == 's' || op == 'S'){
            FILE* archi = fopen(USUARIOS, "r+b");
            jugador.categoriaUsuario = 'A';
            fseek(archi, sizeof(usuario)*(pos-1), SEEK_SET);
            fwrite(&jugador, sizeof(usuario), 1, archi);
            fclose(archi);
            system("cls");
            printf("-------¡La categor%ca del usuario %s se ha cambiado con %cxito!---------\n\n\n\n", 160, nombre, 130);
        }else{
            printf("\n\nNo se ha modificado la categor%ca del jugador %s. Volver%c al men%c anterior.\n\n", 161, nombre, 160, 163);
        }
    }
    system("pause");
}

void bajaUsuario (char nombre[]){
    FILE * archi = fopen(USUARIOS, "r+b");
    usuario aux;
    int flag = 0;
    while(flag == 0 && fread(&aux, sizeof(usuario),1,archi) > 0){
        if(strcmpi(aux.nombreUsuario, nombre) == 0){
            aux.usuarioEliminado = 1;
            fseek(archi, sizeof(usuario)*(-1), SEEK_CUR);
            fwrite(&aux, sizeof(usuario), 1, archi);
            flag = 1;
        }
    }
    fclose(archi);
}

