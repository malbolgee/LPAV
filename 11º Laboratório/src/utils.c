#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

void _alloc_check(const void *_mem, const char *_message)
{

    if (_mem == NULL)
    {

        perror(_message);
        exit(EXIT_FAILURE);
    }
}

void ensure(bool _expression, char *_message)
{

    if (_expression == false)
        fprintf(stderr, "%s\n", _message), exit(1);
}