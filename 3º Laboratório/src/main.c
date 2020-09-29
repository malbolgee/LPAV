#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/types.h"
#include "../include/graph.h"
#include "../include/utils.h"

void usage(void);

lli func_show(const void *);

typedef struct _pos
{

    double x, y;

} pos_t;

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 2)
    {

        usage();
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");

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

        puts("Tamnho inválido.");
        return EXIT_FAILURE;
    }

    if (conn_radius <= 0)
    {

        puts("Raio de comunicação inválido.");
        return EXIT_FAILURE;
    }

    graph_t *grafo = graph_init(size);
    pos_t pos[size];

    size_t id;
    double x, y;

    while (~fscanf(fp, "%lu\t%lf\t%lf\n", &id, &x, &y))
    {

        pos[id].x = x;
        pos[id].y = y;
    }

    for (size_t i = 0; i < id + 1; ++i)
    {

        for (size_t j = 0; j < id + 1; ++j)
        {

            if (i != j)
            {

                if (hypot(pos[i].x - pos[j].x, pos[i].y - pos[j].y) < conn_radius)
                {

                    int *v = (int *)malloc(sizeof(int));
                    *v = j;
                    graph_push_in(v, i, grafo);
                }
            }
        }
    }

    graph_show(grafo, func_show);

    graph_free(grafo);
    fclose(fp);

    return 0;
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
