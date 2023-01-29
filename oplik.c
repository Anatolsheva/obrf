
#include "oplik.h"


/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

int czytaj(FILE *plik_we,obr *obrazek) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return (0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || ((buf[1]!='2') && (buf[1]!='3'))|| koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }
  
  obrazek->znak=buf[1];
  
  /* Pominiecie komentarzy */
  do 
  {
    if ((znak=fgetc(plik_we))=='#') 
    {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  
    else 
    {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } 
  while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */
                                    
                                    
 
 if(obrazek->obraz_pgm!=NULL)
  {
     for (i=0;i<obrazek->wymy;i++)
     	free(obrazek->obraz_pgm[i]);
     	
     	free(obrazek->obraz_pgm);
  
  }
  
   if(obrazek->obraz_ppm_R!=NULL)
  {
     for (i=0;i<obrazek->wymy;i++)
     	free(obrazek->obraz_ppm_R[i]);
     	
     	free(obrazek->obraz_ppm_R);
  
  }
  
   if(obrazek->obraz_ppm_G!=NULL)
  {
     for (i=0;i<obrazek->wymy;i++)
     	free(obrazek->obraz_ppm_G[i]);
     	
     	free(obrazek->obraz_ppm_G);
  
  }
  
   if(obrazek->obraz_ppm_B!=NULL)
  {
     for (i=0;i<obrazek->wymy;i++)
     	free(obrazek->obraz_ppm_B[i]);
     	
     	free(obrazek->obraz_ppm_B);
  
  }
  
  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&obrazek->wymx,&obrazek->wymy,&obrazek->szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
 if(obrazek->znak=='2')
 {
  obrazek->obraz_pgm=(int**)malloc(obrazek->wymy*sizeof(int*));
   for (i=0;i<obrazek->wymy;i++)
  obrazek->obraz_pgm[i]=(int*)malloc(obrazek->wymx*sizeof(int));
  
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obrazek->wymy;i++) {
    for (j=0;j<obrazek->wymx;j++) {
      if (fscanf(plik_we,"%d",&(obrazek->obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  }
  else if(obrazek->znak=='3')
  {
   obrazek->obraz_ppm_R=(int**)malloc(obrazek->wymy*sizeof(int*));
      obrazek->obraz_ppm_G=(int**)malloc(obrazek->wymy*sizeof(int*));
         obrazek->obraz_ppm_B=(int**)malloc(obrazek->wymy*sizeof(int*));
   for (i=0;i<obrazek->wymy;i++)
   { 
   obrazek->obraz_ppm_R[i]=(int*)malloc(obrazek->wymx*sizeof(int));
   obrazek->obraz_ppm_G[i]=(int*)malloc(obrazek->wymx*sizeof(int));
   obrazek->obraz_ppm_B[i]=(int*)malloc(obrazek->wymx*sizeof(int));
   }
 
  
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obrazek->wymy;i++) {
    for (j=0;j<obrazek->wymx;j++) {
      if (fscanf(plik_we,"%d %d %d",&(obrazek->obraz_ppm_R[i][j]),&(obrazek->obraz_ppm_G[i][j]),&(obrazek->obraz_ppm_B[i][j]))!=3) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  }
  
  return (obrazek->wymx) * (obrazek->wymy);   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

void zapis(FILE *plik_wy,obr *obrazek)
{
int i,j;
if(obrazek->znak=='2')
{
    fprintf(plik_wy,"P2\n");
       fprintf(plik_wy,"%d %d\n",obrazek->wymx,obrazek->wymy);
        fprintf(plik_wy,"%d\n",obrazek->szarosci);
        
        for( i=0; i<obrazek->wymy; i++)
        {
                
        for( j=0; j<obrazek->wymx; j++)
        {
           fprintf(plik_wy,"%d ",obrazek->obraz_pgm[i][j]);
        }
             fprintf(plik_wy,"\n");
        }
        }
        else
        {
            fprintf(plik_wy,"P3\n");
       fprintf(plik_wy,"%d %d\n",obrazek->wymx,obrazek->wymy);
        fprintf(plik_wy,"%d\n",obrazek->szarosci);
        
        for( i=0; i<obrazek->wymy; i++)
        {
                
        for( j=0; j<obrazek->wymx; j++)
        {
           fprintf(plik_wy,"%d %d %d ",obrazek->obraz_ppm_R[i][j],obrazek->obraz_ppm_G[i][j],obrazek->obraz_ppm_B[i][j]);
        }
             fprintf(plik_wy,"\n");
        }
        
        
        }

}

