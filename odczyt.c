#include<stdio.h>
#include<stdlib.h>
#include "pobr.h"
#include "oplik.h"
#include "strukobr.h"

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
    char *kolor;
    char *nazwa_pliku_wy;
    FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
    int negatyw,progowanie,konturowanie,wyswietlenie,konwersja;      /* opcje */
    int w_progu;              /* wartosc progu dla opcji progowanie */ 

}   t_opcje;

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(t_opcje * wybor) {
  wybor->kolor="-";
  wybor->nazwa_pliku_wy=NULL;
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->negatyw=0;
  wybor->konturowanie=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
  wybor->konwersja=0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wyb�r, do tego ustawia na 1 pola dla opcji, ktore  */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne            */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor) {
int i, prog;
char *nazwa_pliku_we;

wyzeruj_opcje(wybor);
wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
    return B_NIEPOPRAWNAOPCJA; 
    
    switch (argv[i][1]) {
        case 'i': {                 /* opcja z nazwa pliku wejsciowego */
            if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
                nazwa_pliku_we=argv[i];
                if (strcmp(nazwa_pliku_we,"-")==0) {
                    wybor->plik_we=stdin;
                } else {
                    wybor->plik_we=fopen(nazwa_pliku_we,"r");
                } /* gdy nazwa jest "-"        */
                  /* ustwiamy wejscie na stdin *//* otwieramy wskazany plik   */
            } else {
                return B_BRAKNAZWY;
            }

            break;
        }
        case 'o':  {                 /* opcja z nazwa pliku wyjsciowego */
            if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
                wybor->nazwa_pliku_wy=argv[i];
                if (strcmp(wybor->nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
                    wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
                else                              /* otwieramy wskazany plik    */
                    wybor->plik_wy=fopen(wybor->nazwa_pliku_wy,"w");
            } else {
                return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
            }

            break;
        }
        case 'p': {
            if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
                if (sscanf(argv[i],"%d",&prog)==1) {
                    wybor->progowanie=1;
                    wybor->w_progu=prog;
                } else {
                    return B_BRAKWARTOSCI;
                }
            } else {
                return B_BRAKWARTOSCI;
            }

            break;
        }
        case 'm': {                 /* mamy wykonac negatyw */
            if (++i<argc) { 
                wybor->kolor=argv[i];
                if (strcmp(wybor->kolor,"s")==0)
                    wybor->konwersja=1;
            } else 
                return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
        
            break;
        }

        case 'n': {                 /* mamy wykonac negatyw */
            wybor->negatyw=1;
            break;
        }

        case 'k': {                 /* mamy wykonac konturowanie */
            wybor->konturowanie=1;
            break;
        }

        case 'd': {                 /* mamy wyswietlic obraz */
            wybor->wyswietlenie=1;
            break;
        }

        default:                    /* nierozpoznana opcja */
            return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
} /* koniec for */

if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}


/*******************************************************/
/* Testowe wywo�anie funkcji przetwarzaj_opcje         */
/* PRE:                                                */
/*      brak                                           */
/* POST:                                               */
/*      brak                                           */
/*******************************************************/
//./a.out -i plik.ppm -n -o plik2.ppm
// argc 6
// argv ./a.out -i plik.ppm -n -o plik2.ppm
//argv[2] plik.ppm 
//argv[2][3] k


/* int a = 10 */
/* *pointer = &a */
/* *pointer = 10 */

int main(int argc, char ** argv) {
    t_opcje opcje;
    obr obrazek;

    int kod_bledu;
    int odczytano = 0;

    inicjuj(&obrazek);

    kod_bledu = przetwarzaj_opcje(argc, argv, &opcje);

    if (kod_bledu) {
        printf("Blad nr %d\n", kod_bledu);
    } else {
        if (opcje.plik_we != NULL) {       
            odczytano = czytaj(opcje.plik_we ,&obrazek);
            fclose(opcje.plik_we);
        }    
        
        if(opcje.konwersja) {
            konwersja(&obrazek);
        }

        if(opcje.negatyw) { 
            int ilek;
            
            for(ilek=0; opcje.kolor[ilek]; ilek++) {
                negatyw(&obrazek,opcje.kolor[ilek]);
            }
        }
            
        if(opcje.konturowanie) {
            konturowanie(&obrazek);
        }

        if(opcje.progowanie) {
            progowanie(&obrazek,opcje.w_progu);
        }

        zapis(opcje.plik_wy, &obrazek);
        fclose(opcje.plik_wy);

        if(opcje.wyswietlenie) {
            wyswietl(opcje.nazwa_pliku_wy);
        }
    }

    return kod_bledu;
}
/*
Anatolii Shevchuk 261049 
31.12.2021




Testy programu:

test ma na celu sprawdzic poprawnosc dzialania programu dla modyfikacji obrazkow.

[TEST 1]
Testujemy program przetwrarzania obrazow przez  czarno-bialy obrazek.
po wywolaniu skryptu "make"- gcc -o obrazy2 pobr.o oplik.o strukobr.o odczyt.c -lm
sprawdzamy poprawnosc dzialania przez plik z formatem ppm ,pgm - ./obrazy2 (parametry) 
program dziala poprawnie, po wywolaniu komendy tworzy nowy plik z zmodyfikowanym obrazkiem w formacie ppm ,pgm.

 [TEST 2]
Testujemy program przetwrarzania obrazow przez  kolorowy obrazek.
po wywolaniu skryptu "make"- gcc -o obrazy2 pobr.o oplik.o strukobr.o odczyt.c -lm
sprawdzamy poprawnosc dzialania przez plik z formatem ppm ,pgm - ./obrazy2 (parametry) 
program dziala poprawnie, po wywolaniu komendy tworzy nowy plik z zmodyfikowanym obrazkiem w formacie ppm ,pgm.

[TEST 3]
Testujemy program na funkcje zapisu w ppm,pgm.
Program dziala poprawnie, po wywolaniu ./obrazy2(parametry)
plik  formacie ppm mozemy zapisac w formacie pgm
plik pgm w format ppm

[TEST 4]
Testujemy program na niepoprawny format dla programu.
Program dziala poprawnie,po wywolaniu ./obrazy2 (parametry)
mamy blad ze to nie jest poprawny format .

[TEST 5]
Testujemy program na niepoprawnosc wpisania opcij dla obrazka w ./obrazy2 (parametry)
po wywolaniu,zostanie wpisany blad "-1" "-4" oraz tworzy  pusty plik.

[TEST 6]
Testujemy program na opcje:
przyklad wywolania programu:
1. make
2. ./obrazy2 -d -i obrazek.ppm -n -o obrazek2.pgm -m r
Wszystkie opcje dzialaja poprawnie

KOMENTARZ:
program dziala wylacznie z formatem .ppm .pgm 
*/
