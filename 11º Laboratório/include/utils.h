#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

/** Checa se _mem foi alocada corretamente e imprime _message caso um erro tenha ocorrido. 
 * 
 * @param mem Endereço de memória a ser testado.
 * @param message String de erro para ser impressa em caso de falha na alocação.
 * 
*/
void _alloc_check(const void *_mem, const char *_message);

/**
 * 
 * Checa se uma determinada expressão é verdadeira e imprime uma mensagem caso não seja.
 * 
 * @param expression A expressão a ser verificada.
 * @param message Uma mensagem a se exibida.
 * 
*/
void ensure(bool _expression, char *_message);

#endif