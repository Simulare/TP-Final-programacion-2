#ifndef HISTORIALDEJUGADAS_H_INCLUDED
#define HISTORIALDEJUGADAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int idUsuario;
    char fechaHoraJugada[17];
    int dificultadJugada;
    int resultado;  // 1=Gano / 2=Perdio
    int turnosTotalesJugados;
    int puntosGanados;
}historialDeJugadas;

void muestraHistorialJugadas(int idUsuario);
void guardarHitoricoJugadas(historialDeJugadas historial);
#endif // HISTORIALDEJUGADAS_H_INCLUDED
