#ifndef __UTILS_H__
#define __UTILS_H__

/** Checa se _mem foi alocada corretamente e imprime _message caso um erro tenha ocorrido. 
 * 
 * @param _mem Endereço de memória a ser testado.
 * @param _message String de erro para ser impressa em caso de falha na alocação.
 * 
*/
void _alloc_check(const void *_mem, const char *_message);

#endif