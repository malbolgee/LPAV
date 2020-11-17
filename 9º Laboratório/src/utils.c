#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void _alloc_check(const void *_mem, const char *_message)
{

    if (_mem == NULL)
    {

        perror(_message);
        exit(EXIT_FAILURE);
    }
}