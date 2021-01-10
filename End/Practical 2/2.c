#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include<arpa/inet.h>
#define PCKT_LEN 8192

struct ipheader {
    unsigned char iph_ihl: 5, iph_ver: 4;
    unsigned char iph_tos;
    unsigned short int iph_len;
    unsigned short int iph_ident;
    unsigned char iph_flag;
    unsigned short int iph_offset;
    unsigned char iph_ttl;
    unsigned char iph_protocol;
    unsigned short int iph_chksum;
    unsigned int iph_sourceip;
    unsigned int iph_destip;
    unsigned short ip_offset;
    unsigned short ip_checksum;
};

unsigned short csum(unsigned short * buf, int nwords) {
    unsigned long sum;
    for (sum = 0; nwords > 0; nwords--)
        sum += * buf++;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

int main(int argc, char * argv[]) {
    int sd;
    char buffer[PCKT_LEN];
    struct ipheader * ip = (struct ipheader * ) buffer;
    ip -> iph_ihl = 5;
    ip -> iph_ver = 4;
    ip -> iph_tos = 0;
    ip -> ip_offset = 0;
    ip -> ip_checksum = 0;
    ip -> iph_flag = 0;
    ip -> iph_len = sizeof(struct ipheader) + atoi(argv[3]);
    ip -> iph_ident = htons(atoi(argv[4]));
    ip -> iph_ttl = argv[5];
    ip -> iph_protocol = argv[6];
    ip -> iph_sourceip = inet_addr(argv[1]);
    ip -> iph_destip = inet_addr(argv[2]);
    ip -> iph_chksum = csum((unsigned short * ) buffer, ip -> iph_len);
    printf("%x\n", ip -> iph_chksum);
}