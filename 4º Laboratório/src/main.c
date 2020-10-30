#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/lista.h"
#include "../include/types.h"
#include "../include/graph.h"
#include "../include/utils.h"

typedef struct _pos
{

    double x, y;

} pos_t;

typedef struct _event
{

    int type;
    int target;
    double time;

} event_t;

void usage(void);
lli func_show(const void *);

int compar_ord(const void *a, const void *b);
static void begin_simulation(graph_t *graph, list_t **list);
static event_t *make_new_event(int type, int target, double time);
static void populate(graph_t *_graph, pos_t *_pos, const double _conn_r);

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 2)
    {

        usage();
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    _alloc_check(fp, "Erro ao abrir arquivo.");

    size_t size = 0;
    double conn_radius = 0.0;

    int z = fscanf(fp, "%lu\t%lf", &size, &conn_radius);

    if (z != 2)
    {

        puts("Erro na leitura das variáveis.");
        return EXIT_FAILURE;
    }

    if (size <= 0)
    {

        puts("Tamanho inválido.");
        return EXIT_FAILURE;
    }

    if (conn_radius <= 0)
    {

        puts("Raio de comunicação inválido.");
        return EXIT_FAILURE;
    }

    pos_t pos[size];
    graph_t *grafo = graph_init(size);

    size_t id;
    double x, y;

    while (~fscanf(fp, "%lu\t%lf\t%lf\n", &id, &x, &y))
        pos[id].x = x, pos[id].y = y;

    fclose(fp);

    populate(grafo, pos, conn_radius);

    list_t *ord_list = NULL;
    begin_simulation(grafo, &ord_list);

    list_free(&ord_list);
    graph_free(grafo);

    return 0;
}

static event_t *make_new_event(int type, int target, double time)
{

    event_t *new_event = (event_t *)malloc(sizeof(event_t));
    _alloc_check(new_event, "Erro ao alocar novo evento.");

    new_event->type = type;
    new_event->target = target;
    new_event->time = time;

    return new_event;
}

static void begin_simulation(graph_t *graph, list_t **list)
{

    event_t *new_event = make_new_event(1, 0, 1.0);
    list_add_ord(new_event, list, compar_ord);

    bool _p_sent[graph->n_vertex];
    memset(_p_sent, false, sizeof(_p_sent));

    list_t *_tmp = NULL;

    while ((_tmp = list_pop_head(list)) != NULL)
    {

        printf("[%3.6f] Nó %d recebeu pacote\n", ((event_t *)_tmp->item)->time, ((event_t *)_tmp->item)->target);

        if (!_p_sent[((event_t *)_tmp->item)->target])
        {

            for (node_t *i = graph->adjacency_list[((event_t *)_tmp->item)->target]; i != NULL; i = i->next)
            {

                printf("\t--> Repassando pacote para o nó %d ...\n", *(int *)i->item);
                int target = *(int *)i->item;
                double time = ((event_t *)_tmp->item)->time + (0.1 + (target * 0.01));
                new_event = make_new_event(1, target, time);

                list_add_ord(new_event, list, compar_ord);
            }

            _p_sent[((event_t *)_tmp->item)->target] = true;
        }

        free(_tmp->item);
        _tmp->item = NULL;
        free(_tmp);
        _tmp = NULL;
    }
}

static void populate(graph_t *_graph, pos_t *_pos, const double _conn_r)
{

    size_t size = _graph->n_vertex;
    for (size_t i = 0; i < size; ++i)
    {

        for (size_t j = 0; j < size; ++j)
        {

            if (i != j)
            {

                if (hypot(_pos[i].x - _pos[j].x, _pos[i].y - _pos[j].y) < _conn_r)
                {

                    int *v = (int *)malloc(sizeof(int));
                    *v = j;
                    graph_push_in(v, i, _graph);
                }
            }
        }
    }
}

int compar_ord(const void *a, const void *b)
{

    const double r = ((event_t *)a)->time - ((event_t *)b)->time;
    if ((r < 0.0000001) && (r > (-0.0000001)))
    {

        if (((event_t *)a)->target <= ((event_t *)b)->target)
            return -1;
        else
            return 1;
    }
    else if (((event_t *)a)->time < ((event_t *)b)->time)
        return -1;
    else
        return 1;
}

lli func_show(const void *a)
{

    printf("%d ", *(int *)a);
    return 0;
}

void usage(void)
{

    puts("main <NOME_DO_ARQUIVO>");
}
