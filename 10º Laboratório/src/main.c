#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "../include/utils.h"
#include "../include/package.h"

void usage(void);

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        usage();
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    _alloc_check(fp, "Erro ao abrir arquivo");

    ethernet_hdr_t eth_hdr = {0};
    fread(&eth_hdr, sizeof(ethernet_hdr_t), 1, fp);

    puts("Lendo Ethernet ..");
    printf("  --> MAC de Origem:  ");
    for (size_t i = 0; i < ETH_OCTETS; ++i)
        printf("%.2x%c", eth_hdr.saddr[i], i < ETH_OCTETS - 1 ? ':' : '\n');

    printf("  --> MAC de Destino: ");
    for (size_t i = 0; i < ETH_OCTETS; ++i)
        printf("%.2x%c", eth_hdr.daddr[i], i < ETH_OCTETS - 1 ? ':' : '\n');

    ip_hdr_t ip_hdr = {0};
    fread(&ip_hdr, sizeof(ip_hdr_t), 1, fp);

    puts("Lendo IP ..");
    printf("  --> Versão do IP: %hhu\n", ip_hdr.version);
    printf("  --> Tamanho do cabeçalho: %hu bytes\n", ip_hdr.hdr_len * 4);
    printf("  --> Tamanho do pacote: %hu bytes\n", ntohs(ip_hdr.tot_len));
    printf("  --> Endereço IP de Origem:  ");

    for (size_t i = 0; i < IP_OCTETS; ++i)
        printf("%hhu%c", *((unsigned char *)&ip_hdr.saddr + i), i < IP_OCTETS - 1 ? '.' : '\n');

    printf("  --> Endereço IP de Destino: ");
    for (size_t i = 0; i < IP_OCTETS; ++i)
        printf("%hhu%c", *((unsigned char *)&ip_hdr.daddr + i), i < IP_OCTETS - 1 ? '.' : '\n');

    fseek(fp, (ip_hdr.hdr_len * 4) - sizeof(ip_hdr_t), SEEK_CUR);

    tcp_hdr_t tcp_hdr = {0};
    fread(&tcp_hdr, sizeof(tcp_hdr_t), 1, fp);
    puts("Lendo TCP ..");
    printf("  --> Porta de Origem:  %hu\n", ntohs(tcp_hdr.sport));
    printf("  --> Porta de Destino: %hu\n", ntohs(tcp_hdr.dport));
    printf("  --> Tamanho do cabeçalho: %hu bytes\n", tcp_hdr.hdr_len * 4);

    fseek(fp, (tcp_hdr.hdr_len * 4) - sizeof(tcp_hdr_t), SEEK_CUR);

    uint16_t size_http_data = ntohs(ip_hdr.tot_len) - ((tcp_hdr.hdr_len + ip_hdr.hdr_len) * 4);

    puts("Lendo Dados (HTTP) ..");
    printf("  --> Tamanho dos dados: %hu bytes\n", size_http_data);
    puts("  --> Dados: ");

    char http_data_char = 0;
    while (fread(&http_data_char, sizeof(char), 1, fp))
        putchar_unlocked(http_data_char);

    return 0;
}

void usage(void)
{

    puts("main <NOME_DO_ARQUIVO>");
}
