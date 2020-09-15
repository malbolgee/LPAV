#include <stdbool.h>
#pragma once

typedef struct _event
{

    int type;
    int target;
    double time;

} evento_t;

typedef struct _list_events
{

    evento_t *item;
    struct _list_events *next;

} lista_eventos_t;

/* Tipo para funções de inserção. */
typedef bool (*__insere_evento_lista_t)(evento_t *, lista_eventos_t **);
typedef __insere_evento_lista_t insere_evento_lista_t;

void _alloc_check(const void *_mem, const char *_message);
void lista_eventos_listar(lista_eventos_t *lista);
bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista);
bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista);
bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista);
void lista_eventos_free(lista_eventos_t **lista);
void usage(void);