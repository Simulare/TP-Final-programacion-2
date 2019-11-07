#ifndef MOUNSTRUO_H_INCLUDED
#define MOUNSTRUO_H_INCLUDED

typedef struct{
    int idMonstruo;
    int nivel; ///En qué nivel del arbol va ¿?
	char nombreMonstruo[30];
	int vidaBaseMonstruo;
    int ataqueBaseMonstruo;
    int puntosMonstruo;
}STmonstruo;

typedef struct{
    STmonstruo monstruo;
    struct nodoMonstruo* sig;
    struct nodoMostruo* ante;
}nodoMonstruo;

nodoMonstruo * iniclista();

STmonstruo cargarMonstruo();

void agregarMonstruoArchivo (STmonstruo aux);

nodoMonstruo * cargarListaMonstruos(nodoMonstruo* lista);

nodoMonstruo * crearNodoMonstruo(STmonstruo monstruo);

void mostrarMonstruo(STmonstruo aux);

 void recorrerMostrar(nodoMonstruo * listaMonstruos);

nodoMonstruo* agregarFinal(nodoMonstruo* listaMonstruos, nodoMonstruo * nuevoMonstruo);

nodoMonstruo * buscarUltimo(nodoMonstruo * listaMonstruos);



#endif // MOUNSTRUO_H_INCLUDED
