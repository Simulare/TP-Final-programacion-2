#include <stdio.h>
#include <stdlib.h>
#include "mounstruo.h"

nodoMonstruo * iniclista()
{
    return NULL;
}

STmonstruo cargarMonstruo(){
    STmonstruo aux;
    printf("\nIngrese número de id del monstruo\n"); ///Hay que verificar que no haya uno con el mismo id
    fflush(stdin);
    scanf("%i", aux.idMonstruo);
    printf("Ingrese nombre de monstruo\n");
    fflush(stdin);
    scanf("%s",&aux.nombreMonstruo);
    printf("Ingrese el nivel del monstruo\n ");
    fflush(stdin);
    scanf("%i", &aux.nivel);
    printf("Ingrese vida base del monstruo\n");
    fflush(stdin);
    scanf("%d",&aux.vidaBaseMonstruo);
    printf("Ingrese ataque base del monstruo\n");
    fflush(stdin);
    scanf("%d",&aux.ataqueBaseMonstruo);
    printf("Ingrese puntos que da el monstruo al ser derrotado\n");
    fflush(stdin);
    scanf("%d",&aux.puntosMonstruo);

    return aux;
}

void agregarMonstruoArchivo (STmonstruo aux){
    FILE * archi = fopen("mounstruos.dat","ab");
    fwrite(&aux, sizeof(STmonstruo), 1, archi);
    fclose(archi);
}

nodoMonstruo * cargarListaMonstruos(nodoMonstruo* lista) ///Lo carga a la lista y al archivo
{
    STmonstruo aux;
    nodoMonstruo* nuevo;
    char control='s';
    FILE * archi = fopen("mounstruos.dat","ab");
    while(control=='s'||'S')
    {
        aux = cargarMonstruo();
        nuevo = crearNodoMonstruo(aux);
        lista = agregarFinal(lista, nuevo);
        agregarMonstruoArchivo(aux);
        printf("Desea cargar otro mounstruo? [ s ] / [ n ]\n");
        fflush(stdin);
        scanf("%c",&control);
        system("cls");
    }

    return lista;
}

nodoMonstruo * crearNodoMonstruo(STmonstruo monstruo)
{
    nodoMonstruo * aux = (nodoMonstruo*)malloc(sizeof(nodoMonstruo));
    aux->monstruo = monstruo;
    aux->sig = NULL;
    aux->ante = NULL;

    return aux;
}

void mostrarMonstruo(STmonstruo aux)
{
        printf("ID : %d",aux.idMonstruo);
        printf("Nombre : %s\n",aux.nombreMonstruo);
        printf("Nivel: %d\n", aux.nivel);
        printf("Vida : %d\n",aux.vidaBaseMonstruo);
        printf("Ataque : %d\n\n\n",aux.ataqueBaseMonstruo);
        printf("Puntos por derrotarlo: %d", aux.puntosMonstruo);
}

 void recorrerMostrar(nodoMonstruo * listaMonstruos)
 {
     while(listaMonstruos!=NULL)
     {
         mostrarMonstruo(listaMonstruos->monstruo);
         listaMonstruos=listaMonstruos->sig;
     }
 }


nodoMonstruo* agregarFinal(nodoMonstruo* listaMonstruos, nodoMonstruo * nuevoMonstruo)
{
    if(listaMonstruos==NULL)
    {
        listaMonstruos=nuevoMonstruo;
    }
    else
    {
        nodoMonstruo* ultimo=buscarUltimo(listaMonstruos);
    }
    return listaMonstruos;
}

nodoMonstruo * buscarUltimo(nodoMonstruo * listaMonstruos)
{
    nodoMonstruo * aux = listaMonstruos;
    while(aux!=NULL)
    {
        aux = aux->sig;
    }
    return aux;
}
