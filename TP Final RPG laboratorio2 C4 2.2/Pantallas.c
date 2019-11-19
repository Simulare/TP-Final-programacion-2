#include "Pantallas.h"

void dibujaCaja(int x1, int y1,int x2,int y2){
    /// limpio la zona
    for (int y=y1; y<=y2; y++) {
        for (int x=x1; x<=x2; x++) {
            gotoxy(x,y);
            printf("%c",' ');
        }
    }
    /// renglon de arriba
    for (int x=x1; x<x2; x++) {
        gotoxy(x,y1);
        printf("%c",C_LIN);
    }
    /// renglon de abajo
    for (int x=x1; x<x2; x++) {
        gotoxy(x,y2);
        printf("%c",C_LIN);
    }
    /// columna derecha
    for (int y=y1; y<y2; y++) {
        gotoxy(x1,y);
        printf("%c",C_COL);
    }
    /// columna izquierda
    for (int y=y1; y<y2; y++) {
        gotoxy(x2,y);
        printf("%c",C_COL);
    }
    /// esquinitas
    gotoxy(x1,y1);
    printf("%c",C_ESI);
    gotoxy(x2,y1);
    printf("%c",C_ESD);
    gotoxy(x1,y2);
    printf("%c",C_EII);
    gotoxy(x2,y2);
    printf("%c",C_EID);
}

void dibujaPantallaMuerte(){
printf("\n\n\n\n\n\n\n\n\n\n\n\n");
printf("                                                                                                           _       \n");
printf("                                                                                                         _( (~\\    \n");
printf("                                                  _ _                        /                          ( \\> > \\   \n");
printf("                                              -/~/ / ~\\                     :;                \\       _  > /(~\\/   \n");
printf("                                             || | | /\\ ;\\                   |l      _____     |;     ( \\/    > >   \n");
printf("                                             _\\\\)\\)\\)/ ;;;                  `8o __-~     ~\\   d|      \\      //  \n");
printf("                                            ///(())(__/~;;\\                  '88p;.  -. _\\_;.oP        (_._/ /     \n");
printf("                                           (((__   __ \\\\   \\                  `>,%% (\\  (\\./)8'         ;:'  i     \n");
printf("                                           )))--`.'-- (( ;,8 \\               ,;%%%%%%:  ./V^^^V'          ;.   ;.     \n");
printf("                                           ((\\   |   /)) .,88  `: ..,,;;;;,-::::::'_::\\   ||\\         ;[8:   ;     \n");
printf("                                            )|  ~-~  |(|(888; ..``'::::8888oooooo.  :\\`^^^/,,~--._    |88::  |     \n");
printf("                                            |\\ -===- /|  \\8;; ``:.      oo.8888888888:`((( o.ooo8888Oo;:;:'  |     \n");
printf("                                            |_~-___-~_|   `-\\.   `        `o`88888888b` )) 888b88888P'''     ;     \n");
printf("                                            ; ~~~~;~~         '`--_`.       b`888888888;(.,'888b888'  ..::;-'      \n");
printf("                                              ;      ;              ~'-....  b`8888888:::::.`8888. .:;;;''         \n");
printf("                                                 ;    ;                 `:::. `:::OOO:::::::.`OO' ;;;''            \n");
printf("                                            :       ;                     `.      '``::::::''    .'                \n");
printf("                                               ;                           `.   \\_              /                  \n");
printf("                                             ;       ;                       +:   ~~--  `:'  -';                   \n");
printf("                                                                              `:         : .::/                    \n");
printf("                                                 ;                            ;;+_  :::. :..;;;                    \n");
printf("                                                                               ;;;;;;,;;;;;;;;,;                    \n");
printf("\n");
printf("\n");
printf("                                                                ___  ______________ _____ _____ _____ _____ \n");
printf("                                                                |  \\/  |  _  | ___ \\_   _/  ___|_   _|  ___|\n");
printf("                                                                | .  . | | | | |_/ / | | \\ `--.  | | | |__  \n");
printf("                                                                | |\\/| | | | |    /  | |  `--. \\ | | |  __| \n");
printf("                                                                | |  | \\ \\_/ / |\\ \\ _| |_/\\__/ / | | | |___ \n");
printf("                                                                \\_|  |_/\\___/\\_| \\_|\\___/\\____/  \\_/ \\____/ \n");
printf("\n\n\n\n\n\n\n\n\n\n\n\n");
}



void dibujaMonstruoDesdeTXT(int x, int y, char nombreMonstruo[]){
    char nombreArchi[34];
    char linea[81];

    strcpy(nombreArchi,nombreMonstruo);
    strcat(nombreArchi,".txt");

    ///printf("Archi=%s\n\n",nombreArchi);

    FILE *archi= fopen(nombreArchi,"r");

    gotoxy(x,y);
    while(fgets(&linea,sizeof(linea),archi)>0){
        gotoxy(x,whereY());
        printf("%s",linea);
    }
    fclose(archi);
}

void dibujaPantallaPresentaDesdeTXT(int x, int y, char nombreMonstruo[]){
    char nombreArchi[34];
    char linea[81];

    strcpy(nombreArchi,nombreMonstruo);
    strcat(nombreArchi,".txt");

    ///printf("Archi=%s\n\n",nombreArchi);

    FILE *archi= fopen(nombreArchi,"r");

    gotoxy(x,y);
    while(fgets(&linea,sizeof(linea),archi)>0){
        gotoxy(x,whereY());
        printf("%s",linea);
    }
    fclose(archi);
}
