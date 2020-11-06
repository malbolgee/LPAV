#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/utils.h"
#include "../include/mpeg.h"

void usage(void);

const char *types = "IPB";
const char CODE_START[] = {0, 0, 1};
const char *fps[] = {"23.976fps", "24.000fps", "25.000fps", "29.970fps", "30.000fps", "50.000fps", "59.940fps", "60.000fps"};

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 2)
    {

        usage();
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    _alloc_check(fp, "Erro ao abrir arquivo");

    bool cstart = false;
    unsigned char *c = (unsigned char *)malloc(sizeof(unsigned char) * 3);
    unsigned char *code = (unsigned char *)malloc(sizeof(unsigned char));

    while (fread(c, sizeof(char), 3, fp) >= 3)
    {

        if (memcmp(c, CODE_START, 3) == 0)
        {

            fread(code, sizeof(char), 1, fp);

            if (*code == SEQUENCE)
            {

                unsigned char bytes[4] = {0};

                for (size_t i = 0; i < 4; ++i)
                    bytes[i] = fgetc(fp);

                unsigned width = bytes[0] * 16 + (bytes[1] >> 4);
                unsigned height = (bytes[1] & 0x0F) * 256 + bytes[2];
                unsigned frame_rate = bytes[3] & 0x0F;

                printf("--> Código: %.2x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = %s\n", *code, width, height, fps[frame_rate - 1]);
            }
            else if (*code == GRPOFPCTR)
                printf("--> Código: %.2x -- Group of Pictures\n", *code);
            else if (*code == SLICE)
                printf("--> Código: %.2x -- Slice\n", *code);
            else if (*code == PICTURE)
            {

                unsigned char byte = 0;

                for (size_t i = 0; i < 2; ++i)
                    byte = fgetc(fp);

                byte = (byte >> 3) & 0x07;

                printf("--> Código: %.2x -- Picture -- Tipo = %c\n", *code, types[byte - 1]);
            }
            else if (*code == SYSTEM)
                printf("--> Código: %.2x -- System\n", *code);
            else if (*code == PACK)
                printf("--> Código: %.2x -- Pack\n", *code);
            else if ((*code >= LPACKETV) && (*code <= RPACKETV))
                printf("--> Código: %.2x -- Packet Video\n", *code);
            else if ((*code >= LPACKETA) && (*code <= RPACKETA))
                printf("--> Código: %.2x -- Packet Audio\n", *code);
            else
                printf("--> Código: %.2x -- Tipo de stream não implementado\n", *code);

            cstart = true;
        }

        if (!cstart)
            fseek(fp, -2, SEEK_CUR);
        else
            cstart = false;
    }

    free(c);
    free(code);
    fclose(fp);

    return 0;
}

void usage(void)
{

    puts("main <NOME_DO_VIDEO>");
}
