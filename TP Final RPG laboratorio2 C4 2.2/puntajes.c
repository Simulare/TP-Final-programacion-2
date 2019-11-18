#include "puntajes.h"

nodoPuntajes * inicListaPuntajes()
{
    return NULL;
}

nodoPuntajes * crearNodoPuntajes(char nombre[30],int puntaje)
{
    nodoPuntajes * nuevo=(nodoPuntajes*)malloc(sizeof(nodoPuntajes));
    strcpy(nuevo->puntajes.nombre,nombre);
    nuevo->puntajes.puntaje=puntaje;
    nuevo->siguiente=NULL;
    return nuevo;
}

///Acomoda el puntaje del mayor puntaje al menor
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
            lista=nuevo;
        }
        else
        {
            nodoPuntajes * ante=lista;
            nodoPuntajes * seg=lista->siguiente;
            while(lista != NULL && lista->puntajes.puntaje>nuevo->puntajes.puntaje)
            {
                ante = seg;
                seg = seg->siguiente;
            }
            ante->siguiente=nuevo;
            nuevo->siguiente=seg;
        }
    }
    return lista;
}

nodoPuntajes * abrirArchivoPuntajes()
{
    STpuntajes aux;
    nodoPuntajes * lista;
    FILE * archi=fopen("puntajes.dat","rb");
    while(fread(&aux,sizeof(nodoPuntajes),1 ,archi) >0)
    {
        lista = acomodarPuntaje(lista, crearNodoPuntajes(aux.puntaje, aux.nombre));
        ///strcpy(lista->puntajes.nombre,aux.nombre);
        ///lista->puntajes.puntaje=aux.puntaje;
        ///lista->siguiente=inicListaPuntajes();

    }
    fclose(archi);
    return lista;
}

void guardarArchivoPuntajes(nodoPuntajes * lista)
{
    STpuntajes aux;
    FILE * archi = fopen("puntajes.dat","ab");
    if(lista!=NULL)
    {
        aux.puntaje=lista->puntajes.puntaje;
        strcpy(aux.nombre,lista->puntajes.nombre);
        fwrite(&aux,sizeof(STpuntajes),1,archi);
        lista=lista->siguiente;
    }
    fclose(archi);
}

void mostrarPuntajes(STpuntajes puntaje,int posicion)
{
    printf("[ %d ]\t%s :\t%d\n",posicion,puntaje.nombre,puntaje.puntaje);
}

void recorreMostrarPuntajes()
{
    system("cls");
    STpuntajes aux;

    FILE * archi=fopen("puntajes.dat","rb");
    int posicion=1;
    while(fread(&aux,sizeof(STpuntajes),1,archi)>0)
    {
        mostrarPuntajes(aux,posicion);
        posicion++;
    }
    fclose(archi);
}

void cargarPuntajes(char nombre[],int puntaje)
{
    nodoPuntajes * nuevo=inicListaPuntajes();
    printf("se inicializo la lista\n");
    system("pause");

    nuevo=crearNodoPuntajes(nombre,puntaje);
    printf("se creo el nodo\n");
    system("pause");

    nodoPuntajes * lista = abrirArchivoPuntajes();
    printf("se abrio archivopuntajes\n");
    system("pause");
    lista=acomodarPuntaje(lista,nuevo);
    printf("se acomodo\n");
    system("pause");
    guardarArchivoPuntajes(lista);
    printf("se guardo\n");
    system("pause");

}
