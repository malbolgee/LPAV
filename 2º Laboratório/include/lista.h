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

/* Adiciona um novo item no início da lista. */
bool list_add_start(void *_item, list_t **_list);

/* Adiciona um novo item no fim da lista. */
bool list_add_end(void *_item, list_t **_list);

/* Adiciona um novo item de maneira ordenada. */
bool list_add_ord(void *_item, list_t **_list, __compar_t compare) __nonnull((3));

/* Apaga um item da lista. */
bool list_erase(const void *_item, list_t **_list, __compar_t compare) __nonnull((3));

/* Procura um item em uma lista. */
ptr_list_ref_t *list_search(const void *_item, list_t *_list,
                            ptr_list_ref_t *_ret, __compar_t compare) __nonnull((3, 4));

/* Libra a lista da memória. */
void list_free(list_t **_list);

#endif