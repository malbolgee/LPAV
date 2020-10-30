#ifndef __TYPES_H__
#define __TYPES_H__

typedef long long int lli;

/** Tipo para funções que accessam dados e retornam
 * algum dado. */
typedef void *(*__data_access_t)(const void *);

/** Tipo para funções de acesso a dados e não retornam nada. */
typedef void (*__data_access_fn_t)(const void *);

/** Tipo para funções de comparação. */
typedef int (*__compar_t)(const void *, const void *);

/** Tipo para funções de atribuição. */
typedef void (*__assign_fn_t)(const void *, void *);

/** Tipo para função de operações aritméticas. */
typedef void (*__oprtn_fn_t)(void *, void *, void *);

#endif
