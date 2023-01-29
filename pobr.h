
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"strukobr.h"

void konwersja(obr *obrazek);
void negatyw(obr *obrazek,char kolor)  ;
void konturowanie(obr *obrazek) ;
void rozmycie(obr *obrazek,char kolor)  ;
void histogram(obr *obrazek) ;
void progowanie(obr *obrazek,float procent) ;
void gamma_f(obr *obrazek,float gamma) ;
int poziomy(obr *obrazek,float p_biel, float p_czern) ;
