#include "historialDeJugadas.h"

void guardarHitoricoJugadas(historialDeJugadas historial){
    FILE*archi=fopen("historial.dat","ab");
    fwrite(&historial,sizeof(historial),1,archi);
    fclose(archi);
}

void muestraHistorialJugadas(int idUsuario){
    FILE*archi=fopen("historial.dat","rb");
    historialDeJugadas aux;
    char strResultado[8];
    printf("-----------------------------------------------------------------\n");
    printf("| %17s | %10s | %10s | %6s | %6s |\n","Fecha y Hora  ","Dificultad","Resultado","Turnos","Puntos");
    printf("-----------------------------------------------------------------\n");
    while(fread(&aux,sizeof(historialDeJugadas),1,archi)>0){
        if(aux.idUsuario==idUsuario){
            if(aux.resultado==1){
                strcpy(strResultado,"Ganaste  ");
            }else{
                strcpy(strResultado,"Perdiste ");
            }

            printf("| %17s | %10d | %10s | %6d | %6d |\n",aux.fechaHoraJugada,aux.dificultadJugada,strResultado,aux.turnosTotalesJugados,aux.puntosGanados);
        }
    }
    printf("-----------------------------------------------------------------\n");
}

