#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int data;
    struct Node *suivant;
}Node;

Node *create_Node(){
    Node *new= (Node*)malloc(sizeof(Node));
    if(!new) return NULL;
    return new;
}

Node *AjouterTete(Node *e, int x){
    Node *new = create_Node();
    new->data = x;
    new->suivant=e;
    return new; 
}

Node *AjouterApres(Node *e, int val, int x){
    Node *tmp = e;
    while(tmp!=NULL){
        if(tmp->data==val){
            Node *new=create_Node();
            new->data=x;
            new->suivant=tmp->suivant;
            tmp->suivant=new;
            return e;
        }

        tmp=tmp->suivant;
    }
    printf("Valeur %d non Trouve\n", val);
    return e;
}

Node *AjouterAvant(Node *e, int val, int x){
    if(e!=NULL && e->data==val){
        return AjouterTete(e, x);
    }
    Node *tmp =e;
    while(tmp!=NULL && tmp->suivant!=NULL){
        if(tmp->suivant->data==val){
            Node *new=create_Node();
            new->data=x;
            new->suivant=tmp->suivant;
            tmp->suivant=new;
            return e;
        }
        tmp = tmp->suivant;
    }
    printf("valeur %d non trouve\n", val);
    return e;
}

Node *ajouterFin(Node *e, int x){
    Node *new=create_Node();
    new->data=x;
    new->suivant=NULL;
    if(e ==NULL) return new;
    Node *tmp=e;
    while(tmp->suivant!=NULL){
        tmp=tmp->suivant;
    }
    tmp->suivant=new;
    return e;
}