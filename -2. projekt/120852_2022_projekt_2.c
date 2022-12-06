// PRPR projekt č.2
// Petra Miková, ID: 120852

#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zaznam
{
  char id_cislo[50];
  char meno_osoby[100];
  char mer_modul[10];
  char typ_mer_vel[10];
  double hodnota;
  char cas[10];
  unsigned long long int datum;
  struct zaznam *dalsi;
} ZAZNAM;

void uvolni_list(struct zaznam **head) //funkcia na uvolnenie pamate
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

int n(FILE **fr, ZAZNAM **head, unsigned int *pocet_zaznamov)
{
  struct zaznam *temp, *p;
  int cntr = 0;
  char arr[100], s, pom[5];
  char x[4] = "$$$";
  int i = 1;

  if (head != NULL)
  { // ak uz zaznamy boli nacitane do zoznamu,
    // dealokujeme a alokujeme znova
    uvolni_list(head);
  }

  if (*fr == NULL)
  {
    *fr = fopen("dataloger_V2.txt", "r");
  }

  if (*fr == NULL)
  {
    printf("Zaznamy neboli nacitane!\n"); // ak sa nepodarilo otvorit subor
    return 0;
  }

  fseek(*fr, 0, SEEK_SET); // pre situaciu ak bolo n zavolane viackrat po sebe

  while ((s = fscanf(*fr, "%s", arr)) != EOF)
  {
    if (strcmp(arr, x) == 0)
    { // spocita nam zaznamy pomocou $$$ v subore
      cntr += 1;
    }
  }

  *pocet_zaznamov = cntr;

  fseek(*fr, 0, SEEK_SET);

  do
  {
    temp = (ZAZNAM *)malloc(sizeof(ZAZNAM));
    fgets(pom, 100, *fr);
    fscanf(*fr, "%s\n", temp->id_cislo);
    fgets(temp->meno_osoby, 100, *fr);
    fscanf(*fr, "%s\n", temp->mer_modul);
    fgets(temp->typ_mer_vel, 100, *fr);
    fscanf(*fr, "%lf\n", &(temp->hodnota));
    fgets(temp->cas, 100, *fr);
    fscanf(*fr, "%llu\n", &(temp->datum));
    temp->dalsi = NULL;

    if ((*head) == NULL)
    {
      (*head) = temp;
    }
    else
    {
      p = (*head);
      while (p->dalsi != NULL)
      {
        p = p->dalsi;
      }
      p->dalsi = temp;
    }
    i++;
  } while (i <= cntr);

  printf("Nacitalo sa %d zaznamov.\n", cntr); 
  return 0;
}

int v(ZAZNAM *head)
{
  int i = 0;
  if (head == NULL)
  {
    return 0; //ak neexistuje spajany zoznam, nevypise sa nic
  }
  else
  {
    struct zaznam *p = head;
    while (p != NULL)
    {
      printf("%d:\n", ++i);
      printf("ID cislo mer. osoby: %s\n", p->id_cislo);
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

int hladaj(struct zaznam **head, char s[50]) //funkcia pre hladanie pozicie ktora vracia poziciu, vyuzivam neskor vo funkcii z
{
  struct zaznam *p;
  int cntr = 1;
  p = (*head);
  while (p != NULL)
  {
    if (strcmp(p->id_cislo,s) == 0)
      return cntr;
    p = p->dalsi;
    cntr++;
  }
  return 0;
}

int z(struct zaznam **head, unsigned int *pocet_zaznamov)
{
  int cntr = 0;
  char id[50];
  scanf("%s", id);
  while (hladaj(head, id) == 1) //vymazanie ak je pozicia prvku 1
  {
    struct zaznam *p = *head;
    printf("Zaznam pre ID: %s pre modul %s bol vymazany.\n",
           p->id_cislo, p->mer_modul);
    (*head) = (*head)->dalsi;
    free(p);
    cntr++;
  }

  struct zaznam *p = *head;
  while (p != NULL && p->dalsi != NULL)
  {
    if (strcmp(p->dalsi->id_cislo, id) == 0)
    {
      cntr++;
      printf("Zaznam pre ID: %s pre modul %s bol vymazany.\n",
             p->dalsi->id_cislo, p->dalsi->mer_modul);
      p->dalsi = p->dalsi->dalsi;
    }
    else
    {
      p = p->dalsi;
    }
  }
  *pocet_zaznamov = *pocet_zaznamov - cntr;

  return 0;
}

struct zaznam *vymen(struct zaznam *ptr1, struct zaznam *ptr2) //vymena dvoch prvkov pre bubble sort 
{
  struct zaznam *tmp = ptr2->dalsi;
  ptr2->dalsi = ptr1;
  ptr1->dalsi = tmp;
  return ptr2;
}

int u(ZAZNAM **head, unsigned int *pocet_zaznamov)// funkcia na usporiadanie zoznamu, vyuzivam bubble sort ktory spustam dvakrat pre datum a potom cas
{
  struct zaznam **h;
  int i, j;

  if (*head == NULL)
  {
    printf("Chyba.\n");
  }
  else
  {

    for (i = 0; i < *pocet_zaznamov; i++)
    {

      h = head;

      for (j = 0; j < *pocet_zaznamov - i - 1; j++)
      {

        struct zaznam *p1 = *h;
        struct zaznam *p2 = p1->dalsi;

        if (p1->datum > p2->datum)
        {
          *h = vymen(p1, p2);
        }

        h = &(*h)->dalsi;
      }
    }

    for (i = 0; i < *pocet_zaznamov; i++)
    {

      h = head;

      for (j = 0; j < *pocet_zaznamov - i - 1; j++)
      {

        struct zaznam *p1 = *h;
        struct zaznam *p2 = p1->dalsi;

        if ((p1->datum == p2->datum) && (atoi(p1->cas) > atoi(p2->cas))) // dozoradenie podla casu ak mame rovnake datumy ale casy sa lisia
        {
          *h = vymen(p1, p2);
        }

        h = &(*h)->dalsi;
      }
    }
    printf("Spajany zoznam bol usporiadany.\n");
  }

  return 0;
}

int p(struct zaznam **head, unsigned int *pocet_zaznamov)//pridanie do zoznamu
{ 
  struct zaznam *p, *temp;
  int poz, i;

  scanf("%d", &poz);

  temp = (ZAZNAM *)malloc(sizeof(ZAZNAM));
  scanf("%s\n", temp->id_cislo);
  fgets(temp->meno_osoby, 100, stdin);
  scanf("%s\n", temp->mer_modul);
  fgets(temp->typ_mer_vel, 100, stdin);
  scanf("%lf\n", &(temp->hodnota));
  fgets(temp->cas, 100, stdin);
  scanf("%llu\n", &(temp->datum));
  temp->dalsi = NULL;

  if ((*head) == NULL)
  {
    (*head) = temp;
    *pocet_zaznamov = 1;
  }
  else
  {
    if (poz == 1) //ak pridavame na poziciu 1
    {
      temp->dalsi = (*head);
      *head = temp;
      *pocet_zaznamov = *pocet_zaznamov + 1;
    }
    else if (poz > 1 && poz <= *pocet_zaznamov) //ak pridavame na poziciu od 2 do pozicie ktora sa nachadza v zozname
    {
      p = (*head);
      for (i = 2; i < poz; i++)
      {
        p = p->dalsi;
      }
      temp->dalsi = p->dalsi;
      p->dalsi = temp;
      *pocet_zaznamov = *pocet_zaznamov + 1;
    }
    else //pridanie na koniec, ak zadame poziciu ktora sa v zozname nenachadza
    {
      p = (*head);
      while (p->dalsi != NULL)
      {
        p = p->dalsi;
      }
      p->dalsi = temp;
      *pocet_zaznamov = *pocet_zaznamov + 1;
    }
  }

  return 0;
}

int h(struct zaznam **head, unsigned int *pocet_zaznamov) //vypis podla meracieho modulu
{
  struct zaznam *p = *head;
  char modul[10];
  int i = 0, cntr = 0;
  scanf("%s", modul);

  while (p != NULL)
  {
    if (strcmp(p->mer_modul, modul) == 0)
    {
      printf("%d:\n", ++i);
      printf("ID cislo mer. osoby: %s\n", p->id_cislo);
      printf("Meno osoby: %s", p->meno_osoby);
      printf("Mer. modul: %s\n", p->mer_modul);
      printf("Typ mer. veliciny: %s", p->typ_mer_vel);
      printf("Hodnota: %lf\n", p->hodnota);
      printf("Cas merania: %s", p->cas);
      printf("Datum: %llu\n", p->datum);
      p = p->dalsi;
      cntr++;
    }
    else
    {
      p = p->dalsi;
    }
  }
  if (cntr == 0)
  {
    printf("Pre meraci modul %s niesu zaznamy.\n", modul);
  }
  return 0;
}

int r(struct zaznam **head, unsigned int *pocet_zaznamov) //prehodenie zaznamov
{
  struct zaznam *p1, *p2, *prev1, *prev2, *temp; //vytvorim si ukazovatele pre predosle zaznamy zadanych pozicii a pre zaznamy na danych poziciach
  int c1, c2, i = 1;

  scanf("%d %d", &c1, &c2);

  if ((c1 < 0 || c1 > *pocet_zaznamov) || (c2 < 0 || c2 > *pocet_zaznamov)) //ak niektora pozicia neexistuje
  {
    return 0;
  }

  temp = *head;
  prev1 = NULL;
  prev2 = NULL;

  while (temp != NULL)
  {
    if (i == c1 - 1)
      prev1 = temp;
    if (i == c1)
      p1 = temp;

    if (i == c2 - 1)
      prev2 = temp;
    if (i == c2)
      p2 = temp;

    temp = temp->dalsi;
    i++;
  }

  if (p1 != NULL && p2 != NULL) //ak existuju zaznamy na danych poziciach
  {
    if (prev1 != NULL)
      prev1->dalsi = p2; //predosly zaznam (ak existuje) pozicie 1 bude ukazovat na zaznam na pozicii 2

    if (prev2 != NULL)
      prev2->dalsi = p1; //predosly zaznam (ak existuje) pozicie 2 bude ukazovat na zaznam na pozicii 1

    temp = p1->dalsi;
    p1->dalsi = p2->dalsi;
    p2->dalsi = temp; //vymenim zaznamy na danych poziciach

    //nasledne ak niektora z pozicii bola prva, teda neexistuje jej predosly zaznam, zaznam na danej pozicii bude head listu (prvy prvok)
    if (prev1 == NULL) 
    {
      *head = p2;
    }
    else if (prev2 == NULL)
    {
      *head = p1;
    }
  }
  return 0;
}

int main()
{
  FILE *fr = NULL;
  ZAZNAM *head = NULL;
  unsigned int pocet_zaznamov;
  char vstup;

  do
  {
    scanf("%c", &vstup);
    switch (vstup)
    {
    case 'n':
      n(&fr, &head, &pocet_zaznamov);
      break;
    case 'v':
      v(head);
      break;
    case 'z':
      z(&head, &pocet_zaznamov);
      break;
    case 'u':
      u(&head, &pocet_zaznamov);
      break;
    case 'p':
      p(&head, &pocet_zaznamov);
      break;
    case 'h':
      h(&head, &pocet_zaznamov);
      break;
    case 'r':
      r(&head, &pocet_zaznamov);
      break;
    }
  } while (vstup != 'k');

  if (fr != NULL) //ak bol otvoreny subor, zavriem ho
  {
    fclose(fr);
  }

  if (head != NULL) //ak bol vytvoreny spajany zoznam, uvolnim pamat
  {
    uvolni_list(&head);
  }

  return 0;
}