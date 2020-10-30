#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <arpa/inet.h>

typedef struct chunk_png
{

    int length;
    int chunk_type;

} chunk_png_t;

struct chunk_png_IHDR
{

    int width;
    int height;
    char bit_depth;
    char colour_type;
    char compression_method;
    char filter_method;
    char interlace_method;

} __attribute__((packed));

typedef struct chunk_png_IHDR chunk_png_IHDR_t;

#define IDHR 0x52444849

void usage(void);

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 2)
    {

        usage();
        return 1;

    }

    FILE *fp = fopen(argv[1], "rb");
    _alloc_check(fp, "Erro ao abrir arquivo");

    fseek(fp, 8, SEEK_CUR);
    chunk_png_t *chunk_png = (chunk_png_t *)malloc(sizeof(chunk_png_t));
    char *chunk_type = (char *)calloc(5, sizeof(char));

    size_t count = 0;
    while (fread(chunk_png, sizeof(chunk_png_t), 1, fp))
    {

        printf("Lendo chunk: %ld\n", ++count);
        printf("    --> Tamanho: %d\n", ntohl(chunk_png->length));
        printf("    --> Tipo: %.4s\n", (char *)&chunk_png->chunk_type);

        if (chunk_png->chunk_type == IDHR)
        {

            printf("    --> Tipo:\t %s\n", chunk_type);
            chunk_png_IHDR_t *chunk_png_IHDR = (chunk_png_IHDR_t *)malloc(sizeof(chunk_png_IHDR_t));
            fread(chunk_png_IHDR, sizeof(chunk_png_IHDR_t), 1, fp);

            printf("        --> Largura: %d\n", ntohl(chunk_png_IHDR->width));
            printf("        --> Altura: %d\n", ntohl(chunk_png_IHDR->height));

            free(chunk_png_IHDR);
            fseek(fp, 4, SEEK_CUR);
        }
        else
            fseek(fp, ntohl(chunk_png->length) + 4, SEEK_CUR);
    }

    fclose(fp);
    free(chunk_png);

    return 0;
}

void usage(void)
{

    puts("main <NOME_DO_ARQUIVO>");
}