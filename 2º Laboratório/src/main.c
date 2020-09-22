#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/lista.h"
#include "../include/hash.h"
#include "../include/utils.h"

typedef struct _person
{

    lli cpf;
    int idade;
    char nome[51];

} person_t;

lli func(const void *_item);
lli func_access(const void *data);
void usage(void);

int main(int argc, char **argv)
{

    if (argc < 3 || argc > 3)
    {

        usage();
        exit(EXIT_FAILURE);
    }

    size_t size = abs(atol(argv[1]));

    if (size == 0)
    {

        puts("Forneça um tamanho válido.");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[2], "r");
    _alloc_check(fp, "Erro ao abrir arquivo");

    person_t *person = (person_t *)malloc(sizeof(person_t));
    _alloc_check(person, "Erro ao alocar item.");

    hash_table_t *hash_table = hash_table_init(size);
    while (~fscanf(fp, "%[^\t]\t%lld\r%d\n", person->nome, &person->cpf, &person->idade))
    {

        hash_table_add(person, hash_table, -1, func_access);
        person = (person_t *)malloc(sizeof(person_t));
        _alloc_check(person, "Erro ao alocar item.");
    }

    hash_table_show(hash_table, func);

    hash_table_free(hash_table);
    fclose(fp);

    return 0;
}

lli func(const void *_item)
{

    printf("\t%s\t%lld\t%d\n",
           ((person_t *)_item)->nome,
           ((person_t *)_item)->cpf,
           ((person_t *)_item)->idade);

    return 0;
}

lli func_access(const void *data)
{

    return ((person_t *)data)->cpf;
}

void usage(void)
{

    puts("Uso:");
    puts("   main [NOME_DO_ARQUIVO] [TAMANHO_DA_TABELA]");
}