#include <stdio.h>
#include <stdlib.h>
#include <mounstruo.h>

mounstruo * iniclista()
{
    return NULL;
}

mounstruo * cargarMounstruo()
{
    mounstruo aux;
    mounstruo * nuevo;
    char nombre[30];
    int vidaBase;
    int ataqueBase;
    int puntos;
    int idMonstruo;
    char control='s';
    FILE * archi = fopen("mounstruos.dat","ab");
    while(control=='s'||'S')
    {
        printf("Ingrese nombre de mounstruo\n");
        fflush(stdin);
        scanf("%s",nombre);
        printf("Ingrese vida base del mounstruo\n");
        fflush(stdin);
        scanf("%d",vidaBase);
        printf("Ingrese ataque base del mounstruo\n");
        fflush(stdin);
        scanf("%d",ataqueBase);
        printf("Ingrese puntos que da el mounstruo al ser derrotado\n");
        fflush(stdin);
        scanf("%d",puntos);
        nuevo = crearMounstruo(nombre,idMonstruo,ataqueBase,vidaBase,puntos);

        fwrite(&mounstruo,sizof(mounstruo),1,archi);
        printf("Desea cargar otro mounstruo? [ s ] / [ n ]\n");
        fflush(stdin);
        scanf("%c",&control);
        system("cls");
    }
    fclose(archi);
    return mounstruo;
}

mounstruo * crearMounstruo(char nombre[],int idMounstruo,int ataqueBase,int vidaBase,int puntos)
{
    mounstruo * aux = malloc(sizeof(mounstruo));
    strcpy(aux->nombre,nombre);
    aux->idMounstruo=idMounstruo;
    aux->ataqueBase=ataqueBase;
    aux->vidaBase=vidaBase;
    aux->puntos=puntos;
    return aux;
}

void mostrarMounstruos(mounstruo * listaMounstruos)
{
        printf("ID : %d",listaMounstruos.idMounstruo);
        printf("Nombre : %s\n",listaMounstruos.nombre);
        printf("Vida : %d\n",listaMounstruos.vidaBase);
        printf("Ataque : %d\n\n\n",listaMounstruos.ataqueBase);
}

mounstruo * agregarFinal(mounstruo * listaMounstruos,mounstruo * nuevoMounstruo)
{
    if(listaMounstruos==NULL)
    {
        listaMounstruos=nuevoMounstruo;
    }
    else
    {
        mounstruo * ultimo=buscarFinal(listaMounstruos);
    }
    return listaMounstruos;
}

mounstruo * buscarUltimo(mounstruo * listaMounstruos)
{
    mounstruo * aux = listaMounstruos;
    while(aux!=NULL)
    {
        aux = aux->siguiente;
    }
    return aux;
}

 void recorrerMostrar(mounstruo * listaMounstruos)
 {
     while(listaMounstruos!=NULL)
     {
         mostrarMounstruos(listaMounstruos);
         listaMounstruos=listaMounstruos->siguiente;
     }
 }
