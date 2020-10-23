#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

struct zip_file_hdr
{

    int signature;
    short version;
    short flags;
    short compression;
    short mod_time;
    short mod_date;
    int crc;
    int compressed_size;
    int uncompressed_size;
    short name_length;
    short extra_field_length;

} __attribute__((packed));

typedef struct zip_file_hdr zip_file_hdr;

void usage(void);

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 2)
    {

        usage();
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");

    if (fp == NULL)
    {

        _alloc_check(fp, "Erro ao abrir aquivo");
        return 1;
    }

    size_t index = 0;
    zip_file_hdr *header = (zip_file_hdr *)malloc(sizeof(zip_file_hdr));

    while (true)
    {

        fread(header, sizeof(zip_file_hdr), 1, fp);

        if (header->signature != 0x04034b50)
            break;

        char *file_name = (char *)calloc(header->name_length + 1, sizeof(char));
        fread(file_name, sizeof(char), header->name_length, fp);

        printf("Arquivo %ld ..\n", ++index);
        printf("  --> Nome do Arquivo: %s\n", file_name);
        printf("  --> Tamanho Compactado: %d\n", header->compressed_size);
        printf("  --> Tamanho Descompactado: %d\n", header->uncompressed_size);

        free(file_name);

        fseek(fp, header->compressed_size + header->extra_field_length, SEEK_CUR);
    }

    free(header);
    fclose(fp);

    return 0;
}

void usage(void)
{

    puts("main <NOME_DO_ARQUIVO>");
}