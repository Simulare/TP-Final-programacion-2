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

    printf("%d\n",arbol->desafio.dificultadDesafio);

    printf("%s\n",arbol->desafio.monstruo.nombreMonstruo);
    printf("%d\n",arbol->desafio.monstruo.vidaBaseMonstruo);
    printf("%d\n",arbol->desafio.monstruo.ataqueBaseMonstruo);
    printf("%d\n",arbol->desafio.monstruo.puntosMonstruo);
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

STdesafio cargarDesafio (nodoMonstruo* lista){ ///--------------------FALTA MONSTRUO
    STdesafio aux;
    printf("\nID del desafío: ");
    fflush(stdin);
    scanf("%i", &aux.idDesafio);
    printf("\nTipo de desafío ('P' pelea / 'R' recompensa): ");
    fflush(stdin);
    scanf("%c", &aux.tipoDesafio);
    printf("\nDescripción del desafío: ");
    fflush(stdin);
    gets(aux.descripcionDesafio);
    printf("\nDificultad del desafío: ");
    fflush(stdin);
    scanf("%i", &aux.dificultadDesafio);
    if (aux.tipoDesafio == 'P'){
        char nombre[20];
        printf("\nIngrese el nombre del monstruo del desafío: ");
        fflush(stdin);
        gets(nombre);
        aux.monstruo = ponerMonstruo(lista, nombre, aux.dificultadDesafio);
    }else{
        ///Si no hay monstruo
    }
    printf("\nPregunta al próximo desafío: ");
    fflush(stdin);
    gets(aux.preguntaProxDesafio);
    aux.desafioEliminado = 0;

    return aux;
}


nodoArbolDesa* pasarDesafiosArchivoToArbol (nodoArbolDesa* arbolDesa){
/*
    FILE* archi = fopen(DESAFIOS, "rb");
    STdesafio aux;
    while (fread(&aux, sizeof(STdesafio), 1, archi) > 0){
        insertarNodoArbolDesafio(arbol, aux);
    }
    fclose(archi);
*/
    STdesafio desafio;

    /// --- OJOOO, desafios harcodeados -----
    desafio.idDesafio=4;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Un goblin salvaje se acerca!...\n");
    desafio.dificultadDesafio=1;
    strcpy(desafio.monstruo.nombreMonstruo,"Goblin");
    desafio.monstruo.vidaBaseMonstruo=100;
    desafio.monstruo.ataqueBaseMonstruo=10;
    desafio.monstruo.puntosMonstruo=50;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=2;
    desafio.tipoDesafio='R';
    strcpy(desafio.descripcionDesafio,"Conseguiste una pocion de vida!!!\n\nTu vida se incrementara en 100\n\n");
    desafio.dificultadDesafio=1;
    strcpy(desafio.monstruo.nombreMonstruo,"");
    desafio.monstruo.vidaBaseMonstruo=0;
    desafio.monstruo.ataqueBaseMonstruo=0;
    desafio.monstruo.puntosMonstruo=0;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=1;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Encontraste el final boss!, el dragon rojo...\n");
    desafio.dificultadDesafio=1;
    strcpy(desafio.monstruo.nombreMonstruo,"Dragon Rojo");
    desafio.monstruo.vidaBaseMonstruo=100;
    desafio.monstruo.ataqueBaseMonstruo=15;
    desafio.monstruo.puntosMonstruo=50;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=3;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Encontraste el final boss!, el dragon rojo...\n");
    desafio.dificultadDesafio=1;
    strcpy(desafio.monstruo.nombreMonstruo,"Dragon Rojo");
    desafio.monstruo.vidaBaseMonstruo=500;
    desafio.monstruo.ataqueBaseMonstruo=15;
    desafio.monstruo.puntosMonstruo=50;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=6;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Te encontras con un ghoul...\n");
    desafio.dificultadDesafio=1;
    strcpy(desafio.monstruo.nombreMonstruo,"Ghoul");
    desafio.monstruo.vidaBaseMonstruo=200;
    desafio.monstruo.ataqueBaseMonstruo=10;
    desafio.monstruo.puntosMonstruo=50;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=5;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Encontraste el final boss!, el dragon rojo...\n");
    desafio.dificultadDesafio=1;
    strcpy(desafio.monstruo.nombreMonstruo,"Dragon Rojo");
    desafio.monstruo.vidaBaseMonstruo=500;
    desafio.monstruo.ataqueBaseMonstruo=15;
    desafio.monstruo.puntosMonstruo=50;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);

    desafio.idDesafio=7;
    desafio.tipoDesafio='P';
    strcpy(desafio.descripcionDesafio,"Encontraste el final boss!, el dragon rojo...\n");
    desafio.dificultadDesafio=1;
    strcpy(desafio.monstruo.nombreMonstruo,"Dragon Rojo");
    desafio.monstruo.vidaBaseMonstruo=500;
    desafio.monstruo.ataqueBaseMonstruo=15;
    desafio.monstruo.puntosMonstruo=50;
    strcpy(desafio.preguntaProxDesafio,"1.derecha\n2.izquierda\n\n");
    desafio.desafioEliminado=0;

    arbolDesa=insertarNodoArbolDesafio(arbolDesa,desafio);


    return arbolDesa;

}
