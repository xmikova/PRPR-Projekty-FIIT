#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int v(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4, char ***p5, unsigned long long int *p6, unsigned int *zaznamy)
{
  unsigned long long int id, datum;
  char modul[10], typ[10], cas[10];
  double hodnota;

  if (*fr == NULL)
  {
    *fr = fopen("dataloger.txt", "r");
  }

  if (*fr == NULL)
  {
    printf("Neotvoreny subor\n");
    return 0;
  }

  fseek(*fr, 0, SEEK_SET);

  if (p1 != NULL && *p2 != NULL && *p3 != NULL && p4 != NULL && *p5 != NULL && p6 != NULL) /*ak polia su uz alokovane, vypise z poli*/
  {
    for (int i = 0; i < *zaznamy; i++)
    {
      /*pri volani tejto funkcie po zavolani funkcie "z" nasledujuca podmienka vynecha vymazane zaznamy, je pouzita aj dalej pri funkciach kt.
      vyuzivaju vytvorene dynamicke polia*/
      if (p1[i] == '\0' && (*p2)[i] == NULL && (*p3)[i] == NULL && p4[i] == '\0' && (*p5)[i] == NULL && p6[i] == '\0')
      {
        continue;
      }
      printf("ID cislo mer. osoby: %llu\n", p1[i]);
      printf("Mer. modul: %s\n", (*p2)[i]);
      printf("Typ mer. veliciny: %s\n", (*p3)[i]);
      printf("Hodnota: %lf\n", p4[i]);
      printf("Cas merania: %s\n", (*p5)[i]);
      printf("Datum: %llu\n", p6[i]);
      printf("\n");
    }
  }
  else /*vypise priamo zo suboru*/
  {
    do
    {
      fscanf(*fr, "%llu \n %s \n %s \n %lf \n %s \n %llu \n", &id, modul, typ, &hodnota, cas, &datum);
      printf("ID cislo mer. osoby: %llu\n", id);
      printf("Mer. modul: %s\n", modul);
      printf("Typ mer. veliciny: %s\n", typ);
      printf("Hodnota: %lf\n", hodnota);
      printf("Cas merania: %s\n", cas);
      printf("Datum: %llu\n", datum);
      printf("\n");
    } while (!feof(*fr));
  }
}

int dealokuj_polia(unsigned long long int *p1, char ***p2, char ***p3, double *p4, char ***p5, unsigned long long int *p6,unsigned int *zaznamy) 
/*funkcia pre dealokaciu poli, osetrene ak uz vo funkcii "z" niektore zaznamy boli prealokovane na NULL*/
{
  int i;

  free(p1);
  p1 = NULL;

  for (i = 0; i < *zaznamy; i++)
  {
    free((*p2)[i]);
    if ((*p2)[i] == NULL)
    {
      continue;
    }
    else
    {
      (*p2)[i] = NULL;
    }
  }
  free(*p2);
  *p2 = NULL;

  for (i = 0; i < *zaznamy; i++)
  {
    free((*p3)[i]);
    if ((*p3)[i] == NULL)
    {
      continue;
    }
    else
    {
      (*p3)[i] = NULL;
    }
  }
  free(*p3);
  *p3 = NULL;

  free(p4);
  p4 = NULL;

  for (i = 0; i < *zaznamy; i++)
  {
    free((*p5)[i]);
    if ((*p5)[i] == NULL)
    {
      continue;
    }
    (*p5)[i] = NULL;
  }
  free(*p5);
  *p5 = NULL;

  free(p6);
  p6 = NULL;

  return 0;
}

int n(FILE **fr, unsigned long long int **p1, char ***p2, char ***p3, double **p4, char ***p5, unsigned long long int **p6, unsigned int *zaznamy)
{
  int cntr = 0;
  unsigned long long int id, datum;
  char modul[10], typ[10], cas[10], arr[255], s;
  double hodnota;

  if (*fr != NULL)
  {
    fseek(*fr, 0, SEEK_SET);
  }
  else
  {
    printf("Neotvoreny subor.\n");
    return 0;
  }
  if (p1 != NULL && *p2 != NULL && *p3 != NULL && p4 != NULL && *p5 != NULL && p6 != NULL)
  {
    dealokuj_polia(*p1, p2, p3, *p4, p5, *p6, zaznamy);
  }
  while ((s = fscanf(*fr, "%s", arr)) != EOF) /*skenuje bez prazdnych riadkov, teda priamo dostanem len pocet riadkov so zaznamami*/
  { 
    if (s != '\n')
    {
      cntr++;
    }
  }

  *zaznamy = cntr / 6; /*pocet zaznamov, kazdy zaznam pozostava zo 6 udajov*/

  *p1 = (unsigned long long int *)malloc(*zaznamy * sizeof(unsigned long long int));
  *p2 = malloc(*zaznamy * sizeof(char *));
  *p3 = malloc(*zaznamy * sizeof(char *));
  *p4 = (double *)malloc(*zaznamy * sizeof(double));
  *p5 = malloc(*zaznamy * sizeof(char *));
  *p6 = (unsigned long long int *)malloc(*zaznamy * sizeof(unsigned long long int));

  fseek(*fr, 0, SEEK_SET);

  int i = 0;
  do
  {
    fscanf(*fr, "%llu \n %s \n %s \n %lf \n %s \n %llu \n", &id, modul, typ,
           &hodnota, cas, &datum);
    (*p1)[i] = id;
    (*p2)[i] = malloc(4 * sizeof(char));
    strcpy((*p2)[i], modul);
    (*p3)[i] = malloc(3 * sizeof(char));
    strcpy((*p3)[i], typ);
    (*p4)[i] = hodnota;
    (*p5)[i] = malloc(5 * sizeof(char));
    strcpy((*p5)[i], cas);
    (*p6)[i] = datum;
    i++;
  } while (!feof(*fr));

  return 0;
}

int o(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4, char ***p5, unsigned long long int *p6, unsigned int *zaznamy)
{
  char mm[100], tmr[100];
  int pole_poz[57], pom = 0, j = 0, i = 0, cntr = 0;

  if (*fr == NULL)
  {
    printf("Neotvoreny subor.\n");
    return 0;
  }

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL && p6 == NULL)
  {
    n(fr, &p1, p2, p3, &p4, p5, &p6, zaznamy); /*ak este neboli polia alokovane, alokujem si ich a na konci dealokujem, kedze "n" stlacene nebolo*/
    scanf("%s %s", mm, tmr);

    for (i = 0; i < *zaznamy; i++)
    {
      if (p1[i] == '\0' && (*p2)[i] == NULL && (*p3)[i] == NULL && p4[i] == '\0' && (*p5)[i] == NULL && p6[i] == '\0')
      {
        continue;
      }
      else
      {
        if (strcmp(((*p2)[i]), mm) == 0 && strcmp(((*p3)[i]), tmr) == 0)
        {
          pole_poz[j] = i; /*do pomocneho pola si ulozim pozicie v dynam. poliach, na ktorych su udaje zhodne so vstupom od uzivatela*/
          j++;
          cntr++;
        }
      }
    }

    /*na sortovanie pouzivam bubble sort*/
    for (i = 0; i < cntr - 1; i++)
    {
      for (j = 0; j < cntr - i - 1; j++)
      {
        if (((p6[pole_poz[j]] > p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) <= atoi((*p5)[pole_poz[j + 1]]))) ||
            ((p6[pole_poz[j]] == p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) > atoi((*p5)[pole_poz[j + 1]])))) /*podmienky aby sortovalo aj podla datumu aj podla casu*/
        {
          pom = pole_poz[j + 1];
          pole_poz[j + 1] = pole_poz[j];
          pole_poz[j] = pom;
        }
      }
    }

    for (i = 0; i < cntr; i++)
    {
      printf("%s\t%s\t%llu\t%s\t%f\n", (*p2)[pole_poz[i]], (*p3)[pole_poz[i]], p6[pole_poz[i]], (*p5)[pole_poz[i]], p4[pole_poz[i]]);
    }
    dealokuj_polia(p1, p2, p3, p4, p5, p6, zaznamy);
  }
  else /*rovnaky algoritmus, len pripad kde n uz bolo stlacene*/
  {
    scanf("%s %s", mm, tmr);

    for (i = 0; i < *zaznamy; i++)
    {
      if (p1[i] == '\0' && (*p2)[i] == NULL && (*p3)[i] == NULL && p4[i] == '\0' && (*p5)[i] == NULL && p6[i] == '\0')
      {
        continue;
      }
      else
      {
        if (strcmp(((*p2)[i]), mm) == 0 && strcmp(((*p3)[i]), tmr) == 0)
        {
          pole_poz[j] = i;
          j++;
          cntr++;
        }
      }
    }

    for (i = 0; i < cntr - 1; i++)
    {
      for (j = 0; j < cntr - i - 1; j++)
      {
        if (((p6[pole_poz[j]] > p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) <= atoi((*p5)[pole_poz[j + 1]]))) ||
            ((p6[pole_poz[j]] == p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) > atoi((*p5)[pole_poz[j + 1]]))))
        {
          pom = pole_poz[j + 1];
          pole_poz[j + 1] = pole_poz[j];
          pole_poz[j] = pom;
        }
      }
    }

    for (i = 0; i < cntr; i++)
    {
      printf("%s\t%s\t%llu\t%s\t%lf\n", (*p2)[pole_poz[i]], (*p3)[pole_poz[i]], p6[pole_poz[i]], (*p5)[pole_poz[i]], p4[pole_poz[i]]);
    }
  }
  return 0;
}

int r(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4, char ***p5, unsigned long long int *p6, unsigned int *zaznamy)
{
  int i, j;
  char **pole_casy, hod[3], min[3], last_hod[3], last_min[3], pom[5];

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL && p6 == NULL)
  {
    printf("Polia nie su vytvorene.\n");
    return 0;
  }
  pole_casy = malloc((*zaznamy) * sizeof(char *)); /*vytvorim si pomocne pole, v ktorom si povodne pole s casmi zoradim vzostupne cez bubblesort*/

  for (i = 0; i < *zaznamy; i++)
  {
    if (p1[i] == '\0' && (*p2)[i] == NULL && (*p3)[i] == NULL && p4[i] == '\0' && (*p5)[i] == NULL && p6[i] == '\0')
    {
      continue;
    }
    else
    {
      pole_casy[i] = malloc(5 * sizeof(char));
      strcpy(pole_casy[i], (*p5)[i]);
    }
  }

  for (i = 0; i < *zaznamy - 1; i++)
  {
    for (j = 0; j < *zaznamy - i - 1; j++)
    {
      if (atoi(pole_casy[j]) > atoi(pole_casy[j + 1]))
      {
        strcpy(pom, pole_casy[j + 1]);
        strcpy(pole_casy[j + 1], pole_casy[j]);
        strcpy(pole_casy[j], pom);
      }
    }
  }

  for (i = 0; i < *zaznamy; i++)
  {
    memcpy(hod, pole_casy[i], 2);
    strcpy(min, &pole_casy[i][2]);

    if (i == 0)
    {
      printf("%s:", hod);
      strcpy(last_hod, hod);
      printf("%s", min);
      strcpy(last_min, min);
    }
    else
    {
      if (atoi(hod) > atoi(last_hod))
      {
        printf("\n%s:", hod);
        strcpy(last_hod, hod);
        printf("%s", min);
        strcpy(last_min, min);
      }
      else
      {
        if ((atoi(hod) == atoi(last_hod)) && (atoi(min) == atoi(last_min)))
        {
          continue;
        }
        else
        {
          printf(", %s", min);
          strcpy(last_min, min);
        }
      }
    }
  }
  printf("\n");
  return 0;
}

int h(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4, char ***p5, unsigned long long int *p6, unsigned int *zaznamy)
{
  char tmv[10];
  int i = 0, j = 0, cntr = 0, pom = 0, cntr_hist = 0, min = 0, max = 5, vel_pol = 0, pos = 0, pole_poz[100], *pocetnost;
  double del;

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL && p6 == NULL)
  {
    printf("Polia nie su vytvorene.\n");
    return 0;
  }

  scanf("%s", tmv);

  for (i = 0; i < *zaznamy; i++)
  {
    if (p1[i] == '\0' && (*p2)[i] == NULL && (*p3)[i] == NULL && p4[i] == '\0' && (*p5)[i] == NULL && p6[i] == '\0')
    {
      continue;
    }
    else
    {
      if (strcmp(((*p3)[i]), tmv) == 0)
      {
        pole_poz[j] = i; /*pomocne pole s poziciami v dynam. poliach kde sa udaje zhoduju so vstupom*/
        j++;
        cntr++;
      }
    }
  }

  /*usporiadam si pole pozicii podla toho ako idu hodnoty v povodnom poli vzostupne cez bubblesort*/
  for (i = 0; i < cntr - 1; i++)
  {
    for (j = 0; j < cntr - i - 1; j++)
    {
      if (p4[pole_poz[j]] > p4[pole_poz[j + 1]])
      {
        pom = pole_poz[j + 1];
        pole_poz[j + 1] = pole_poz[j];
        pole_poz[j] = pom;
      }
    }
  }

  vel_pol = ceil((p4[pole_poz[cntr - 1]]) / 5); /*zistim si pocet intervalov; najvacsiu hodnotu vydelim 5 a zaokruhlim nahor pomocou funkcie ceil*/

  pocetnost = (int *)malloc(vel_pol * sizeof(int)); /*alokujem si pole kde budem ukladat pocetnost pre dane intervaly*/
  for (i = 0; i < vel_pol; i++)
  {
    pocetnost[i] = 0;
  }

  for (i = 0; i < cntr; i++)
  {
    del = floor(p4[pole_poz[i]] / 5); /*hodnotu pre typ meranej veliciny zhodnej so vstupom vydelim 5 a zaokruhlim nadol, cim zistim do ktoreho intervalu patri*/
    pos = (int)del;
    pocetnost[pos] = pocetnost[pos] + 1; /*do pola ukladam pocet hodnot v intervaloch*/
  }

  printf("\t%s\t\tpocetnost\n", tmv);

  for (i = 0; i < vel_pol; i++)
  {
    if (pocetnost[i] > 0)
    {
      printf("(%3d.0-\t%3d.0>\t   \t    %d\n", min, max, pocetnost[i]);
    }
    min = max;
    max += 5;
  }
  return 0;
}

int s(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4, char ***p5, unsigned long long int *p6, unsigned int *zaznamy)
{
  FILE *fw;
  char mm[10], tmr[10];
  int pole_poz[57];
  double *merania;
  int pom = 0, j = 0, i = 0, cntr = 0;

  fw = fopen("vystup_S.txt", "w");

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL && p6 == NULL)
  {
    printf("Polia nie su vytvorene.\n");
    return 0;
  }

  scanf("%s %s", mm, tmr);

  for (i = 0; i < *zaznamy; i++)
  {
    if (p1[i] == '\0' && (*p2)[i] == NULL && (*p3)[i] == NULL && p4[i] == '\0' && (*p5)[i] == NULL && p6[i] == '\0')
    {
      continue;
    }
    else
    {
      if (strcmp(((*p2)[i]), mm) == 0 && strcmp(((*p3)[i]), tmr) == 0)
      {
        pole_poz[j] = i; /*pomocne pole s poziciami v dynam. poliach kde sa udaje zhoduju so vstupom*/
        j++;
        cntr++;
      }
    }
  }

  if (cntr == 0)
  {
    printf("Pre dany vstup neexistuju zaznamy.\n");
    return 0;
  }

  /*bubblesort pre datum a cas vzostupne*/
  for (i = 0; i < cntr - 1; i++)
  {
    for (j = 0; j < cntr - i - 1; j++)
    {
      if (((p6[pole_poz[j]] > p6[pole_poz[j + 1]]) &&
           (atoi((*p5)[pole_poz[j]]) <= atoi((*p5)[pole_poz[j + 1]]))) ||
          ((p6[pole_poz[j]] == p6[pole_poz[j + 1]]) &&
           (atoi((*p5)[pole_poz[j]]) > atoi((*p5)[pole_poz[j + 1]]))))
      {
        pom = pole_poz[j + 1];
        pole_poz[j + 1] = pole_poz[j];
        pole_poz[j] = pom;
      }
    }
  }

  merania = (double *)malloc(cntr * sizeof(double));
  for (i = 0; i < cntr; i++)
  {
    merania[i] = p4[pole_poz[i]]; /*nove pole s nameranymi hodnotami zoradenymi podla datumu a casu vzostupne*/
  }

  for (i = 0; i <= cntr; i++)
  {
    if (i == cntr) /*v poslednom kroku vypise vetu a zavrie subor*/
    {
      printf("Pre dany vstup je vytvoreny txt subor.\n");
      fclose(fw);
    }
    else
    {
      fprintf(fw, "%llu%s\t%.7lf\n", p6[pole_poz[i]], (*p5)[pole_poz[i]],merania[i]);
    }
  }
  return 0;
}

int c(FILE **fr)
{
  double hodnota;
  char id[100], modul[10], typ[10], cas[10], hod[3], min[3], datum[10], den[3], mesiac[3];
  int i = 0, spravnost = 0;
  char tmr[9][3] = {"R1", "U1", "A1", "R2", "U2", "A2", "R4", "U4", "A4"};
  char mesiace31[7][3] = {"01", "03", "05", "07", "08", "10", "12"};
  char mesiace30[4][3] = {"04", "06", "09", "11"};

  if (*fr != NULL)
  {
    fseek(*fr, 0, SEEK_SET);
  }
  else
  {
    printf("Neotvoreny subor.\n");
    return 0;
  }

  do
  {
    int cntr1 = 0, cntr2 = 0;
    fscanf(*fr, "%s \n %s \n %s \n %lf \n %s \n %s \n ", id, modul, typ, &hodnota, cas, datum);
    if (((atoll(id)) % 11 != 0) || strlen(id) != 10)
    {
      printf("Nekorektne zadany vstup: ID cislo mer. osoby.\n");
      spravnost++;
    }
    if (isupper(modul[0]) == 0 || isdigit(modul[1]) == 0 || isdigit(modul[2]) == 0 || strlen(modul) != 3)
    {
      printf("Nekorektne zadany vstup: Mer. modul.\n");
      spravnost++;
    }
    for (i = 0; i < 9; i++)
    {
      if (strcmp(tmr[i], typ) == 0)
      {
        cntr1++;
      }
    }
    if (cntr1 == 0)
    {
      printf("Nekorektne zadany vstup: Typ mer. veliciny.\n");
      spravnost++;
    }

    if (strlen(cas) != 4)
    {
      printf("Nekorektne zadany vstup: Cas.\n");
      spravnost++;
    }
    else
    {
      strncpy(hod, cas, 2);
      strcpy(min, &cas[2]);
      if (atoi(hod) > 23 || atoi(min) > 59)
      {
        printf("Nekorektne zadany vstup: Cas.\n");
        spravnost++;
      }
    }

    if (strlen(datum) != 8)
    {
      printf("Nekorektne zadany vstup: Datum.\n");
      spravnost++;
    }
    else
    {
      strncpy(mesiac, &datum[4], 6 - 4);
      mesiac[2] = '\0'; /*kedze kopirujem zo stredu stringu musim este vlozit znak '\0'*/
      strncpy(den, datum + 6, 2);
    }
    if (atoi(mesiac) > 12)
    {
      printf("Nekorektne zadany vstup: Datum.\n");
      spravnost++;
    }
    else
    {
    for (i = 0; i < 7; i++) /*osetrenie pre mesiace kt. maju max 31 dni*/
      {
        if (strcmp(mesiace31[i], mesiac) == 0)
        {
          if (atoi(den) > 31)
          {
            printf("Nekorektne zadany vstup: Datum.\n");
            spravnost++;
          }
        }
      }
      for (i = 0; i < 4; i++) /*osetrenie pre mesiace kt. maju max 30 dni*/
      {
        if (strcmp(mesiace30[i], mesiac) == 0)
        {
          if (atoi(den) > 30)
          {
            printf("Nekorektne zadany vstup: Datum.\n");
            spravnost++;
          }
        }
      }
      if (atoi(mesiac) == 2) /*osetrenie mesiaca februar*/
      {
        if (atoi(den) > 28)
        {
          printf("Nekorektne zadany vstup: Datum.\n");
          spravnost++;
        }
      }
    }
  } while (!feof(*fr));

  if (spravnost == 0)
  {
    printf("Data su korektne.\n");
  }

  return 0;
}

int z(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4, char ***p5, unsigned long long int *p6, unsigned int *zaznamy)
{
  int i, j = 0, cntr = 0;
  unsigned long long int id;
  char pole_poz[57];

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL && p6 == NULL)
  {
    printf("Polia nie su vytvorene.\n");
    return 0;
  }

  scanf("%llu", &id);
  for (i = 0; i < *zaznamy; i++)
  {
    if (p1[i] == id)
    {
      pole_poz[j] = i; /*pomocne pole s poziciami v dynam. poliach kde sa udaje zhoduju so vstupom*/
      j++;
      cntr++;
    }
  }
  for (i = 0; i < *zaznamy; i++)
  {
    for (j = 0; j < cntr; j++)
    {
      if (i == pole_poz[j]) /*vymazanie zaznamov pre dany vstup, tieto zaznamy uz program v dalsich funkciach po zavolani tejto bude ignorovat*/
      {
        p1[i] = '\0';
        (*p2)[i] = NULL;
        (*p3)[i] = NULL;
        p4[i] = '\0';
        (*p5)[i] = NULL;
        p6[i] = '\0';
      }
    }
  }
  printf("Vymazalo sa : %d zaznamov !\n", cntr);
  return 0;
}

int main()
{
  FILE *fr = NULL;
  unsigned long long int *p1 = NULL, *p6 = NULL;
  char **p2 = NULL, **p3 = NULL, **p5 = NULL;
  double *p4 = NULL;
  unsigned int zaznamy;
  char vstup;

  do
  {
    scanf("%c", &vstup);
    switch (vstup)
    {
    case 'v':
      v(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break; 
    case 'o':
      o(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break; 
    case 'n':
      n(&fr, &p1, &p2, &p3, &p4, &p5, &p6, &zaznamy);
      break; 
    case 'h':
      h(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break; 
    case 's':
      s(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break; 
    case 'r':
      r(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break;
    case 'c':
      c(&fr);
      break;
    case 'z':
      z(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break;
    }
  } while (vstup != 'k');
  /*funkcia k:*/
  if (fr != NULL)
  {
    fclose(fr);
  }

  if (p1 != NULL && p2 != NULL && p3 != NULL && p4 != NULL && p5 != NULL && p6 != NULL)
  {
    dealokuj_polia(p1, &p2, &p3, p4, &p5, p6, &zaznamy);
  }
  return 0;
}