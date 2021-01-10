#include <stdio.h>
#include <string.h>
#include <math.h>

void extractIpAddress(unsigned char * sourceString, short * ipAddress) {
    unsigned short len = 0;
    unsigned char oct[5] = {0}, cnt = 0, cnt1 = 0, i, buf[8];
    len = strlen(sourceString);
    for (i = 0; i < len; i++) {
        if (sourceString[i] != '.') {
            buf[cnt++] = sourceString[i];
        }
        if (sourceString[i] == '.' || i == len - 1 || sourceString[i] == '/') {
            buf[cnt] = '\0';
            cnt = 0;
            oct[cnt1++] = atoi(buf);
        }
    }
    ipAddress[0] = oct[0];
    ipAddress[1] = oct[1];
    ipAddress[2] = oct[2];
    ipAddress[3] = oct[3];
    ipAddress[4] = oct[4];
}
int main() {
    unsigned char ip[20] = {0};
    short ipAddress[5];
    short ipAddress1[4];
    short ipAddress2[4];
    short ipAddress3[4];
    short nwprefix, suffix, newnwprefix;
    short initaddr[4];
    int mask;
    int ntk[32];
    int subs, sizeofblock, remaining, addr;
    printf("Enter a Classless IP Block: ");
    scanf("%s", ip);
    printf("Enter number of subnets: ");
    scanf("%d", & subs);
    extractIpAddress(ip, & ipAddress[0]);
    printf("Ip Address: %d. %d. %d. %d / %d\n ",ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3],ipAddress[4]);
    sizeofblock = (int) pow(2, 32 - ipAddress[4]);
    if (ipAddress[3] % sizeofblock == 0) {
        printf("It is a valid CIDR block\n");
    } else {
        printf("It is not a valid CIDR block\n");
        exit(0);
    }
    newnwprefix = ipAddress[4] + (int)(floor(log(subs) / log(2))); 
    printf("Length of new subnet mask=%d\n", newnwprefix); 
    remaining = 32 - newnwprefix; addr = (int) pow(2, remaining); 
    printf("Number of addresses per subnet: %d\n", addr); 
    ipAddress1[0] = (addr - 1 >> 24) & 0xFF; ipAddress1[1] = (addr - 1 >> 16) & 0xFF; 
    ipAddress1[2] = (addr - 1 >> 8) & 0xFF; ipAddress1[3] = addr - 1 & 0xFF; 
    printf("Range of first subnet: %d.%d.%d.%d/%d - %d. %d. %d. %d / %d\n ",
        ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3],newnwprefix,ipAddress[0] + ipAddress1[0], 
        ipAddress[1] + ipAddress1[1], ipAddress[2] + ipAddress1[2], ipAddress[3] + ipAddress1[3], newnwprefix);
    
    ipAddress1[0] = (sizeofblock - 1 >> 24) & 0xFF;
    ipAddress1[1] = (sizeofblock - 1 >> 16) & 0xFF;
    ipAddress1[2] = (sizeofblock - 1 >> 8) & 0xFF;
    ipAddress1[3] = sizeofblock - 1 & 0xFF;
    ipAddress2[0] = ipAddress1[0] + ipAddress[0];
    ipAddress2[1] = ipAddress1[1] + ipAddress[1];
    ipAddress2[2] = ipAddress1[2] + ipAddress[2];
    ipAddress2[3] = ipAddress1[3] + ipAddress[3];
    ipAddress3[0] = (addr - 1 >> 24) & 0xFF;
    ipAddress3[1] = (addr - 1 >> 16) & 0xFF;
    ipAddress3[2] = (addr - 1 >> 8) & 0xFF;
    ipAddress3[3] = addr - 1 & 0xFF;
    
    printf("Range of last subnet: %d.%d.%d.%d/%d - %d.%d.%d.%d/%d", ipAddress2[0] -
        ipAddress3[0], ipAddress2[1] - ipAddress3[1], ipAddress2[2] - ipAddress3[2], ipAddress2[3] -
        ipAddress3[3], newnwprefix, ipAddress2[0], ipAddress2[1], ipAddress2[2], ipAddress2[3], newnwprefix);

}