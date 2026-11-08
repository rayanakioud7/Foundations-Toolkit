#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
typedef struct Etudiant{
    int matricule;
    char *nom;
    float taille;
    struct Etudiant *next;
}Etudiant;
*/
// or
typedef struct Etudiant{
    int matricule;
    char *nom;
    float taille;
}Etudiant;

typedef struct Node{
    Etudiant e;
    struct Node *next;
}Node;

Node *create_node(int matric, char *nom, float taille){
    Node *new = malloc(sizeof(Node));
    if(!new) return NULL;
    new->e.matricule = matric;
    new->e.nom = nom;
    new->e.taille = taille;
    new->next = NULL;
    return new;
}

// Q2.
bool existe(Node *l, int matr){

    Node *tmp = l;
    while(tmp!=NULL){
        if(tmp->e.matricule==matr){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

Node *ajouter_tete(Node *l, int matric, char *nom, float taille){
    if(!existe(l,matric)){
        Node *new = create_node(matric, nom, taille);
        if(new == NULL) return l;
        new->next = l;
        return new;
    }else{
        printf("Etudiant Existe deja\n");
        return l;
    }
}

int nombre_indiv(Node *l){
    int count = 0;
    Node *tmp = l;
    while(tmp!=NULL){
        count++;
        tmp = tmp->next;
    }
    return count;
}

float moyenne_taille(Node *l){
    float somme = 0;
    Node *tmp =l;
    while(tmp!=NULL){
        somme+=tmp->e.taille;
        tmp = tmp->next;
    }
    int count = nombre_indiv(l);
    if(count==0){
        return 0;
    }else{
        return somme/count;
    }
}

void free_list(Node *l){
    Node *current =l;
    Node *next;
    while(current){
        next = current->next;
        free(current);
        current = next;
    }
}

int main(){

    Node *l = create_node(1, "rayan", 1.75);
    l = ajouter_tete(l, 2, "riyad", 1.77);
    float moy_taile = moyenne_taille(l);

    printf("taille moyene: %.2f\n", moy_taile);
    free_list(l);
    return 0;
}
