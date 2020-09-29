#ifndef _GRAPH_H
#define _GRAPH_H

#include "lista.h"

typedef list_t node_t;

/* Representa um objeto de Grafo. */
typedef struct _graph_type
{

    size_t n_vertex;         /* Indica o número de vértices.       */
    node_t **adjacency_list; /* Representa a lista de adjacência.  */

} graph_t;

/* Inicializa um grafo com SIZE nós. */
graph_t *graph_init(const size_t _size);

/* Cria um vértice entre src e item em graph. */
void graph_push_in(void *_item, size_t src, graph_t *graph) __nonnull((3));

/* Imprime na tela os nós de graph. */
void graph_show(graph_t *graph, __data_access_t func_show) __nonnull((2));

/* Encontra a menor distância entre SRC e todos os outros nós de graph. 
DIST é um vetor de distâncias com cada membro tendo MWIDTH de tamanho.
BDIST e INFC são, respectivamente, a distância de SRC para ele mesmo e 
uma constante indicando a distância inalcançável entre quaisquer dois 
vértices(ela precisa ser do tipo de DIST). COMPARE, ASSIGN e OPERATION,
são, respectivamente, funções para comparar dois elementos de DIST, 
atribuir a DIST em uma posição qualquer um valor de seu tipo e
realizar operações aritméticas entre dois elementos de DIST ou 
um elemento de DIST e um número que seja do tipo de um elemento em DIST.*/
void graph_djikstra(void *dist, graph_t *graph, const int src, void *bdist, size_t mwidth, __compar_t compare, 
                    __assign_fn_t assign, void *infc, __oprtn_fn_t operation) __nonnull((1, 2, 6, 7, 9));

/* Libera graph da memória*/
void graph_free(graph_t *graph);

#endif