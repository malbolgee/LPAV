#ifndef HASH_H
#define HASH_H

#include "lista.h"
#include "types.h"
#include <stdio.h>

/*
    O cálculo padrão de hash é feito simplesmente tirando-se
    o resto da divisão entre algum dado de uma strutura definida
    pelo usuário e o tamanho da tabela. Caso se deseje utilizar uma
    função personalizada, o retorno deve ser um long long int
    e deve ser passado como o parâmetro hash para as funções que
    apresentem a possibilidade desse argumento.
*/

typedef list_t hash_table_list_t;

/* Estrutura representa uma hash table. */
typedef struct _hash_table
{

    size_t size;
    hash_table_list_t **table;

} hash_table_t;

/* Inicializa uma tabela hash com SIZE posições. */
hash_table_t *hash_table_init(const size_t _size);

/* Adiciona um ITEM à TABELA. Se HASH for -1, então realiza o 
cálculo de hash padrão, caso contrário, utiliza hash, usando 
func_access para acessar os dados em ITEM. */
bool hash_table_add(void *item, hash_table_t *table, lli hash,
                    __data_access_t func_access) __nonnull((1, 2, 4));

/* Imprime na tela todas as posições de table que contém elementos. */
void hash_table_show(hash_table_t *table, __data_access_t func_show);

/* Libera table da memória. */
void hash_table_free(hash_table_t *table);

/* Localiza item em table. Se hash for -1, então utiliza o 
cálculo padrão de hash, caso contrário, utiliza o valor de hash. */
void *hash_table_serach(const void *_item, hash_table_t *table, __compar_t compare,
                        lli hash, __data_access_t func_access) __nonnull((3, 5));

/* Retira um item da tabela. */
bool hash_table_erase(const void *_item, hash_table_t *table, lli hash,
                      __compar_t compare, __data_access_t func_access) __nonnull((2, 4));

#endif