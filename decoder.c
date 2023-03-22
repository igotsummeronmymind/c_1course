#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int translate(char n);
char register_def(int n);

int translate(char n)
{
    switch (n) {
    case 'a':
        return 10;
        break;
    case 'b':
        return 11;
        break;
    case 'c':
        return 12;
        break;
    case 'd':
        return 13;
        break;
    case 'e':
        return 14;
        break;
    case 'f':
        return 15;
        break;
    default:
        return n - '0';
    }
}

char register_def(int n)
{
    n = n % 4;
    switch (n) {
    case 0:
        return 'A';
        break;
    case 1:
        return 'B';
        break;
    case 2:
        return 'C';
        break;
    case 3:
        return 'D';
        break;
    }
    return 0;
}

int main()
{
    char str[100000];
    int encoding[8];
    int x = 0, y = 0, j = 0, res_binary = 0, res_decimal = 0, save = 0;
    fscanf(stdin, "%[^\n]s", str);
    for (int i = 2; i < strlen(str) + 1; i = i + 5)     //0x60 0x66 
    {
        for (int i = 0; i < 8; i++) {
            encoding[i] = 0;
        }
        j = 3;
        x = translate(str[i]);
        if (str[i + 1] == ' ') {
            x = 0;
            i--;
        }
        while (x > 0) {
            encoding[j] = x % 2;
            j--;
            x = x / 2;
        }
        j = 7;
        y = translate(str[i + 1]);
        while (y > 0) {
            encoding[j] = y % 2;
            j--;
            y = y / 2;
        }
        for (int i = 0; i < 8; i++) {
            res_binary = res_binary * 2 + encoding[i];
        }
        for (int i = 0; i < 8; i++) {
            res_decimal = res_decimal * 10 + encoding[i];
        }
        if (res_decimal / 10000000 == 0) {
            printf("MOVI %d\n", res_binary);
        } else
            switch (res_decimal / 10000) {
            case 1000:
                printf("ADD %c, %c\n", register_def(res_binary / 4),
                       register_def(res_binary));
                break;
            case 1001:
                printf("SUB %c, %c\n", register_def(res_binary / 4),
                       register_def(res_binary));
                break;
            case 1010:
                printf("MUL %c, %c\n", register_def(res_binary / 4),
                       register_def(res_binary));
                break;
            case 1011:
                printf("DIV %c, %c\n", register_def(res_binary / 4),
                       register_def(res_binary));
                break;
            default:
                break;
            }
        if (res_decimal / 100 == 110000) {
            printf("IN %c\n", register_def(res_binary));
        }
        if (res_decimal / 100 == 110001) {
            printf("OUT %c\n", register_def(res_binary));
        }
        if (res_binary >= 200) {
            printf("ERROR");
            break;
        }
        res_binary = 0;
        res_decimal = 0;
    }
    return 0;
}

