#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct monome {
  float coefficient;
  int exposant;
  struct monome *next;
} monome;

typedef monome *polynome;

monome *create_monome(float coef, int expo) {
  monome *new = malloc(sizeof(monome));
  if (!new)
    return NULL;
  new->coefficient = coef;
  new->exposant = expo;
  new->next = NULL;
  return new;
}

void saisir(polynome *p) {
  *p = NULL;

  float coeff;
  int expo;

  printf("Enter exponent (negative to stop): ");
  if (scanf("%d", &expo) != 1) {
    return;
  }
  while (expo >= 0) {
    printf("Enter coefficient: ");
    scanf("%f", &coeff);

    monome *new = create_monome(coeff, expo);
    if (new == NULL)
      return;
    if (*p == NULL) {
      *p = new;
    } else if (new->exposant > (*p)->exposant) {
      new->next = *p;
      *p = new;
    } else if (new->exposant == (*p)->exposant) {
      (*p)->coefficient += new->coefficient;
      free(new);

    } else {
      monome *tmp = *p;

      while (tmp->next != NULL && tmp->next->exposant > new->exposant) {
        tmp = tmp->next;
      }

      if (tmp->next != NULL && tmp->next->exposant == new->exposant) {
        tmp->next->coefficient += new->coefficient;
        free(new);

      } else {
        new->next = tmp->next;
        tmp->next = new;
      }
    }

    printf("Enter exponent (negative to stop): ");
    scanf("%d", &expo);
  }
}
