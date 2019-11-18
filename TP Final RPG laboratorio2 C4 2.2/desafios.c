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

STdesafio cargarDesafio (nodoMonstruo* lista){
    STdesafio aux;
    printf("\nID del desafío: ");
    fflush(stdin);
    scanf("%i", &aux.idDesafio);
    do{ ///Para verificar que sea tipo P o R
        printf("\nTipo de desaf%co ('P' pelea / 'R' recompensa): ", 161);
        fflush(stdin);
        scanf("%c", &aux.tipoDesafio);
        if (aux.tipoDesafio != 'R' && aux.tipoDesafio != 'P'){
            printf("\n\nError. El tipo de desaf%co solo puede ser 'P' o 'R'. Vuelva a intentar.\n\n", 161);
            system("pause");
            system("cls");
        }
    }while (aux.tipoDesafio != 'P' && aux.tipoDesafio != 'R');

    printf("\nDescripci%cn del desaf%co: ", 162, 161);
    fflush(stdin);
    gets(aux.descripcionDesafio);
    printf("\nDificultad del desaf%co: ", 161);
    fflush(stdin);
    scanf("%i", &aux.dificultadDesafio);
    if (aux.tipoDesafio == 'P'){
        char nombre[20];
        printf("\nIngrese el nombre del monstruo del desaf%co: ", 161);
        fflush(stdin);
        gets(nombre);
        nodoMonstruo* monster = buscarMonstruoNombre(lista, nombre);
        if (monster == NULL){
            printf("\n\nEl monstruo ingresado no existe en la lista de monstruos, si quiere ingresar un monstruo nuevo primero debe cargarlo en 'cargar monstruo'. Ser%c enviado al men%c anterior.\n\n", 160, 163);
            system("pause");
            ///MENU ANTERIOR ---------------------
        }else{
            aux.monstruo = ponerMonstruo(monster, aux.dificultadDesafio);
        }
    }else{
        aux.monstruo = monstruoVacio();
    }
    printf("\nPregunta al pr%cximo desaf%co: ", 162, 161);
    fflush(stdin);
    gets(aux.preguntaProxDesafio);
    aux.desafioEliminado = 0;

    return aux;
}

void buscarMonstruoPorId(int idMonstruo, STmonstruo *aux_monstruo){
    STmonstruo monstruo;
    FILE*archi=fopen("monstruos.dat","rb");
    int flag=0;
    while(fread(&monstruo,sizeof(STmonstruo),1,archi)>0 && flag==0){
        if(idMonstruo==monstruo.idMonstruo){
            aux_monstruo->idMonstruo=monstruo.idMonstruo;
            strcpy(aux_monstruo->nombreMonstruo,monstruo.nombreMonstruo);
            aux_monstruo->vidaBaseMonstruo=monstruo.vidaBaseMonstruo;
            aux_monstruo->ataqueBaseMonstruo=monstruo.ataqueBaseMonstruo;
            aux_monstruo->puntosMonstruo=monstruo.puntosMonstruo;

            flag=1;
        }
    }
    fclose(archi);
}

nodoArbolDesa* pasarDesafiosArchivoToArbol (nodoArbolDesa* arbolDesa){

    FILE* archi = fopen(DESAFIOS, "rb");
    REGdesafio aux_reg;
    STdesafio aux_desafio;

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
            buscarMonstruoPorId(aux_reg.idMonstruo, &aux_monstruo);
            /// los agrego a la estructura para el nodo de desafios.
            aux_desafio.monstruo=aux_monstruo;

            arbolDesa=insertarNodoArbolDesafio(arbolDesa, aux_desafio);
        }
    }
    fclose(archi);

    /*
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

    */

    return arbolDesa;
}

void muestraArchiDesafios(){
    REGdesafio desafio;
    FILE *archi= fopen(DESAFIOS,"rb");
    // printf("%d-%c-%s-%d-%d-%s,%d\n","");
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

        printf("\nIdMonstruo: ");
        fflush(stdin);
        scanf("%d",&desafio.idMonstruo);

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
