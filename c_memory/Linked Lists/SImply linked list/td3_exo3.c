#include <math.h>
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
      if ((*p)->coefficient == 0) {
        monome *tmp = *p;
        *p = (*p)->next;
        free(tmp);
      }

    } else {
      monome *tmp = *p;

      while (tmp->next != NULL && tmp->next->exposant > new->exposant) {
        tmp = tmp->next;
      }

      if (tmp->next != NULL && tmp->next->exposant == new->exposant) {
        tmp->next->coefficient += new->coefficient;
        free(new);
        if (tmp->next->coefficient == 0) {
          monome *to_delete = tmp->next;
          tmp->next = to_delete->next;
          free(to_delete);
        }

      } else {
        new->next = tmp->next;
        tmp->next = new;
      }
    }

    printf("Enter exponent (negative to stop): ");
    scanf("%d", &expo);
  }
}

float evaluer(polynome p, float x) {
  float somme = 0.0;
  monome *tmp = p;
  while (tmp != NULL) {
    somme += tmp->coefficient * pow(x, tmp->exposant);
    tmp = tmp->next;
  }
  return somme;
}

polynome multi(polynome p, float a, int n) {
  monome *tmp = p;
  monome *tail = NULL;
  polynome resultat = NULL;
  if(p == NULL || a == 0) return NULL;
  while (tmp != NULL) {
    monome *new = create_monome(tmp->coefficient * a, tmp->exposant + n);
    if (resultat == NULL) {
      resultat = new;
      tail = new;
    }else{
        tail->next = new;
        tail = new;
    }
    tmp = tmp->next;
  }
  return resultat;
}

void afficher(polynome p){
    if(p == NULL){
        printf("0\n");
        return;
    }
    monome *tmp = p;
    while(tmp!=NULL){
        printf("%.2fx^%d ", fabsf(tmp->coefficient), tmp->exposant);

        if(tmp->next != NULL){
            if(tmp->next->coefficient < 0){
                printf(" - ");
            }else{
            printf(" + ");
            }
        }

        tmp = tmp ->next;
    }
    printf("\n");
}
