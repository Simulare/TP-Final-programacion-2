#ifndef MOUNSTRUO_H_INCLUDED
#define MOUNSTRUO_H_INCLUDED

typedef struct{
int idMounstruo;
char nombre[30];
int vidaBase;
int ataqueBase;
int puntos;
struct * siguiente;
}mounstruo;

mounstruo * iniclista();

mounstruo * crearMounstruo(char nombre[],int idMounstruo,int ataqueBase,int vidaBase,int ataqueBase,int puntos);

mounstruo * cargarMounstruo();

void mostrarMounstruos(mounstruo * listaMounstruos);

mounstruo * agregarFinal(mounstruo * listaMounstruos,mounstruo * nuevoMounstruo)

mounstruo * buscarUltimo(mounstruo * listaMounstruos);

void recorrerMostrar(mounstruo * listaMounstruos);




#endif // MOUNSTRUO_H_INCLUDED
