// Crie uma lista encadeada com inserção no início para
// inteiros

// Implemente as funcionalidades de:

// Inserção

// Remoção

// Busca (booleana)

#include <stdio.h>
#include <stdlib.h>

typedef struct LISTA{
    int numero;
    struct LISTA *proximo;
} NO;


NO *iniciar() {
    NO *Lista = NULL;
    return Lista;
}

NO* criar_no() {
    NO *novo = (NO*) malloc(sizeof(NO));
    return novo;
}

NO* inserir_no_inicio(NO *lista, int valor) {
    NO * novo = criar_no();
    novo->numero = valor;
    if (lista==NULL) {
        lista = novo;
        novo->proximo = NULL;
    }
    else {
        novo->proximo = lista;
        lista = novo;
    }
    return lista;
}

NO* remover_do_inicio(NO *lista) {
    NO *aux = lista;
    lista = aux->proximo;
    free(aux);
    return lista;
}

void imprimir_lista(NO *lista) {
    NO *aux = lista;
    while(aux != NULL) {
        printf("%d\n", aux->numero);
        aux = aux->proximo;
    }
}

int isValueInList(NO* lista, int value) {
    NO *aux = lista;
    while(aux != NULL) {
        if (aux->numero == value) {
            return 1;
        }
        aux = aux->proximo;
    }
    return 0;
}

int main() {
    NO *Lista = iniciar();
    Lista = inserir_no_inicio(Lista, 5);
    Lista = inserir_no_inicio(Lista, 4);
    Lista = inserir_no_inicio(Lista, 12);
    Lista = inserir_no_inicio(Lista, 32);


    imprimir_lista(Lista);
    puts("\n");
    printf("O numero %d esta na lista? %s\n", 32, isValueInList(Lista, 32)?"True":"False");
    printf("O numero %d esta na lista? %s\n", 33, isValueInList(Lista, 33)?"True":"False");

    Lista = remover_do_inicio(Lista);
    imprimir_lista(Lista);
    puts("\n");
    printf("O numero %d esta na lista? %s\n", 32, isValueInList(Lista, 32)?"True":"False");
    printf("O numero %d esta na lista? %s\n", 33, isValueInList(Lista, 33)?"True":"False");
    Lista = remover_do_inicio(Lista);
    imprimir_lista(Lista);


    return 0;
}