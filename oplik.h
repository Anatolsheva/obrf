#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strukobr.h"





#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */


int czytaj(FILE *plik_we,obr *obrazek) ;
void wyswietl(char *n_pliku) ;
void zapis(FILE *plik_wy,obr *obrazek);  
