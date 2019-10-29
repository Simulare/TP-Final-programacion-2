#include "desafios.h"

nodoArbolDesa*inicArbolDesafio(){
    return NULL;
}

nodoArbolDesa*crearNodoArbolDesafio(STdesafio desafio)
{
    nodoArbolDesa*aux=(nodoArbolDesa*)malloc(sizeof(nodoArbolDesa));
    aux->desafio=desafio;
    aux->izquierda=NULL;
    aux->derecha=NULL;

    return aux;
}

nodoArbolDesa*insertarNodoArbolDesafio(nodoArbolDesa*arbol,STdesafio desafio)
{
    if(arbol==NULL){
        arbol=crearNodoArbolDesafio(desafio);
    }else{
        if(desafio.idDesafio>arbol->desafio.idDesafio){
            arbol->derecha=insertarNodoArbolDesafio(arbol->derecha,desafio);
        }else{
            arbol->izquierda=insertarNodoArbolDesafio(arbol->izquierda,desafio);
        }
    }
    return arbol;
}


void mostrarNodoArbolDesafio(nodoArbolDesa*arbol){

    printf("%d\n",arbol->desafio.idDesafio);
    printf("%c\n",arbol->desafio.tipoDesafio);
    printf("%s\n",arbol->desafio.descripcionDesafio);
    printf("%d\n",arbol->desafio.puntosDesafio);
    printf("%d\n",arbol->desafio.vidaBase);
    printf("%d\n",arbol->desafio.ataqueBase);
    printf("%s\n",arbol->desafio.preguntaProxDesafio);
    printf("%d\n",arbol->desafio.desafioEliminado);
    printf("-----------------------------\n");
}

void listarArbolDesafio(nodoArbolDesa*arbol){
    if(arbol!=NULL){
            listarArbolDesafio(arbol->izquierda);
            mostrarNodoArbolDesafio(arbol);
            listarArbolDesafio(arbol->derecha);
    }
}

void guardarDesafioEnArchivo (nodoArbolDesa* nuevo){
    FILE* archi = fopen(DESAFIOS, "ab");
    fwrite(&nuevo->desafio, sizeof(STdesafio), 1, archi);
    fclose(archi);
}

nodoArbolDesa* pasarDesafiosArchivoToArbol (nodoArbolDesa* arbol){
    FILE* archi = fopen(DESAFIOS, "rb");
    STdesafio aux;
    while (fread(&aux, sizeof(STdesafio), 1, archi) > 0){
        insertarNodoArbolDesafio(arbol, aux);
    }
    fclose(archi);
}
