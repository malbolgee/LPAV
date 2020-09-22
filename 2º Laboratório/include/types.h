#ifndef TYPES_H
#define TYPES_H

typedef long long int lli;

/* Tipo para função de acesso aos dados em item. */
typedef lli (*__data_access_t)(const void *);
typedef lli (*__compar_t)(const void *, const void *);

#endif
