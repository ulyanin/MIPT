#include <iostream>
#include <cstdio>

void readIp(int ip[])
{
    for (int i = 0; i < 3; ++i) {
        scanf("%d.", &ip[i]);
    }
    scanf("%d", &ip[3]);
}

int main()
{
    int ip[4];
    int mask[4];
    readIp(ip);
    readIp(mask);
    for (int i = 0; i < 4; ++i) {
        if (i) {
            printf(".");
        }
        printf("%d", ((~mask[i]) & 0xFF) | ip[i]);
    }
    printf("\n");
}