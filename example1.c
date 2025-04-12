//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int restaurant;
    struct Node *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct graf {
    int numar_restaurante;
    int *vizitat;
    struct Node **listaAdiacenta;
}GRAF;

typedef struct stiva {
    int top;
    int capacitateaStivei;
    int *vector;
}STIVA;

NODE *creareNod(int v) {
    NODE *nodNou = malloc(sizeof(NODE));
    nodNou->restaurant = v;
    nodNou->next = NULL;
    return nodNou;
}

void add_edge(GRAF *graf, int src, int dest) {
    NODE *nodNou = creareNod(dest);
    nodNou->next = graf->listaAdiacenta[src];
    graf->listaAdiacenta[src] = nodNou;
    nodNou = creareNod(src);
    nodNou->next = graf->listaAdiacenta[dest];
    graf->listaAdiacenta[dest] = nodNou;
}

GRAF *creareGraf(int v) {
    GRAF *graf = malloc(sizeof(GRAF));
    graf->numar_restaurante = v;
    graf->listaAdiacenta = malloc(sizeof(NODE *) * v);
    graf->vizitat = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        graf->listaAdiacenta[i] = NULL;
        graf->vizitat[i] = 0;
    }
    return graf;
}

STIVA *creareStiva(int capacitate) {
    STIVA *stiva = malloc(sizeof(STIVA));
    stiva->vector = malloc(capacitate * sizeof(int));
    stiva->top = -1;
    stiva->capacitateaStivei = capacitate;

    return stiva;
}

void push(int pshd, STIVA *stiva) {
    stiva->top = stiva->top + 1;
    stiva->vector[stiva->top] = pshd;
}

void depthfirstSearch(GRAF *graf, STIVA *stiva, int v_nr) {
    NODE *adj_list = graf->listaAdiacenta[v_nr];
    NODE *aux = adj_list;
    graf->vizitat[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, stiva);
    while (aux != NULL) {
        int con_ver = aux->restaurant;
        if (graf->vizitat[con_ver] == 0)
            depthfirstSearch(graf, stiva, con_ver);
        aux = aux->next;
    }
}

void adaugareMuchii(GRAF *graf, int numar_muchii, int nrv) {
    int initial, final, i;
    printf("adauga %d muchii (de la 1 la %d)\n", numar_muchii, nrv);
    for (i = 0; i < numar_muchii; i++) {
        scanf("%d%d", &initial, &final);
        add_edge(graf, initial, final);
    }
}

void resetareVizita(GRAF *graf, int nrv) {
    for (int i = 0; i < nrv; i++) {
        graf->vizitat[i] = 0;
    }
}

int existaDrum(GRAF *graf, int numar_restaurante, STIVA *restaurant_inceput, STIVA *restaurant_destinatie) {
    int restaurant1, restaurant2;
    printf("Introduceti doua restaurante (de la 1 la %d): ", numar_restaurante);
    scanf("%d %d", &restaurant1, &restaurant2);

    restaurant_inceput->top = -1;
    restaurant_destinatie->top = -1;

    depthfirstSearch(graf, restaurant_inceput, restaurant1 - 1);
    resetareVizita(graf, numar_restaurante);
    depthfirstSearch(graf, restaurant_destinatie, restaurant2 - 1);

    for (int i = 0; i <= restaurant_inceput->top; i++) {
        for (int j = 0; j <= restaurant_destinatie->top; j++) {
            if (restaurant_inceput->vector[i] == restaurant_destinatie->vector[j])
                return 1; // exista drum intre cele doua restaurante
        }
    }
    return 0; //nu exista drum intre cele doua restaurante
}

int main() {
    int numar_varfuri;
    int numar_muchii;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &numar_varfuri);

    printf("cate muchii are graful?");
    scanf("%d", &numar_muchii);

    GRAF *graf = creareGraf(numar_varfuri);
    STIVA *stiva1 = creareStiva(2 * numar_varfuri);
    STIVA *stiva2 = creareStiva(2 * numar_varfuri);

    insert_edges(graf, numar_muchii, numar_varfuri);

    canbe(graf, numar_varfuri, stiva1, stiva2);
}
