#ifndef STRUKOBR_H
#define STRUKOBR_H

#include<stdio.h>
#include<stdlib.h>
#define MAX 512    

struct obraz {
    char znak;
    int wymx;       // rozmiar tablicy
    int wymy;       //
    int szarosci;
    int **obraz_pgm;

    //sp1
    int **obraz_ppm_R;
    int **obraz_ppm_G;
    int **obraz_ppm_B;

    //sp2
    //int ***obraz_ppm;
};



typedef struct obraz obr;

void inicjuj(obr *obrazek);
#endif
