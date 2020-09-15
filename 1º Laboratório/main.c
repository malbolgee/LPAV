#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lista.h"

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 3)
    {

        usage();
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    _alloc_check(fp, "Erro na leitura do arquivo");

    int idx = 2;
    char ch = 'o';

    switch (ch = getopt(argc, argv, "FIOfioh"))
    {

        case 'F':
        case 'f':
            idx = 0;
            break;
        case 'I':
        case 'i':
            idx = 1;
            break;
        case -1:
        case 'O':
        case 'o':
            idx = 2;
            break;
        default:
        case 'h':
        case '?':
            usage();
            return 1;
    }

    evento_t *item = (evento_t *)malloc(sizeof(evento_t));
    _alloc_check(item, "Falha na alocação do Evento");

    lista_eventos_t *lista = NULL;
    insere_evento_lista_t funcs[3] = {lista_eventos_adicionar_inicio,
                                      lista_eventos_adicionar_fim,
                                      lista_eventos_adicionar_ordenado};

    while (~fscanf(fp, "%lf\t%d\t%d", &item->time, &item->target, &item->type))
    {

        funcs[idx](item, &lista);
        item = (evento_t *)malloc(sizeof(evento_t));
        _alloc_check(item, "Falha na alocação do Evento");
    }

    lista_eventos_listar(lista);
    lista_eventos_free(&lista);

    fclose(fp);

    return 0;
}
