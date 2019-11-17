#include "puntajes.h"

nodoPuntajes * inicListaPuntajes()
{
    return NULL;
}

nodoPuntajes * crearNodoPuntajes(int puntaje,char nombre[30])
{
    nodoPuntajes * nuevo=(nodoPuntajes*)malloc(sizof(nodoPuntajes));
    strcpy(nuevo->puntajes.nombre,nombre);
    nuevo->puntajes.puntaje=puntaje;
    nuevo->siguiente=NULL;
    return nuevo;
}

//Acomoda el puntaje del mayor puntaje al menor
nodoPuntajes * acomodarPuntaje(nodoPuntajes * lista, nodoPuntajes * nuevo)
{

    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(lista->puntajes.puntaje<nuevo->puntajes.puntaje)
        {
            nuevo->siguiente=lista;
        }
        else
        {
            nodoPuntajes * ante=lista;
            nodoPuntajes * seg=lista->siguiente;
            while(lista->puntajes.puntaje<nuevo->puntajes.puntaje)
            {
                ante = seg;
                seg = seg->siguiente
            }
            nuevo->siguiente=seg;
            ante->siguiente=nuevo;
        }
    }
    return lista;
}

nodoPuntajes * abrirArchivoPuntajes()
{
    nodoPuntajes aux;
    nodoPuntajes * lista;
    FILE * archi=fread("puntajes.bin","rb");
    while(fread(&aux,sizof(nodoPuntajes),1,archi)>0)
    {
        lista=aux;
    }
    fclose(archi);
    return lista;
}

void guardarArchivoPuntajes(nodoPuntajes * lista)
{
    nodoPuntajes aux;
    FILE * fopen("puntajes.bin","wb");
    if(lista!=NULL)
    {
        aux=lista;
        fwrite(&aux,sizeof(nodoPuntajes),1,archi));
        lista=lista->siguiente;
    }
    fclose(archi);
}

void mostrarPuntajes(nodoPuntajes * lista,int posicion)
{
    printf("[ %d ]\t%s :\t%d\n",posicion,lista->puntajes.nombre,lista->puntajes.puntaje);
}

void recorreMostrarPuntajes()
{
    system("cls");
    STpuntajes aux;
    FILE * archi=fread("puntajes.bin","rb");
    int posicion=1;
    while(fread(&aux,sizof(nodoPuntajes),1,archi)>0)
    {
        mostrarPuntajes(posicion);
        posicion++;
    }
    fclose(archi);
    return
}

void cargarPuntajes(char nombre[30],int puntaje)
{
    nodoPuntajes * nuevo=crearNodoPuntajes(nombre,puntaje);
    nuevo=inicListaPuntajes();
    nodoPuntajes * lista = abrirArchivoPuntajes();
    lista=acomodarPuntaje(lista,nuevo);
    guardarArchivoPuntajes(lista);
}
