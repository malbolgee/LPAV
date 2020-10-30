#ifndef __LISTA_H__
#define __LISTA_H__

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>

/** Estrutura representa um nó da lista.*/
typedef struct _list
{

    void *item;         /**< O item que contém o dado no nó.*/
    struct _list *next; /**< Um ponteiro para o próximo nó. */

} list_t;

/** Estrutura auxiliar para guardar referências
dos pontos ao redor de '.cur'. */
typedef struct _ptr_list_ref
{

    list_t *prev;  /*< Ponteiro anterior. */
    list_t *cur;   /*< Ponteiro atual.    */
    list_t *_next; /*< Próximo ponteiro.  */

} ptr_list_ref_t;


/** Adiciona um novo item no início da lista.
 * 
 *  @param _item O item que será adicionado na lista.
 *  @param _list Um ponteiro de ponteiro para uma lista.
 *  
*/
bool list_add_start(void *_item, list_t **_list);


/** Adiciona um novo item no fim de list. 
 *  
 * @param _item Item que será inserido na lista.
 * @param _list Lista em que o item será inserido.
 * 
*/
bool list_add_end(void *_item, list_t **_list);


/** Adiciona um novo item de maneira ordenada utilizando
 * compare para realizar as comparações. 
 * 
 * @param _item O item que será inserido na lista.
 * @param _list A lista em que o item será inserido.
 * @param compare Função de comparação
 * 
*/
bool list_add_ord(void *_item, list_t **_list, __compar_t compare) __nonnull((3));


/** Localiza e apaga um item da lista utilizando compare 
 * para realizar as operações. 
 * 
 * @param _item Item que deve ser apagado da lista.
 * @param _list Um ponteiro para um ponteiro de lista.
 * @param compare Uma função de comparação que irá realizar as 
 * comparações ente os itens da lista e o item passado como parâmetro.
 *  
*/
bool list_erase(const void *_item, list_t **_list, __compar_t compare) __nonnull((3));


/** Retira e retorna o primeiro item de list. 
 * 
 * @param list É um ponteiro para um ponteiro de uma lista.
 * 
 * @return Retorna o item retirado ou NULL, se não havia nada para retirar.
 * 
*/
list_t *list_pop_head(list_t **list);


/** Verifica se list está vazia. 
 * 
 * @param list É um ponteiro par uma lista.
 * @return verdadeiro se a lista está vazia e falso se não está.
 * 
*/
bool list_is_empty(const list_t *list);


/** Procura um item em list utilizando compare para fazer 
 * as comparações. 
 * 
 * @param _item O item que está sendo propcurado.
 * @param _list Um ponteiro para uma lista.
 * @param _ret Um ponteiro para uma struct do tipo ptr_list_ref_t.
 * @param compare Uma função de comparação que irá realizar as comparações 
 * entre os itens da lista e o _item passado como parâmetro. 
 *  
 * */
void list_search(const void *_item, list_t *_list,
                ptr_list_ref_t *_ret, __compar_t compare) __nonnull((3, 4));

/**
 * Percorre uma lista usando func_s para mostrar os itens.
 * 
 * @param list É um ponteiro para uma lista
 * @param func_s É um ponteiro para uma função que irá acessar os itens da lista.
 * 
*/
void list_show(list_t *list, __data_access_fn_t func_s);

/** Libera list da memória. 
 * 
 * @param _list Um ponteiro para um ponteiro de uma lista.
 * 
*/
void list_free(list_t **_list);

#endif