#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/mpeg.h"

#define BYTE 1048576 /** 1 Mb em bytes. */
#define MAX_STRING_FILE_NAME_SIZE 100 /** O maior tamanho que a string do nome do arquivo de saída. */
#define CODE_PREFIX_SIZE 4 /** Tamanho do CODE_PREFIX. */

#define MBTOB(x, y) (x * y) /** Converte megabytes para bytes. */

/** Informa o uso correto do programa. */
void usage(void);

int main(int argc, char **argv)
{

    if (argc < 3 || argc > 3)
    {

        usage();
        return 1;
    }

    size_t size = atoll(argv[2]);

    if (size <= 0)
    {

        usage();
        return 1;
    }

    size_t piece = 1;
    size = MBTOB(size, BYTE);

    FILE *fp = fopen(argv[1], "rb");
    _alloc_check(fp, "Erro ao abrir arquivo");

    char stringFileName[MAX_STRING_FILE_NAME_SIZE] = {0};
    sprintf(stringFileName, "video_parte_%ld.mpg", piece);
    printf("Criando arquivo %s ..\n", stringFileName);

    FILE *fs = fopen(stringFileName, "wb");
    _alloc_check(fs, "Erro ao abrir arquivo");

    unsigned char code_prefix[CODE_PREFIX_SIZE];
    unsigned char *buffer = (unsigned char *)calloc(size + 1, sizeof(unsigned char));

    size_t tamBuffer, tamFile;
    tamBuffer = tamFile = 0;
    while (fread(&code_prefix, sizeof(unsigned char), CODE_PREFIX_SIZE, fp) >= CODE_PREFIX_SIZE)
    {

        if (memcmp(code_prefix, "\x00\x00\x01\xB3", CODE_PREFIX_SIZE) != 0)
        {

            buffer[tamBuffer] = code_prefix[0];
            ++tamBuffer;
            fseek(fp, (-CODE_PREFIX_SIZE) + 1, SEEK_CUR);
            continue;
        }
        else
        {

            memcpy(&buffer[tamBuffer], code_prefix, CODE_PREFIX_SIZE);
            tamBuffer += CODE_PREFIX_SIZE;

            if (tamFile + tamBuffer > size)
            {

                fclose(fs);
                sprintf(stringFileName, "video_parte_%ld.mpg", ++piece);
                printf("Criando arquivo %s ..\n", stringFileName);
                fs = fopen(stringFileName, "wb");
                fwrite(buffer, sizeof(unsigned char), tamBuffer, fs);
                tamFile = tamBuffer;
                tamBuffer = 0;
            }
            else
            {

                fwrite(buffer, sizeof(unsigned char), tamBuffer, fs);
                tamFile += tamBuffer;
                tamBuffer = 0;
            }
        }
    }

    fclose(fs);
    fclose(fp);
    free(buffer);

    return 0;
}

void usage(void)
{

    puts("main <NOME_DO_VIDEO>");
}
