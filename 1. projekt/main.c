#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int v(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4,
      char ***p5, unsigned long long int *p6, unsigned int *zaznamy) {
  unsigned long long int id, datum;
  char modul[10], typ[10], cas[10];
  double hodnota;
  char arr[255];
  char s;

  if (*fr == NULL) {
    *fr = fopen("dataloger.txt", "r");
    printf("Otvoril som.");
  }

  if (*fr == NULL) {
    printf("Neotvoreny subor\n");
    return 0;
  }

  fseek(*fr, 0, SEEK_SET);

  printf("%d %d %d %d %d %d\n", p1, *p2, *p3, p4, *p5, p6);
  if (p1 != NULL && *p2 != NULL && *p3 != NULL && p4 != NULL && *p5 != NULL &&
      p6 != NULL) {
    printf("testik");
    for (int i = 0; i < *zaznamy; i++) {
      printf("ID cislo mer. osoby: %llu\n", p1[i]);
      printf("Mer. modul: %s\n", (*p2)[i]);
      printf("Typ mer. veliciny: %s\n", (*p3)[i]);
      printf("Hodnota: %lf\n", p4[i]);
      printf("Cas merania: %s\n", (*p5)[i]);
      printf("Datum: %llu\n", p6[i]);
      printf("\n");
    }
  } else {
    printf("test");
    do {
      fscanf(*fr, "%llu \n %s \n %s \n %lf \n %s \n %llu \n", &id, modul, typ,
             &hodnota, cas, &datum);
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

int n(FILE **fr, unsigned long long int **p1, char ***p2, char ***p3,
      double **p4, char ***p5, unsigned long long int **p6,
      unsigned int *zaznamy) {
  int cntr = 0;
  unsigned long long int id, datum;
  char modul[10], typ[10], cas[10];
  double hodnota;
  char arr[255];
  char s;

  if (*fr != NULL) {
    fseek(*fr, 0, SEEK_SET);
  } else {
    printf("Neotvoreny subor.\n");
    return 0;
  }

  //*fr = fopen("dataloger.txt", "r");
  while ((s = fscanf(*fr, "%s", arr)) !=
         EOF) { // skenuje bez prazdnych riadkov teda priamo dostanem len pocet
                // riadkov so zaznamami
    if (s != '\n') {
      cntr++;
    }
  }
  printf("%d\n", cntr);

  *zaznamy = cntr / 6; // pocet zaznamov, kazdy zaznam pozostava zo 6 udajov

  *p1 = (unsigned long long int *)malloc(*zaznamy *
                                         sizeof(unsigned long long int));
  *p2 = malloc(*zaznamy * sizeof(char *));
  *p3 = malloc(*zaznamy * sizeof(char *));
  *p4 = (double *)malloc(*zaznamy * sizeof(double));
  *p5 = malloc(*zaznamy * sizeof(char *));
  *p6 = (unsigned long long int *)malloc(*zaznamy *
                                         sizeof(unsigned long long int));

  fseek(*fr, 0, SEEK_SET);
  rewind(*fr);
  printf("%d\n", *zaznamy);

  // printf("%d %d %d %d %d %d\n",p1,*p2,*p3,p4,*p5,p6);
  printf("%d %d %d %d %d %d\n", *p1, *p2, *p3, *p4, *p5, *p6);

  int i = 0;
  do {
    fscanf(*fr, "%llu \n %s \n %s \n %lf \n %s \n %llu \n", &id, modul, typ,
           &hodnota, cas, &datum);
    (*p1)[i] = id;
    (*p2)[i] = malloc(4 * sizeof(char));
    strcpy((*p2)[i], modul);
    // printf("%s\n", (*p2)[i]);
    (*p3)[i] = malloc(3 * sizeof(char));
    strcpy((*p3)[i], typ);
    // printf("%s\n", (*p3)[i]);
    (*p4)[i] = hodnota;
    (*p5)[i] = malloc(5 * sizeof(char));
    strcpy((*p5)[i], cas);
    // printf("%s\n", (*p5)[i]);
    (*p6)[i] = datum;
    i++;
  } while (!feof(*fr));

  return 0;
}

int dealokuj_polia(unsigned long long int *p1, char ***p2, char ***p3,
                   double *p4, char ***p5, unsigned long long int *p6,
                   unsigned int *zaznamy) {
  int i;

  free(p1);
  p1 = NULL;

  for (i = 0; i < *zaznamy; i++) {
    free((*p2)[i]);
    (*p2)[i] = NULL;
  }
  free(*p2);
  *p2 = NULL;

  for (i = 0; i < *zaznamy; i++) {
    free((*p3)[i]);
    (*p3)[i] = NULL;
  }
  free(*p3);
  *p3 = NULL;

  free(p4);
  p4 = NULL;

  for (i = 0; i < *zaznamy; i++) {
    free((*p5)[i]);
    (*p5)[i] = NULL;
  }
  free(*p5);
  *p5 = NULL;

  free(p6);
  p6 = NULL;

  printf("%p %p %p %p %p %p", p1, *p2, *p3, p4, *p5, p6);
  return 0;
}

int o(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4,
      char ***p5, unsigned long long int *p6, unsigned int *zaznamy) {
  char mm[10], tmr[10];
  int pole_poz[57];
  int pom = 0, j = 0, i = 0, cntr = 0;

  if (*fr == NULL) {
    printf("Neotvoreny subor.\n");
    return 0;
  }

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL &&
      p6 == NULL) {
    n(fr, &p1, p2, p3, &p4, p5, &p6, zaznamy);
    scanf("%s %s", mm, tmr);
    printf("%s %s", mm, tmr);

    for (i = 0; i < *zaznamy; i++) {
      if (strcmp(((*p2)[i]), mm) == 0 && strcmp(((*p3)[i]), tmr) == 0) {
        pole_poz[j] = i;
        j++;
        cntr++;
      }
    }

    for (i = 0; i < cntr; i++) {
      printf("%d ", pole_poz[i]);
    }
    printf("\n");

    for (i = 0; i < cntr - 1; i++) {
      for (j = 0; j < cntr - i - 1; j++) {
        if (((p6[pole_poz[j]] > p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) <= atoi((*p5)[pole_poz[j + 1]]))) ||
            ((p6[pole_poz[j]] == p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) > atoi((*p5)[pole_poz[j + 1]])))) {
          pom = pole_poz[j + 1];
          pole_poz[j + 1] = pole_poz[j];
          pole_poz[j] = pom;
        }
      }
    }

    for (i = 0; i < cntr; i++) {
      printf("%s\t%s\t%llu\t%s\t%lf\n", (*p2)[pole_poz[i]], (*p3)[pole_poz[i]],
             p6[pole_poz[i]], (*p5)[pole_poz[i]], p4[pole_poz[i]]);
    }
    printf("\n");
    dealokuj_polia(p1, p2, p3, p4, p5, p6, zaznamy);

  } else {
    scanf("%s %s", mm, tmr);
    printf("%s %s", mm, tmr);

    for (i = 0; i < *zaznamy; i++) {
      if (strcmp(((*p2)[i]), mm) == 0 && strcmp(((*p3)[i]), tmr) == 0) {
        pole_poz[j] = i;
        j++;
        cntr++;
      }
    }

    for (i = 0; i < cntr; i++) {
      printf("%d ", pole_poz[i]);
    }
    printf("\n");

    for (i = 0; i < cntr - 1; i++) {
      for (j = 0; j < cntr - i - 1; j++) {
        if (((p6[pole_poz[j]] > p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) <= atoi((*p5)[pole_poz[j + 1]]))) ||
            ((p6[pole_poz[j]] == p6[pole_poz[j + 1]]) &&
             (atoi((*p5)[pole_poz[j]]) > atoi((*p5)[pole_poz[j + 1]])))) {
          pom = pole_poz[j + 1];
          pole_poz[j + 1] = pole_poz[j];
          pole_poz[j] = pom;
        }
      }
    }

    for (i = 0; i < cntr; i++) {
      printf("%s\t%s\t%llu\t%s\t%lf\n", (*p2)[pole_poz[i]], (*p3)[pole_poz[i]],
             p6[pole_poz[i]], (*p5)[pole_poz[i]], p4[pole_poz[i]]);
    }
    printf("\n");
  }
}

int r(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4,
      char ***p5, unsigned long long int *p6, unsigned int *zaznamy) {
  int i, j;
  char **pole_casy;
  char hod[3], min[3], last_hod[3], last_min[3], pom[5];

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL &&
      p6 == NULL) {
    printf("Polia nie su vytvorene.\n");
    return 0;
  }
  pole_casy = malloc((*zaznamy) * sizeof(char *));

  for (i = 0; i < *zaznamy; i++) {
    pole_casy[i] = malloc(5 * sizeof(char));
    strcpy(pole_casy[i], (*p5)[i]);
  }

  for (i = 0; i < *zaznamy - 1; i++) {
    for (j = 0; j < *zaznamy - i - 1; j++) {
      if (atoi(pole_casy[j]) > atoi(pole_casy[j + 1])) {
        strcpy(pom, pole_casy[j + 1]);
        strcpy(pole_casy[j + 1], pole_casy[j]);
        strcpy(pole_casy[j], pom);
      }
    }
  }

  for (i = 0; i < *zaznamy; i++) {
    memcpy(hod, pole_casy[i], 2);
    strcpy(min, &pole_casy[i][2]);

    if (i == 0) {
      printf("%s:", hod);
      strcpy(last_hod, hod);
      printf("%s", min);
      strcpy(last_min, min);
    } else {
      if (atoi(hod) > atoi(last_hod)) {
        printf("\n%s:", hod);
        strcpy(last_hod, hod);
        printf("%s", min);
        strcpy(last_min, min);
      } else {
        if ((atoi(hod) == atoi(last_hod)) && (atoi(min) == atoi(last_min))) {
          continue;
        } else {
          printf(", %s", min);
          strcpy(last_min, min);
        }
      }
    }
  }
  return 0;
}

int h(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4,
      char ***p5, unsigned long long int *p6, unsigned int *zaznamy) {
  char tmv[10];
  int i = 0, j = 0, cntr = 0, pom = 0, cntr_hist = 0, min = 0, max = 5,
      vel_pol = 0, pos = 0;
  int pole_poz[57], *pocetnost;
  double del;

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL &&
      p6 == NULL) {
    printf("Polia nie su vytvorene.\n");
    return 0;
  }

  scanf("%s", tmv);

  for (i = 0; i < *zaznamy; i++) {
    if (strcmp(((*p3)[i]), tmv) == 0) {
      pole_poz[j] = i;
      j++;
      cntr++;
    }
  }

  for (i = 0; i < cntr - 1; i++) {
    for (j = 0; j < cntr - i - 1; j++) {
      if (p4[pole_poz[j]] > p4[pole_poz[j + 1]]) {
        pom = pole_poz[j + 1];
        pole_poz[j + 1] = pole_poz[j];
        pole_poz[j] = pom;
      }
    }
  }

  for (i = 0; i < cntr; i++) {
    printf("%lf\n", p4[pole_poz[i]]);
  }

  vel_pol = ceil((p4[pole_poz[cntr - 1]]) / 5);
  printf("%d\n", vel_pol);

  pocetnost = (int *)malloc(vel_pol * sizeof(int));
  for (i = 0; i < vel_pol; i++) {
    pocetnost[i] = 0;
  }

  for (i = 0; i < cntr; i++) {
    del = floor(p4[pole_poz[i]] / 5);
    pos = (int)del;
    pocetnost[pos] = pocetnost[pos] + 1;
    // printf("%d\n",pocetnost[pos]);
  }

  // for (i = 0; i<vel_pol; i++){
  //   printf("%d", pocetnost[i]);
  //   }

  for (i = 0; i < vel_pol; i++) {
    if (pocetnost[i] > 0) {
      printf("%d-%d: %d\n", min, max, pocetnost[i]);
    }
    min = max;
    max += 5;
  }
}

int s(FILE **fr, unsigned long long int *p1, char ***p2, char ***p3, double *p4,
      char ***p5, unsigned long long int *p6, unsigned int *zaznamy) {
  FILE *fw;
  char mm[10], tmr[10];
  int pole_poz[57];
  double *merania;
  int pom = 0, j = 0, i = 0, cntr = 0;

  fw = fopen("vystup_S.txt", "w");

  if (p1 == NULL && *p2 == NULL && *p3 == NULL && p4 == NULL && *p5 == NULL &&
      p6 == NULL) {
    printf("Polia nie su vytvorene.\n");
    return 0;
  }

  scanf("%s %s", mm, tmr);

  for (i = 0; i < *zaznamy; i++) {
    if (strcmp(((*p2)[i]), mm) == 0 && strcmp(((*p3)[i]), tmr) == 0) {
      pole_poz[j] = i;
      j++;
      cntr++;
    }
  }

  if (cntr == 0) {
    printf("Pre dany vstup neexistuju zaznamy.");
  }

  for (i = 0; i < cntr - 1; i++) {
    for (j = 0; j < cntr - i - 1; j++) {
      if (((p6[pole_poz[j]] > p6[pole_poz[j + 1]]) &&
           (atoi((*p5)[pole_poz[j]]) <= atoi((*p5)[pole_poz[j + 1]]))) ||
          ((p6[pole_poz[j]] == p6[pole_poz[j + 1]]) &&
           (atoi((*p5)[pole_poz[j]]) > atoi((*p5)[pole_poz[j + 1]])))) {
        pom = pole_poz[j + 1];
        pole_poz[j + 1] = pole_poz[j];
        pole_poz[j] = pom;
      }
    }
  }

  merania = (double *)malloc(cntr * sizeof(double));
  for (i = 0; i < cntr; i++) {
    merania[i] = p4[pole_poz[i]];
  }

  for (i = 0; i <= cntr; i++) {
    if (i == cntr) {
      printf("Pre dany vstup je vytvoreny txt subor.\n");
      fclose(fw);
    } else {
      fprintf(fw, "%llu%s\t%.7lf\n", p6[pole_poz[i]], (*p5)[pole_poz[i]],
              merania[i]);
    }
  }
  return 0;
}

int c(FILE **fr){
  unsigned long long int id, datum;
  char modul[10], typ[10], cas[10];
  double hodnota;
  char arr[255];
  char s;
  int i = 0;


  if (*fr != NULL) {
    fseek(*fr, 0, SEEK_SET);
  } else {
    printf("Neotvoreny subor.\n");
    return 0;
  }

  
  printf("test");
 do {
        fscanf(*fr, "%llu \n %s \n %s \n %lf \n %s \n %llu \n", &id, modul, typ, &hodnota, cas, &datum);
        if ((id % 11 != 0) || (floor(log10(id) + 1) != 10)){
          printf("Nekorektne zadany vstup: ID cislo mer. osoby.");
        }
        printf("Mer. modul: %s\n", modul);
        if (isupper(modul[0]) == 0 || isdigit(modul[1]) == 0 || isdigit(modul[2]) == 0 || strlen(modul) != 3){
          printf("Nekorektne zadany vstup: Mer. modul.");
        }
        printf("Typ mer. veliciny: %s\n", typ);
        printf("Hodnota: %lf\n", hodnota);
        printf("Cas merania: %s\n", cas);
        printf("Datum: %llu\n", datum);
        printf("\n");
    } while (!feof(*fr));
    
  return 0;
}

int main() {
  FILE *fr = NULL;
  unsigned long long int *p1 = NULL, *p6 = NULL;
  char **p2 = NULL, **p3 = NULL, **p5 = NULL;
  double *p4 = NULL;
  unsigned int zaznamy;
  char pismeno;

  do {
    scanf("%c", &pismeno);
    switch (pismeno) {
    case 'v':
      v(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break; // funkcia na vypis zaznamov
    case 'o':
      o(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break; // funkcia na vypis odmeny
    case 'n':
      n(&fr, &p1, &p2, &p3, &p4, &p5, &p6, &zaznamy);
      break; // funkcia na vytvorenie dinamickeho pola
    case 'h':
      h(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      ;
      break; // vypise spz specialnym sposobom
    case 's':
      s(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break; // vypise najcastejsie sa vyskitujuci sa znak a jeho pocetnost
    case 'r':
      r(&fr, p1, &p2, &p3, p4, &p5, p6, &zaznamy);
      break;
    case 'c': 
      c(&fr); 
      break;
      // case 'z': z(&SPZ); break;//vypise pocetnost znakov
      // case 'k': z(&SPZ); break;//vypise pocetnost znakov
    }
  } while (pismeno != 'k');

  printf("%d", zaznamy);

  // TODO: dealokovat polia ak boli vytvorene a zavriet subor
  fclose(fr);

  return 0;
}
