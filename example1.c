//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int restaurant;
    struct Node *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graf {
    int numar_restaurante;
    int *vizitat_nod;
    struct Node **lista_adiacenta;
}GRAF;

typedef struct Stiva {
    int top;
    int capacitateaStivei;
    int *vector;
}STIVA;

NODE *creareNod(int v) {
    NODE *nod_nou = malloc(sizeof(NODE));
    if (!nod_nou)
        return NULL;

    nod_nou->restaurant = v;
    nod_nou->next = NULL;
    return nod_nou;
}

void adaugareNod(GRAF *graf, int start, int final) {
    NODE *nod_nou = creareNod(final);
    nod_nou->next = graf->lista_adiacenta[start];
    graf->lista_adiacenta[start] = nod_nou;

    nod_nou = creareNod(start);
    nod_nou->next = graf->lista_adiacenta[final];
    graf->lista_adiacenta[final] = nod_nou;
}

GRAF *creareGraf(int numar_restaurante) {
    GRAF *graf = malloc(sizeof(GRAF));
    graf->numar_restaurante = numar_restaurante;
    graf->lista_adiacenta = malloc(numar_restaurante * sizeof(NODE *));
    graf->vizitat_nod = malloc(sizeof(int) * numar_restaurante);

    for (int i = 0; i < numar_restaurante; i++) {
        graf->lista_adiacenta[i] = NULL;
        graf->vizitat_nod[i] = 0;
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

void pushStiva(int valoare, STIVA *stiva) {
    stiva->top = stiva->top + 1;
    stiva->vector[stiva->top] = valoare;
}

void depthFirstSearch(GRAF *graf, STIVA *stiva, int nod_actual) {
    NODE *copie_nod_actual = graf->lista_adiacenta[nod_actual];
    graf->vizitat_nod[nod_actual] = 1;
    pushStiva(nod_actual, stiva);
    while (copie_nod_actual != NULL) {
        int nod_conectat = copie_nod_actual->restaurant;
        if (graf->vizitat_nod[nod_conectat] == 0)
            depthFirstSearch(graf, stiva, nod_conectat);
        copie_nod_actual = copie_nod_actual->next;
    }
}

void adaugareMuchii(GRAF *graf, int numar_muchii, int numar_noduri) {
    int initial, final, i;
    printf("adauga %d muchii (de la 1 la %d)\n", numar_muchii, numar_noduri);
    for (i = 0; i < numar_muchii; i++) {
        scanf("%d%d", &initial, &final);
        adaugareNod(graf, initial - 1, final - 1);
    }
}

void resetareVizita(GRAF *graf, int numar_noduri) {
    for (int i = 0; i < numar_noduri; i++) {
        graf->vizitat_nod[i] = 0;
    }
}

void existaDrum(GRAF *graf, int restaurant_inceput, int restaurant_destinatie, STIVA *stiva1, STIVA *stiva2) {
    int ajunge = 0;

    depthFirstSearch(graf, stiva1, restaurant_inceput);
    resetareVizita(graf, graf->numar_restaurante);
    depthFirstSearch(graf, stiva2, restaurant_destinatie);

    for (int i = 0; i < stiva2->top; i++) {
        for (int j = 0; j < stiva2->top; j++) {
            if (stiva1->vector[i] == restaurant_destinatie && stiva2->vector[j] == restaurant_inceput) {
                ajunge = 1;
                break;
            }
        }
    }

    if (ajunge) {
        printf("Exista drum intre restaurantele %d si %d\n", restaurant_inceput + 1, restaurant_destinatie + 1);
    }
    else {
        printf("Nu exista drum intre restaurantele %d si %d\n", restaurant_inceput + 1, restaurant_destinatie + 1);
    }
}

void verificareDrum(GRAF *graf, STIVA *stiva1, STIVA *stiva2) {
    // 0 sau 1 daca poate fi sau nu ajuns
    int *noduri_verificate = calloc(graf->numar_restaurante, sizeof(int));
    if (!noduri_verificate) {
        printf("eroare!");
        return;
    }
    for (int i = 0; i < graf->numar_restaurante; i++) {
        // aici i tine loc de numar adica de restaurant
        for (int j = 0; j < graf->numar_restaurante; j++) {
            stiva1->top = -1;
            depthFirstSearch(graf, stiva1, i);
            resetareVizita(graf, graf->numar_restaurante);
            depthFirstSearch(graf, stiva2, j);

            for (int m = 0; m < graf->numar_restaurante; m++){
                for (int n = 0; n < graf->numar_restaurante; n++){
                    if ((stiva1->vector[n] == m) && (stiva2->vector[m] == n))
                        noduri_verificate[n] = 1;
                }
            }
        }
    }
}

int main() {
    int numar_restaurante, numar_drumuri;
    int restaurant_inceput, restaurant_destinatie;
    printf("Cate restaurante sunt?");
    scanf("%d", &numar_restaurante);

    printf("Cate drumuri sunt?");
    scanf("%d", &numar_drumuri);

    GRAF *graf = creareGraf(numar_restaurante);
    STIVA *stiva1 = creareStiva(2 * numar_restaurante);
    STIVA *stiva2 = creareStiva(2 * numar_restaurante);

    adaugareMuchii(graf, numar_drumuri, numar_restaurante);
    printf("Introduceti primul restaurant (1-%d): ", numar_restaurante);
    scanf("%d",&restaurant_inceput);
    printf("Introduceti restaurantul destinatie (1-%d): ", numar_restaurante);
    scanf("%d",&restaurant_destinatie);

    existaDrum(graf, restaurant_inceput - 1, restaurant_destinatie - 1, stiva1, stiva2);

    free(stiva1->vector);
    free(stiva1);
    free(stiva2->vector);
    free(stiva2);
    free(graf->vizitat_nod);
    free(graf->lista_adiacenta);
    free(graf);

    return 0;
}
