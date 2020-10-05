#ifndef LISTA_H
#define LISTA_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>

/* Estrutura representa um nó da lista. */
typedef struct _list
{

    void *item;
    struct _list *next;

} list_t;

/* Estrutura auxiliar para guardar referências
dos pontos ao redor de '.cur'. */
typedef struct _ptr_list_ref
{

    list_t *prev;  /* Ponteiro anterior. */
    list_t *cur;   /* Ponteiro atual.    */
    list_t *_next; /* Próximo ponteiro.  */

} ptr_list_ref_t;

/* Tipo para funções de inserção. */
typedef _Bool (*__insert_list_t)(void *, list_t **);
typedef __insert_list_t insert_list_t;

/* Adiciona um novo item no início da list. */
bool list_add_start(void *_item, list_t **_list);

/* Adiciona um novo item no fim de list. */
bool list_add_end(void *_item, list_t **_list);

/* Adiciona um novo item de maneira ordenada utilizando
compare para realizar as comparações. */
bool list_add_ord(void *_item, list_t **_list, __compar_t compare) __nonnull((3));

/* Localiza e apaga um item da lista utilizando compare
para realizar as operações. */
bool list_erase(const void *_item, list_t **_list, __compar_t compare) __nonnull((3));

/* Retira e retorna o primeiro item de list. */
list_t * list_pop_head(list_t **list);

/* Verifica se list está vazia. */
bool list_is_empty(const list_t *list);

/* Procura um item em list utilizando compare para fazer
as comparações. */
ptr_list_ref_t *list_search(const void *_item, list_t *_list,
                            ptr_list_ref_t *_ret, __compar_t compare) __nonnull((3, 4));

/* Libera list da memória. */
void list_free(list_t **_list);

#endif