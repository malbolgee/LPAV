#include "lista.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void lista_eventos_listar(lista_eventos_t *lista)
{

    lista_eventos_t *_tmp = lista;

    while (_tmp)
    {

        printf("Time %lf, Target %d and type: %d\n", _tmp->item->time, _tmp->item->target, _tmp->item->type);
        _tmp = _tmp->next;
    }
}

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista)
{

    lista_eventos_t *_tmp;
    _tmp = (lista_eventos_t *)malloc(sizeof(lista_eventos_t));
    _alloc_check(_tmp, "Falha na alocação da lista");

    _tmp->item = evento;
    _tmp->next = *lista;
    *lista = _tmp;

    return true;
}

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista)
{

    if (*lista == NULL)
    {

        *lista = (lista_eventos_t *)malloc(sizeof(lista_eventos_t));
        _alloc_check(*lista, "Falha na alocação da lista");
        (*lista)->item = evento;
        (*lista)->next = NULL;

        return true;
    }
    else
    {

        lista_eventos_t *_tmp = *lista;

        while (_tmp->next != NULL)
            _tmp = _tmp->next;

        _tmp->next = (lista_eventos_t *)malloc(sizeof(lista_eventos_t));
        _alloc_check(_tmp->next, "Falha na alocação da lista");

        _tmp->next->item = evento;
        _tmp->next->next = NULL;

        return true;
    }

    return false;
}

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista)
{

    if (*lista == NULL || (*lista)->item->time > evento->time)
        return lista_eventos_adicionar_inicio(evento, lista);
    else if ((*lista)->next == NULL)
        return lista_eventos_adicionar_fim(evento, lista);
    else
    {

        lista_eventos_t *_current = *lista;

        while (_current->next != NULL && _current->next->item->time < evento->time)
            _current = _current->next;

        lista_eventos_t *new_node = (lista_eventos_t *)malloc(sizeof(lista_eventos_t));
        _alloc_check(new_node, "Falha na alocação da lista");

        new_node->item = evento;
        new_node->next = _current->next;
        _current->next = new_node;

        return true;
    }

    return false;
}

/* Checa se _mem foi alocada corretamente e imprime _message caso um erro tenha ocorrido. */
void _alloc_check(const void *_mem, const char *_message)
{

    if (_mem == NULL)
    {

        perror(_message);
        exit(EXIT_FAILURE);
    }
}

void lista_eventos_free(lista_eventos_t **lista)
{

    lista_eventos_t *_tmp = NULL;
    lista_eventos_t *_current = *lista;

    while (_current)
    {

        _tmp = _current;
        _current = _current->next;

        free(_tmp->item);
        _tmp->item = NULL;
        free(_tmp);
        _tmp = NULL;
    }
}

void usage(void)
{

    puts("Uso: main <nome_do_arquivo> [modo_de_inserção]");
    puts("  -o, -O\t\tmodo padrão de inserção, inserção ordenada (menor para maior).");
    puts("  -i, -I\t\tinserção no início.");
    puts("  -f, -F\t\tinserção no final.");
    puts("  -h    \t\timprime instruções de uso.");

}