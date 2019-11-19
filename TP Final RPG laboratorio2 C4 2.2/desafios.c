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

void mostrarNodoArbolDesafio(STdesafio desafio){

    printf("Id         : %d\n",desafio.idDesafio);
    printf("Tipo       : %c\n",desafio.tipoDesafio);
    printf("Descripcion: %s\n",desafio.descripcionDesafio);

    printf("Dificultad : %d\n",desafio.dificultadDesafio);
    if (desafio.tipoDesafio == 'R'){
        printf("   Nombre Mons.  : %s\n",desafio.monstruo.nombreMonstruo);
        printf("   Vida Monst.   : %d\n",desafio.monstruo.vidaBaseMonstruo);
        printf("   Ataque Monst. : %d\n",desafio.monstruo.ataqueBaseMonstruo);
        printf("   Punstos Monst.: %d\n",desafio.monstruo.puntosMonstruo);
    }
    printf("Preg.Prox.Desaf. : %s\n",desafio.preguntaProxDesafio);
    printf("Desafio Eliminado: %d\n",desafio.desafioEliminado);
    printf("-----------------------------\n");
}

void listarArbolDesafio(nodoArbolDesa*arbol){
    if(arbol!=NULL){
            listarArbolDesafio(arbol->izquierda);
            mostrarNodoArbolDesafio(arbol->desafio);
            listarArbolDesafio(arbol->derecha);
    }
}

void guardarDesafioEnArchivo (nodoArbolDesa* nuevo){
    FILE* archi = fopen(DESAFIOS, "ab");
    fwrite(&nuevo->desafio, sizeof(STdesafio), 1, archi);
    fclose(archi);
}


void pasarDesafiosArchivoToArbol (celda adaArbolDesa[]){

    FILE* archi = fopen(DESAFIOS, "rb");
    REGdesafio aux_reg;
    STdesafio aux_desafio;

    adaArbolDesa[0].dificultad=1;
    adaArbolDesa[0].arbol=inicArbolDesafio();
    adaArbolDesa[1].dificultad=2;
    adaArbolDesa[1].arbol=inicArbolDesafio();
    adaArbolDesa[2].dificultad=3;
    adaArbolDesa[2].arbol=inicArbolDesafio();


    while (fread(&aux_reg, sizeof(REGdesafio), 1, archi) > 0){
        if(&aux_reg.desafioEliminado!=1){
            /// paso los datos del archivo a la estructura para el nodo de desafios.
            aux_desafio.idDesafio=aux_reg.idDesafio;
            aux_desafio.tipoDesafio=aux_reg.tipoDesafio;
            strcpy(aux_desafio.descripcionDesafio,aux_reg.descripcionDesafio);
            aux_desafio.dificultadDesafio=aux_reg.dificultadDesafio;
            strcpy(aux_desafio.preguntaProxDesafio,aux_reg.preguntaProxDesafio);
            aux_desafio.desafioEliminado=aux_reg.desafioEliminado;

            /// Busco los datos del Monstruo que me faltan en el archivo "monstruos.dat"
            STmonstruo aux_monstruo;
            if (aux_reg.idMonstruo == -1){
                aux_monstruo = monstruoVacio();
            }else{
                buscarMonstruoPorId(aux_reg.idMonstruo, &aux_monstruo);
            }
            /// los agrego a la estructura para el nodo de desafios.
            aux_desafio.monstruo=aux_monstruo;

            /// Original
            adaArbolDesa[0].arbol=insertarNodoArbolDesafio(adaArbolDesa[0].arbol,aux_desafio);

            if (aux_desafio.monstruo.idMonstruo != -1){ ///Si es un monstruo vacío entonces no se aplican modificadores
                aux_desafio.monstruo.ataqueBaseMonstruo=aux_desafio.monstruo.ataqueBaseMonstruo+5;
                aux_desafio.monstruo.vidaBaseMonstruo  =aux_desafio.monstruo.vidaBaseMonstruo*2;
                aux_desafio.monstruo.puntosMonstruo    =aux_desafio.monstruo.puntosMonstruo*2;
            }
            adaArbolDesa[1].arbol=insertarNodoArbolDesafio(adaArbolDesa[1].arbol,aux_desafio);

            if (aux_desafio.monstruo.idMonstruo != -1){
                aux_desafio.monstruo.ataqueBaseMonstruo=aux_desafio.monstruo.ataqueBaseMonstruo+5;
                aux_desafio.monstruo.vidaBaseMonstruo  =aux_desafio.monstruo.vidaBaseMonstruo*1.5;
                aux_desafio.monstruo.puntosMonstruo    =aux_desafio.monstruo.puntosMonstruo*2;
            }
            adaArbolDesa[2].arbol=insertarNodoArbolDesafio(adaArbolDesa[2].arbol,aux_desafio);
        }
    }
    fclose(archi);

}

void muestraArchiDesafios(){
    REGdesafio desafio;
    FILE *archi= fopen(DESAFIOS,"rb");
    printf("----- DESAFIOS -----\n");
    while(fread(&desafio,sizeof(REGdesafio),1,archi)>0){
          printf("%d-%c-%s-%d-%d-%s,%d\n",desafio.idDesafio,desafio.tipoDesafio,desafio.descripcionDesafio,desafio.dificultadDesafio,desafio.idMonstruo,desafio.preguntaProxDesafio,desafio.desafioEliminado);
    }
    fclose(archi);
}

void muestraArchiMonstruos(){
    STmonstruo monstruo;
    FILE *archi= fopen("monstruos.dat","rb");
    printf("----- MONSTRUOS -----\n");
    while(fread(&monstruo,sizeof(STmonstruo),1,archi)>0){
          printf("%d-%s-%d-%d-%d\n",monstruo.idMonstruo,monstruo.nombreMonstruo,monstruo.vidaBaseMonstruo,monstruo.ataqueBaseMonstruo,monstruo.puntosMonstruo);
    }
    fclose(archi);
}


void altaREGdesafio(){
    REGdesafio desafio;
    FILE *archi= fopen(DESAFIOS,"ab");

    char control='s';

    while(control=='s'){
        system("cls");
        REGdesafio desafio;
        printf("\nIdDesafio: ");
        fflush(stdin);
        scanf("%d",&desafio.idDesafio);

        printf("\nTipo desaf%co: ", 161);
        fflush(stdin);
        scanf("%c",&desafio.tipoDesafio);

        printf("\nDescripci%cn: ", 162);
        fflush(stdin);
        gets(desafio.descripcionDesafio);

        printf("\nDificultad: ");
        fflush(stdin);
        scanf("%d",&desafio.dificultadDesafio);

        if (desafio.tipoDesafio == 'P'){
            printf("\nIdMonstruo: ");
            fflush(stdin);
            scanf("%d",&desafio.idMonstruo);
        }else{
            desafio.idMonstruo = -1;
        }

        printf("\nPregunta pr%cximo desafio: ", 162);
        fflush(stdin);
        gets(desafio.preguntaProxDesafio);

        printf("\nDesafio eliminado: ");
        fflush(stdin);
        scanf("%d",&desafio.desafioEliminado);

        fwrite(&desafio,sizeof(REGdesafio),1,archi);

        printf("\nDesea cargar otro?");
        fflush(stdin);
        scanf("%c",&control);

    }
    fclose(archi);
}


nodoArbolDesa* buscarDesafioEnArbolID (nodoArbolDesa* arbol, int id){
    nodoArbolDesa* rta = NULL;
    if (arbol != NULL){
        if (id == arbol->desafio.idDesafio){
            rta = arbol;
        }else{
            if (id > arbol->desafio.idDesafio){
                rta = buscarDesafioEnArbolID(arbol->derecha, id);
            }else{
                rta = buscarDesafioEnArbolID(arbol->derecha, id);
            }
        }
    }
    return rta;
}

int existeREGDesafioID (int id){
    FILE* archi = fopen(DESAFIOS, "rb");
    REGdesafio aux;
    int flag = 0;
    while (fread(&aux, sizeof(REGdesafio), 1, archi) > 0){
        if (aux.idDesafio == id);
        flag = 1;
    }
    return flag;
}

void buscarYReemplazarREGDesafio (int id, REGdesafio reemplazo){
    FILE* archi = fopen(DESAFIOS, "r+b");
    REGdesafio aux;
    int flag = 0;
    while (flag == 0 && fread(&aux, sizeof(REGdesafio), 1, archi) > 0 ){
        if (aux.idDesafio == id){
            fseek(archi, sizeof(REGdesafio)*(-1), SEEK_CUR);
            fwrite(&reemplazo, sizeof(REGdesafio), 1, archi);
            flag = 1;
        }
    }
    fclose(archi);
}

REGdesafio REGparaReemplazar (int id){
    REGdesafio desafio;

    printf("\n\nIngrese los nuevos datos:\n");
    printf("\nTipo desaf%co: ", 161);
    fflush(stdin);
    scanf("%c",&desafio.tipoDesafio);
    printf("\nDescripci%cn: ", 162);
    fflush(stdin);
    gets(desafio.descripcionDesafio);
    if (desafio.tipoDesafio == 'P'){
        printf("\nIdMonstruo: ");
        fflush(stdin);
        scanf("%d",&desafio.idMonstruo);
    }else{
        desafio.idMonstruo = -1;
    }
    printf("\nPregunta pr%cximo desafio: ", 162);
    fflush(stdin);
    gets(desafio.preguntaProxDesafio);
    desafio.desafioEliminado = 0;
    desafio.dificultadDesafio = 1;
    desafio.idDesafio = id;

    return desafio;
}


void reemplazarNodoDesafio (nodoArbolDesa* nodo, REGdesafio desafio){
    STdesafio aux;
    STmonstruo aux_monstruo;

    aux.tipoDesafio = desafio.tipoDesafio;
    strcpy(aux.descripcionDesafio, desafio.descripcionDesafio);
    strcpy(aux.preguntaProxDesafio, desafio.preguntaProxDesafio);
    aux.desafioEliminado = aux.desafioEliminado;
    aux.dificultadDesafio = desafio.dificultadDesafio;
    buscarMonstruoPorId(desafio.idMonstruo, &aux_monstruo);
    aux.monstruo = aux_monstruo;
    nodo->desafio = aux;
}
