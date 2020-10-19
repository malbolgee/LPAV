#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "lista.h"

/** @see list_t */
typedef list_t node_t;

/** Representa um objeto de Grafo. */
typedef struct _graph_type
{

    size_t n_vertex;         /**< Indica o número de vértices.       */
    node_t **adjacency_list; /**< Representa a lista de adjacência.  */

} graph_t;

/** Inicializa um grafo com SIZE nós. 
 * 
 * @param _size O tamanho (quantidade de nós) que o grafo terá.
 * 
*/
graph_t *graph_init(const size_t _size);

/** Cria um vértice entre dst e item em graph. 
 * 
 * @param _item O item que será inserido no grafo.
 * @param dst   Índice da lista de adjacência onde o _item será inserido. 
 * @param graph É um ponteiro para um grafo.
 * 
 * @note Essa função sempre insere no início da lista de adjacência do grafo.
*/
void graph_push_in(void *_item, size_t dst, graph_t *graph) __nonnull((3));

/** Imprime na tela os nós de graph. 
 * 
 * @param graph É um ponteiro para um grafo.
 * @param func_show Função para acesso dos dados no grafo.
 *  
 * @warning O tipo de retorno da função de acesso pode mudar no futuro.
*/
void graph_show(graph_t *graph, __data_access_fn_t func_show) __nonnull((2));

/** Econtra a menor distância entre SRC e todos os outros nós do grafo.
 *  
 * @param graph É um ponteiro para um grafo.
 * @param dist É um vetor de distâncias.
 * @param mwidth É a largura de cada membro em dist.
 * @param src É o nó de origem do cálculo de distâncias.
 * @param bdist É a distância de src para ele mesmo.
 * @param infc É uma constante que representa uma distância inalcançável entre quaisquer dois nós
 * @param compare É uma função de comparação usada para comprar dois elementos de dist.
 * @param assign É função para fazer atribuição de valores em dist.
 * @param operation É uma função que realiza operações aritméticas entre dois elementos 
 * de dist ou entre um elemento de dist e um número.
 * 
 * @warning bdist e infc precisam ser do mesmo tipo de dist.
 * 
 * @return As distâncias estão em dist.
 * 
*/
void graph_djikstra(graph_t *graph, void *dist, size_t mwidth, const int src, void *bdist, void *infc, __compar_t compare, 
                    __assign_fn_t assign,  __oprtn_fn_t operation) __nonnull((1, 2, 5, 6, 7, 8, 9));

/** Libera graph da memória
 * 
 * @param graph É um ponteiro para um grafo.
 * 
*/
void graph_free(graph_t *graph);

#endif