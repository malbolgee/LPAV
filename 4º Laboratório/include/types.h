#ifndef TYPES_H
#define TYPES_H

typedef long long int lli;

/* Tipo para funções que accessam dados. */
typedef lli (*__data_access_t)(const void *);

/* Tipo para funções de comparação. */
typedef lli (*__compar_t)(const void *, const void *);

/* Tipo para funções de atribuição. */
typedef void (*__assign_fn_t)(const void *, void *);

/* Tipo para função de operações aritméticas. */
typedef void (*__oprtn_fn_t)(void *, void *, void *);

/* Tipo para funções de acesso a dados que retornam 
um elemento sem tipo. */
typedef void (*__data_access_fn_t)(const void *, void *);

#endif
