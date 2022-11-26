#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zaznam {
  unsigned long long int id_cislo;
  char meno_osoby[100];
  char mer_modul[4];
  char typ_mer_vel[3];
  double hodnota;
  char cas[5];
  unsigned long long int datum;
  struct zaznam *dalsi;
} ZAZNAM;

void uvolni_list(struct zaznam **head)
{
    struct zaznam *p;
    p = *head;
    while (*head != NULL)
    {
        p = *head;
        *head = (*head)->dalsi;
        free(p);
    }
}

int n(FILE **fr, ZAZNAM **head, unsigned int *pocet_zaznamov) {
  struct zaznam *temp, *p;
  int cntr = 0;
  char arr[100], s, pom[5];
  char x[4] = "$$$";
  int i = 1;

  if (head != NULL){ //ak uz zaznamy boli nacitane do zoznamu, dealokujeme a alokujeme znova
    uvolni_list(head);
  }
  
  if (*fr == NULL) {
    *fr = fopen("dataloger_V2.txt", "r");
  }

  fseek(*fr, 0, SEEK_SET); //pre situaciu ak bolo n zavolane viackrat po sebe


  if (*fr == NULL) {
    printf("Zaznamy neboli nacitane!\n"); //ak sa nepodarilo otvorit subor
    return 0;
  }
  

  while ((s = fscanf(*fr, "%s", arr)) != EOF) {
    if (strcmp(arr, x) == 0) { //spocita nam zaznamy pomocou $$$
      cntr += 1;
    }
  }

  *pocet_zaznamov = cntr;

  fseek(*fr, 0, SEEK_SET);

  do {
    temp = (ZAZNAM *)malloc(sizeof(ZAZNAM));
    fgets(pom, 100, *fr);
    fscanf(*fr, "%llu\n", &(temp->id_cislo));
    fgets(temp->meno_osoby, 100, *fr);
    fscanf(*fr, "%s\n", temp->mer_modul);
    fgets(temp->typ_mer_vel, 100, *fr);
    fscanf(*fr, "%lf\n", &(temp->hodnota));
    fgets(temp->cas, 100, *fr);
    fscanf(*fr, "%llu\n", &(temp->datum));

    temp->dalsi = NULL;
    if ((*head) == NULL) {
      (*head) = temp;
    } else {
      p = (*head);
      while (p->dalsi != NULL) {
        p = p->dalsi;
      }
      p->dalsi = temp;
    }
    i++;
  } while (i <= *pocet_zaznamov);

  printf("Nacitalo sa %d zaznamov.\n", *pocet_zaznamov);
  
  return 0;
}

int v(ZAZNAM *head, unsigned int *pocet_zaznamov){
  int i = 0;
  if (head == NULL){
    return 0;
  } else{  
    struct zaznam *p = head;
    while (p != NULL)
    {
        printf("%d:\n",++i);
        printf("ID cislo mer. osoby: %llu\n", p->id_cislo);
        printf("Meno osoby: %s", p->meno_osoby);
        printf("Mer. modul: %s\n", p->mer_modul);
        printf("Typ mer. veliciny: %s", p->typ_mer_vel);
        printf("Hodnota: %lf\n", p->hodnota);
        printf("Cas merania: %s", p->cas);
        printf("Datum: %llu\n", p->datum);
        p = p->dalsi;
    }
    return 0;
  }
}

int main() {
  FILE *fr = NULL;
  ZAZNAM *head = NULL;
  unsigned int pocet_zaznamov;
  char vstup;

  do {
    scanf("%c", &vstup);
    switch (vstup) {
    case 'n':
      n(&fr, &head, &pocet_zaznamov);
      break;
    case 'v':
      v(head, &pocet_zaznamov);
      break;
    }
  } while (vstup != 'k');
  return 0;
}