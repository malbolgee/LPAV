#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "../include/graph.h"
#include "../include/lista.h"
#include "../include/utils.h"

graph_t *graph_init(const size_t _size)
{

    graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
    _alloc_check(graph, "Erro ao alocar o grafo.");

    graph->adjacency_list = (node_t **)calloc(_size, sizeof(node_t *));
    _alloc_check(graph->adjacency_list, "Erro ao alocar a lista de adjacência.");

    graph->n_vertex = _size;

    return graph;
}

void graph_push_in(void *_item, size_t src, graph_t *graph)
{

    list_add_start(_item, &graph->adjacency_list[src]);
}

void graph_show(graph_t *graph, __data_access_t func_show)
{

    for (size_t i = 0; i < graph->n_vertex; ++i)
    {

        printf("NÓ %lu: ", i);
        for (node_t *j = graph->adjacency_list[i]; j != NULL; j = j->next)
            func_show(j->item);

        putchar('\n');
    }
}

void graph_free(graph_t *graph)
{

    for (size_t i = 0; i < graph->n_vertex; ++i)
        list_free(&graph->adjacency_list[i]);

    free(graph->adjacency_list);
    graph->adjacency_list = NULL;
    free(graph);
    graph = NULL;
}

void graph_djikstra(void *dist, graph_t *graph, const int src, void *bdist, size_t mwidth, __compar_t compare, __assign_fn_t assign, void *infc, __oprtn_fn_t operation)
{

    char *base_dist = (char *)dist;

    if (graph->n_vertex == 0LLU)
        return;

    char *_visited = (char *)calloc(graph->n_vertex, sizeof(char));

    size_t size = graph->n_vertex;

    for (size_t i = 0; i < size; ++i)
        assign(base_dist + i * mwidth, infc);

    assign(base_dist + src * mwidth, bdist);

    for (size_t i = 0; i < size; ++i)
    {

        int v = -1;
        for (size_t j = 0; j < size; ++j)
            if (!_visited[j] && (v == -1 || compare(base_dist + j * mwidth, base_dist + v * mwidth) < 0LL))
                v = j;

        if (compare(base_dist + v * mwidth, infc) == 0LL)
            break;

        _visited[v] = true;

        void *result = malloc(mwidth);
        void *length = malloc(mwidth);
        void *destination = malloc(sizeof(int));
        for (node_t *j = graph->adjacency_list[v]; j != NULL; j = j->next)
        {

            assign(j->item, destination);
            assign(j->item, length);

            operation(base_dist + v * mwidth, length, result);
            if (compare(result, base_dist + (*(int *)destination) * mwidth) < 0LL)
                assign(base_dist + (*(int *)destination) * mwidth, result);
        }

        free(result);
        free(length);
        free(destination);
    }

    free(_visited);
}