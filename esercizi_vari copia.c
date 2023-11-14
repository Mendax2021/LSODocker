/*1- Data una lista L dinamica singolarmente puntata di valori interi, 
raddoppiare (numericamente) tutti i numeri dispari in essa contenuti. 
Per esempio 1->3->4 diventa 2->6->4*/
/*2- Data una lista L dinamica singolarmente puntata di valori interi, 
duplicare tutti i numeri dispari in essa contenuti. 
Per esempio 1->3->4 diventa 1->3->3->4*/
/*3- Data una lista L dinamica singolarmente puntata di valori interi
ed un valore intero value, verificare se value è presente in L*/
/*4- Inserire in maniera ordinata gli elementi all'interno di una lista*/
/*Data una lista L dinamica singolarmente puntata diu valori interi, cancellare da L tutti i numeri pari*/
#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int val;
    struct lista* next;
} L;

int is_empty(L* p_head);
void print_list(L* p_head);
L* create_node(int value);
void append(L** pp_head, int value);
void prepend(L** pp_head, int value);
void double_odds(L* pp_head);
void duplicate_odds(L* pp_head);
void remove_even(L** pp_head);
int is_present(L* p_head, int value);
void deallocate_list(L** pp_head);
void deallocate_list_reverse(L** pp_head);
void Insert_in_order(L** pp_head, int value);

int main() {
    L* start_lista = NULL;
    int scelta;
    int value;

    do {

        printf("Fai una scelta:\n");
        printf("\n1- Inserisci un elemento in testa\n2- Inserisci un elemento in coda\n3- Inserisci gli elementi in ordine\n4- Raddoppia gli elementi dispari\n5- Duplica gli elementi dispari\n6- Verifica la presenza di un elemento\n7- Elimina gli elementi pari\n8- Stampa\n0- Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1: 
                printf(">>> Inserisci un valore: ");
                scanf("%d", &value);
                prepend(&start_lista, value);
                print_list(start_lista);
            break;
            case 2: 
                printf(">>> Inserisci un valore: ");
                scanf("%d", &value);
                append(&start_lista, value);
                print_list(start_lista);
            break;
            case 3:
                printf(">>> Inserisci un valore: ");
                scanf("%d", &value);
                printf("Inserisco in ordin l'elemento: %d\n", value);
                Insert_in_order(&start_lista, value);
            break;
            case 4: 
                printf(">>> Raddoppio...\n");
                double_odds(start_lista);
                print_list(start_lista);
            break;
            case 5: 
                printf(">>> Duplico...\n");
                duplicate_odds(start_lista);
                print_list(start_lista);
            break;
            case 6:
                printf(">>> Che valore vuoi cercare: ");
                scanf("%d", &value);
                printf(">>> Verifico se è presente...\n");
                if (is_present(start_lista, value)) {
                    printf(">>> Si e' presente");
                } else {
                    printf(">>> Non è presente\n");
                }
            break;
            case 7:
                printf("Elimino gli elementi pari...\n");
                remove_even(&start_lista);
            break;
            case 8: 
                printf("Lista: ");
                print_list(start_lista);
            break;
            default: 
                printf("Dealloco...\nEsco...\n");
                deallocate_list_reverse(&start_lista);
                scelta = 0;
                break;
        }
    } while(scelta != 0);

    return 0;
}

int is_empty(L* p_head) {
    return p_head == NULL;
}

L* create_node(int value) {
    L* to_create = malloc(sizeof(L));
    to_create->val = value;
    to_create->next = NULL;

    return to_create;
}

void append(L** pp_head, int value) {
    if (is_empty(*pp_head)) {
        *pp_head = create_node(value);
        return;
    }
    append(&((*pp_head)->next), value);
}

void prepend(L** pp_head, int value) {
    L* next = *pp_head;
    *pp_head = create_node(value);
    (*pp_head)->next = next;
}

void Insert_in_order(L** pp_head, int value) {
    if (is_empty(*pp_head) || value < (*pp_head)->val) {
        L* p_new = create_node(value);
        p_new->next = *pp_head;
        *pp_head = p_new;
        return;
    }
    Insert_in_order(&((*pp_head)->next), value);
}

void print_list(L* p_head) {
    if (is_empty(p_head)) {
        printf("\n");
        return;
    }
    printf("%d ", p_head->val);
    print_list(p_head->next);
}

void double_odds(L* p_head) {
    if (is_empty(p_head)) {
        return;
    }
    if (p_head->val % 2 != 0) {
        p_head->val = p_head->val * 2;
    }
    double_odds(p_head->next);
}

void duplicate_odds(L* p_head) {
    if (is_empty(p_head)) {
        return;
    }
    if (p_head->val % 2 != 0) {
        L* p_new = create_node(p_head->val);
        p_new->next = p_head->next;
        p_head->next = p_new;
        duplicate_odds(p_new->next);
    } else {
        duplicate_odds(p_head->next);
    }   
}

void remove_even(L** pp_head) {
    if (is_empty(*pp_head)) {
        return;
    }
    if ((*pp_head)->val % 2 == 0) {
        L* to_del = *pp_head;
        *pp_head = to_del->next;
        free(to_del);
        remove_even(pp_head);
    } else {
        remove_even(&((*pp_head)->next));
    }
}

int is_present(L* p_head, int value) {
    if (is_empty(p_head)) {
        return 0;
    }
    if (p_head->val ==  value) {
        return 1;
    } else {
        return is_present(p_head->next, value);
    }
}

void deallocate_list(L** pp_head) {
    if (is_empty(*pp_head)) {
        return;
    }
    L* to_del = *pp_head;
    *pp_head = (*pp_head)->next;
    free(to_del);
    deallocate_list(pp_head);
}

void deallocate_list_reverse(L** pp_head) {
    if (is_empty(*pp_head)) {
        return;
    }
    deallocate_list_reverse(&((*pp_head)->next));
    free(*pp_head);
    *pp_head = NULL;
}