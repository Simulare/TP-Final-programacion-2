#include "mounstruo.h"

nodoMonstruo * iniclista()
{
    return NULL;
}

STmonstruo cargarMonstruo(){
    STmonstruo aux;
    printf("\nIngrese número de id del monstruo\n"); ///Hay que verificar que no haya uno con el mismo id
    fflush(stdin);
    scanf("%i", &aux.idMonstruo);
    printf("Ingrese nombre de monstruo\n");
    fflush(stdin);
    scanf("%s",&aux.nombreMonstruo);
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
    FILE * archi = fopen("monstruos.dat","ab");
    fwrite(&aux, sizeof(STmonstruo), 1, archi);
    fclose(archi);
}

nodoMonstruo * cargarListaMonstruos(nodoMonstruo* lista) ///Lo carga a la lista y al archivo
{
    STmonstruo aux;
    nodoMonstruo* nuevo;
    char control='s';
    FILE * archi = fopen("monstruos.dat","ab");
    while(control=='s'||'S')
    {
        aux = cargarMonstruo();
        nuevo = crearNodoMonstruo(aux);
        lista = agregarFinal(lista, nuevo);
        agregarMonstruoArchivo(aux);
        printf("Desea cargar otro monstruos? [ s ] / [ n ]\n");
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
        printf("\nID : %d\n",aux.idMonstruo);
        printf("Nombre : %s\n",aux.nombreMonstruo);
        printf("Vida : %d\n",aux.vidaBaseMonstruo);
        printf("Ataque : %d\n",aux.ataqueBaseMonstruo);
        printf("Puntos por derrotarlo: %d\n", aux.puntosMonstruo);
        printf("\n-------------------\n");
}

 void mostrarListaMonstruo(nodoMonstruo * listaMonstruos)
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

nodoMonstruo* buscarMonstruoNombre (nodoMonstruo* lista, char nombre[]){
    nodoMonstruo* rta = NULL;
    while (lista != NULL && rta == NULL){
        if (strcmpi(lista->monstruo.nombreMonstruo, nombre) == 0 ){
            rta = lista;
        }
        lista = lista->sig;
    }
    return rta;
}

STmonstruo ponerMonstruo (nodoMonstruo* nodo, int dificultad){
    STmonstruo monster = nodo->monstruo;
    int modificador;
    switch (dificultad){
        case 1:
            modificador = 0;
            break;
        case 2:
            modificador = MODIF_LVL2;
            break;
        case 3:
            modificador = MODIF_LVL3;
            break;
        default:
            modificador = 0;
            break;
    }
        monster.vidaBaseMonstruo = monster.vidaBaseMonstruo + monster.vidaBaseMonstruo * modificador / 100;
        monster.ataqueBaseMonstruo = monster.ataqueBaseMonstruo + monster.ataqueBaseMonstruo * modificador / 100;

    return monster;
}

STmonstruo monstruoVacio (){  ///Cuando el desafío es tipo recompensa va esta función como monstruo del desafio
    STmonstruo aux;
    aux.ataqueBaseMonstruo = -1;
    aux.idMonstruo = -1;
    aux.puntosMonstruo = -1;
    aux.vidaBaseMonstruo = -1;
    strcpy(aux.nombreMonstruo, "NULL");
    return aux;
}

nodoMonstruo* bajaMonstruo (nodoMonstruo* lista, char nombre[]){
    if (lista != NULL){
        nodoMonstruo* seg;
        if (strcmpi(lista->monstruo.nombreMonstruo, nombre) == 0 ){
            seg = lista;
            lista = lista->sig;
            free(seg);
        }else{
            nodoMonstruo* ante = lista;
            seg = lista->sig;
            while (seg != NULL && strcmpi(seg->monstruo.nombreMonstruo, nombre) != 0){
                ante = seg;
                seg = seg->sig;
            }
            if (seg!= NULL){
                ante->sig = seg->sig;
                free(seg);
            }
        }
    }
    return lista;
}

void pasarListaMonstruoToArchivo (nodoMonstruo* lista){
    FILE* archi = fopen(MONSTRUOS, "wb");
    while (lista != NULL){
        fwrite(&lista->monstruo, sizeof(STmonstruo), 1, archi);
        lista = lista->sig;
    }
    fclose(archi);
}

nodoMonstruo* pasarArchivoMonstruosToLista (nodoMonstruo* lista){
    FILE* archi = fopen(MONSTRUOS, "rb");
    STmonstruo aux;
    while (fread(&aux, sizeof(STmonstruo), 1, archi) > 0){
        lista = agregarFinal(lista, crearNodoMonstruo(aux));
    }
    fclose(archi);
    return lista;
}

void modificarVidaMonstruo(nodoMonstruo* lista, nodoMonstruo* aModificar){
    mostrarMonstruo(aModificar->monstruo);
    printf("\n\nIngrese la nueva vida: ");
    int vida;
    fflush(stdin);
    scanf("%i", &vida);
    aModificar->monstruo.vidaBaseMonstruo = vida;
    modificarRegistroMonstruo(aModificar->monstruo.nombreMonstruo, vida, 1);
}

void modificarAtaqueMonstruo(nodoMonstruo* lista, nodoMonstruo* aModificar){
    mostrarMonstruo(aModificar->monstruo);
    printf("\n\nIngrese los nuevos puntos de ataque: ");
    int atq;
    fflush(stdin);
    scanf("%i", &atq);
    aModificar->monstruo.ataqueBaseMonstruo = atq;
    modificarRegistroMonstruo(aModificar->monstruo.nombreMonstruo, atq, 2);
}

void modificarPuntosMonstruo(nodoMonstruo* lista, nodoMonstruo* aModificar){
    mostrarMonstruo(aModificar->monstruo);
    printf("\n\nIngrese el nuevo puntaje por derrotarlo: ");
    int puntos;
    fflush(stdin);
    scanf("%i", &puntos);
    aModificar->monstruo.puntosMonstruo = puntos;
    modificarRegistroMonstruo(aModificar->monstruo.nombreMonstruo, puntos, 3);
}

void modificarRegistroMonstruo (char nombre[], int nuevoDato, int tipo){ ///1 vida, 2 atq, 3 puntos.
    FILE * archi = fopen(MONSTRUOS, "r+b");
    STmonstruo aux;
    int flag = 0;
    while(flag == 0 && fread(&aux, sizeof(STmonstruo),1,archi) > 0){
        if(strcmpi(aux.nombreMonstruo, nombre) == 0){
            switch(tipo){
            case 1:
                aux.vidaBaseMonstruo = nuevoDato;
                break;
            case 2:
                aux.ataqueBaseMonstruo = nuevoDato;
                break;
            case 3:
                aux.puntosMonstruo = nuevoDato;
                break;
            }
            fseek(archi, sizeof(STmonstruo)*(-1), SEEK_CUR);
            fwrite(&aux, sizeof(STmonstruo), 1, archi);
            flag = 1;
            fclose(archi);
        }
    }
    fclose(archi);
}
