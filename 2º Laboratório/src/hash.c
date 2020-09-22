#include <stdbool.h>
#include <stdlib.h>
#include "../include/lista.h"
#include "../include/types.h"
#include "../include/hash.h"
#include "../include/utils.h"

static lli _hash_calc(lli _x, lli _y);

hash_table_t *hash_table_init(size_t _size)
{

    hash_table_t *hash_table = (hash_table_t *)calloc(1, sizeof(hash_table_t));
    _alloc_check(hash_table, "Erro ao alocar hash table");

    hash_table->table = (hash_table_list_t **)calloc(_size, sizeof(hash_table_list_t *));
    _alloc_check(hash_table->table, "Erro ao alocar a lista");
    hash_table->size = _size;

    return hash_table;
}

bool hash_table_add(void *item, hash_table_t *table, lli hash, __data_access_t func_access)
{

    if (hash == -1)
        hash = _hash_calc(func_access(item), table->size);

    return list_add_start(item, &table->table[hash]);
}

void hash_table_show(hash_table_t *table, __data_access_t func_show)
{

    for (size_t i = 0; i < table->size; ++i)
    {

        printf("POSIÇÃO %ld DA TABELA HASH:\n", i);
        for (hash_table_list_t *j = table->table[i]; j != NULL; j = j->next)
            func_show(j->item);
    }
}

void hash_table_free(hash_table_t *table)
{

    for (size_t i = 0; i < table->size; ++i)
        list_free(&table->table[i]);

    free(table->table);
    free(table);
}

void *hash_table_serach(const void *key, hash_table_t *table, __compar_t compare, lli hash, __data_access_t func_access)
{

    if (hash == -1)
        hash = _hash_calc(func_access(key), table->size);

    if (table->table[hash] == NULL)
        return NULL;
    else if (compare(table->table[hash]->item, key) == 0)
        return table->table[hash]->item;
    else
    {

        hash_table_list_t *_tmp = table->table[hash];
        while (_tmp != NULL)
        {

            if (compare(_tmp->item, key) == 0)
                return _tmp->item;

            _tmp = _tmp->next;
        }

        return NULL;
    }
}

bool hash_table_erase(const void *_item, hash_table_t *table, lli hash, __compar_t compare, __data_access_t func_access)
{

    if (hash == -1)
        hash = _hash_calc(func_access(_item), table->size);
    
    return list_erase(_item, &table->table[hash], compare);
}

static lli _hash_calc(lli _x, lli _y)
{

    return _x % _y;
}