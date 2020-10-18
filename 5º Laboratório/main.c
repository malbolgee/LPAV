#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void password_crack(char *, int);
void password_generate(char *, int, char *, int);

void usage(void);

int main(int argc, char **argv)
{

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

    password_crack(argv[2], size);

    return 0;
}

void password_crack(char *alphabet, int len)
{   

    char c[len];
    memset(c, 0, sizeof(char) * len);
    for (int i = 1; i <= len; ++i)
        password_generate(alphabet, i, c, len);

}

void password_generate(char *alphabet, int i, char *string, int len)
{

    if (i == 0)
    {
        printf("%s\n", string);
        return;
    }

    for (int j = 0; j < len; ++j)
    {

        char c[len];
        char _c[len];

        memset(c, 0, sizeof(char) * len);
        memset(_c, 0, sizeof(char) * len);

        strcat(_c, string);

        int index = strlen(_c);
        _c[index] = alphabet[j];
        strcat(c, _c);

        password_generate(alphabet, i - 1, c, len);
    }

    return;

}

void usage(void)
{

    puts("main <TAMANHO_MÁXIMO> <ALFABETO>");
    return;
}