#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void usage(void);
void password_crack(char *, int, int);

int main(int argc, char **argv)
{

    // 0 to (C + C^2 + C^3 + .. + C^n);
    // ((1 - x^(n + 1)) / (1 - x)) - 1;

    // C tamanho do alfabeto
    // N tamanho do password

    if (argc < 3 || argc > 3)   
    {

        usage();
        return 1;
    }

    size_t size = atoi(argv[1]);

    if (size <= 0)
    {

        puts("Tamanho inválido.");
        return 1;
    }

    int len = strlen(argv[2]);

    for (size_t i = 1; i <= size; ++i)
        password_crack(argv[2], i, len);

    return 0;
}

void password_crack(char *alphabet, int plength, int len)
{

    for (int i = 0; i < (int)pow(len, plength); ++i)
    {

        int x = i;
        char s[plength];
        memset(s, 0, sizeof(char) * plength);

        for (int j = 0; j < plength; ++j)
        {

            char _s[2] = {0};
            _s[0] = alphabet[x % len];
            strcat(s, _s);

            x /= len;
        }

        printf("%s\n", s);
    }
}


void usage(void)
{

    puts("main <TAMANHO_MÁXIMO> <ALFABETO>");
}