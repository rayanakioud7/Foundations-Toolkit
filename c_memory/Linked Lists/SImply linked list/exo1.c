#include <stdio.h>
#include <stdlib.h>

typedef struct Element{
    int valeur;
    struct Element *next;
}Element;

void free_list(Element *e){
    Element *current = e;
    Element *next;

    while(current){
        next = current->next;
        free(current);
        current = next;
    }
}

Element *create_linked_list(int valeur){
    Element *e = (Element*)malloc(sizeof(Element));
    if(!e) return NULL;
    e->valeur = valeur;
    e->next = NULL;
    return e;
}

Element* insert(Element *head, int valeur){
    Element *new_e = create_linked_list(valeur);
    if(!new_e) return head;
    new_e->next = head;
    return new_e;

}
Element *ajouterApres(Element *e, int val, int x){
    Element *tmp=e;
    while(tmp!=NULL){
        if(tmp->valeur==val){
            Element *new = create_linked_list(x);
            if(new == NULL) return e;
            new->next=tmp->next;
            tmp->next=new;
            return e;
        }
        tmp=tmp->next;
    }
    return e;
}

Element *ajouter_Ordre_croissant(Element *e, int x) {
    Element *new = create_linked_list(x);
    if (new == NULL) return e;

    if (e == NULL || e->valeur >= x) {
        new->next = e;
        return new;
    }

    Element *tmp = e;

    while (tmp->next != NULL && tmp->next->valeur < x) {
        tmp = tmp->next;
    }

    new->next = tmp->next;
    tmp->next = new;

    return e;
}


Element *creer_liste_ordonnee(int tab[], int n) {
    Element *e = NULL;

    for (int i = 0; i < n; i++) {
        e = ajouter_Ordre_croissant(e, tab[i]);
    }

    return e;
}

Element * occurence(Element *e, int x){
    if(e==NULL){
        printf("liste vide\n");
        return NULL;
    }
    Element * tmp = e;
    while(tmp!=NULL){
        if(tmp->valeur==x){
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("Valuer non Trouve\n");
    return NULL;
}

Element *supprimer(Element * e, int x){
    if(e==NULL) return NULL;
    if(e->valeur==x){
        Element *tmp=e->next;
        free(e);
        return tmp;
    }
    Element *prec=e;
    while(prec->next!=NULL){
        if(prec->next->valeur==x){
            Element *tmp = prec->next;
            prec->next =tmp->next;
            free(tmp);
            return e;
        }
        prec=prec->next;
    }
    return e;
}

Element *supprimer_tous_occur(Element *e, int x){

    while (e!=NULL && e->valeur==x){
        e = supprimer(e,x);
    }
    Element *tmp =e;

    while(tmp!=NULL && tmp->next!=NULL){
        if(tmp->next->valeur==x){
            supprimer(tmp, x);
        }else{
            tmp = tmp->next;
        }
    }
    return e;

}

int sum_list(Element *e){
    int somme =0;
    Element *tmp = e;
    while(tmp!=NULL){
        somme+=tmp->valeur;
        tmp = tmp->next;
    }
    return somme;
}

void print_list(Element *head){
    Element *current = head;
    while(current){
        printf("%d -> ", current->valeur);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    int tab[] = {8, 3, 12, 1, 6, 3, 8};
    int n = sizeof(tab) / sizeof(tab[0]);

    Element *head = creer_liste_ordonnee(tab, n);

    printf("Liste ordonnee :\n");
    print_list(head);

    printf("Suppression de toutes les occurrences de 3 :\n");
    head = supprimer_tous_occur(head, 3);
    print_list(head);

    printf("Somme : %d\n", sum_list(head));

    free_list(head);
    return 0;
}
