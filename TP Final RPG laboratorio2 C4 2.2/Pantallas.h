#ifndef PANTALLAS_H_INCLUDED
#define PANTALLAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "gotoxy.h"

#define C_ESI 201   // '╔'   // (201)
#define C_EII 200   // '╚'   // (200)
#define C_ESD 187   // '╗'   // (187)
#define C_EID 188   // '╝'   // (188)
#define C_LIN 205   // '═'   // (205)
#define C_COL 186   // '║'   // (186)


///void clrscr();
void dibujaCaja(int x1, int y1,int x2,int y2);
void dibujaPantallaMuerte();
void dibujaGoblin();
void dibujarPantallaGanaste();
void dibujaMonstruoDesdeTXT(int x, int y, char nombreMonstruo[]);

#endif // PANTALLAS_H_INCLUDED
