#ifndef __PACKAGE_H__
#define __PACKAGE_H__

#include <stdint.h>

#define IP_OCTETS 4             /** Octetos do endereço IP.         */
#define ETH_OCTETS 6            /** Octetos do endereço MAC.        */
#define MAX_HTTP_DATA 1501      /** Tamanho máximo dos dados HTTP.  */

/** Representa um cabeçalho Ethernet. */
typedef struct _ethernet_hdr
{

    uint8_t  daddr[ETH_OCTETS]; /** Endereço MAC de destino.           */
    uint8_t  saddr[ETH_OCTETS]; /** Endereço MAC de origem.            */
    uint16_t protocol;          /** Protocolo da camada superior (IP). */

} __attribute__ ((packed)) ethernet_hdr_t;

/** Representa um cabeçalho IP. */
typedef struct _ip_hdr
{

    uint8_t  hdr_len:4;     /** Tamanho do cabeçalho.          */
    uint8_t  version:4;     /** Versão do IP.                  */
    uint8_t  tos;           /** Tipo do Serviço.               */
    uint16_t tot_len;       /** Tamanho Total do IP.           */
    uint16_t id;            /** Id do Pacote.                  */
    uint16_t frag_off;      /** Fragmentado?                   */
    uint8_t  ttl;           /** Tempo de Vida.                 */
    uint8_t  protocol;      /** Protocolo da Camada Superior.  */
    uint16_t check;         /** Checksum.                      */
    uint32_t saddr;         /** Endereço IP de Origem.         */
    uint32_t daddr;         /** Endereço IP de Destino.        */

} ip_hdr_t;

/** Representa um cabeçalho TCP. */
typedef struct _tcp_hdr
{

    uint16_t sport;         /** Porta TCP de Origem.           */
    uint16_t dport;         /** Porta TCP de Destino.          */
    uint32_t seq;           /** Sequência.                     */
    uint32_t ack_seq;       /** Acknowledgement.               */
    uint8_t  reserved:4;    /** Não Usado.                     */
    uint8_t  hdr_len:4;     /** Tamanho do Cabeçalho.          */
    uint8_t  flags;         /** Flags do TCP.                  */
    uint16_t window;        /** Tamanho da Janela.             */
    uint16_t check;         /** Checksum.                      */
    uint16_t urg_ptr;       /** Urgente.                       */

} tcp_hdr_t;

#endif