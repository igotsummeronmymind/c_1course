#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int pow_10(int n);
int pow_2(int n);
int encoding_value(char *a);
int register_binary(char a);

int register_binary(char a)
{
    switch (a)
    {
    case 'A':
        return 0;
        break;
    case 'B':
        return 1;
        break;
    case 'C':
        return 10;
        break;
    case 'D':
        return 11;
        break;
    default:
        return 666;
    }
}

int pow_10(int n)
{
    int p = 1;
    if (n==0)
    {
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        p *= 10;
    }
    return p;
}

int pow_2(int n)
{
    int p = 1;
    if (n==0)
    {
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        p *= 2;
    }
    return p;
}

int encoding_value(char *a)
{
    unsigned u;
    int sum = 0;
    if (a[0] == 77 && a[1] == 79) // MOVI Imm
    {
        int i = 5, k = 0;
        while (a[i]!=0) // define the number of digits Imm
        {
            i++;
            k++;
        }
        i=4+k;
        while (i!=4)
        {
            sum += (a[i] - 48)*pow_10(4+k-i);
            i--;
        }
        assert(sizeof(int) == sizeof(unsigned));
        memcpy(&u, &sum, sizeof(int));
        return u;
    }
    else if (a[0] == 65 && a[1] == 68) // ADD R, R
    {
        int x, y;
        int encoding_binary[8]={1, 0, 0, 0, 0, 0, 0, 0};
        x = register_binary(a[4]);
        y = register_binary(a[7]);
        encoding_binary[4] = x / 10;
        encoding_binary[5] = x % 10;
        encoding_binary[6] = y / 10;
        encoding_binary[7] = y % 10;
        for (int i = 7; i >=0; --i)
        {
            sum += encoding_binary[i]*pow_2(7-i);
        }
        assert(sizeof(int) == sizeof(unsigned));
        memcpy(&u, &sum, sizeof(int));
        return u;
    }
    else if (a[0]==83 && a[1]==85) // SUB R, R
    {
        int x, y;
        int encoding_binary[8]={1, 0, 0, 1, 0, 0, 0, 0};
        x = register_binary(a[4]);
        y = register_binary(a[7]);
        encoding_binary[4] = x / 10;
        encoding_binary[5] = x % 10;
        encoding_binary[6] = y / 10;
        encoding_binary[7] = y % 10;
        for (int i = 7; i >=0; --i)
        {
            sum += encoding_binary[i]*pow_2(7-i);
        }
        assert(sizeof(int) == sizeof(unsigned));
        memcpy(&u, &sum, sizeof(int));
        return u;
    }
    else if (a[0]==77 && a[1]==85) // MUL R, R
    {
        int x, y;
        int encoding_binary[8]={1, 0, 1, 0, 0, 0, 0, 0};
        x = register_binary(a[4]);
        y = register_binary(a[7]);
        encoding_binary[4] = x / 10;
        encoding_binary[5] = x % 10;
        encoding_binary[6] = y / 10;
        encoding_binary[7] = y % 10;
        for (int i = 7; i >=0; --i)
        {
            sum += encoding_binary[i]*pow_2(7-i);
        }
        assert(sizeof(int) == sizeof(unsigned));
        memcpy(&u, &sum, sizeof(int));
        return u;
    }
    else if (a[0]==68 && a[1]==73) // DIV R, R
    {
        int x, y;
        int encoding_binary[8]={1, 0, 1, 1, 0, 0, 0, 0};
        x = register_binary(a[4]);
        y = register_binary(a[7]);
        encoding_binary[4] = x / 10;
        encoding_binary[5] = x % 10;
        encoding_binary[6] = y / 10;
        encoding_binary[7] = y % 10;
        for (int i = 7; i >=0; --i)
        {
            sum += encoding_binary[i]*pow_2(7-i);
        }
        assert(sizeof(int) == sizeof(unsigned));
        memcpy(&u, &sum, sizeof(int));
        return u;
    }
    else if (a[0]==73 && a[1]==78) // IN R
    {
        int x;
        int encoding_binary[8]={1, 1, 0, 0, 0, 0, 0, 0};
        x = register_binary(a[3]);
        encoding_binary[6] = x / 10;
        encoding_binary[7] = x % 10;
        for (int i = 7; i >=0; --i)
        {
            sum += encoding_binary[i]*pow_2(7-i);
        }
        assert(sizeof(int) == sizeof(unsigned));
        memcpy(&u, &sum, sizeof(int));
        return u;
    }
    else if (a[0]==79 && a[1]==85) // OUT R
    {
        int x;
        int encoding_binary[8]={1, 1, 0, 0, 0, 1, 0, 0};
        x = register_binary(a[4]);
        encoding_binary[6] = x / 10;
        encoding_binary[7] = x % 10;
        for (int i = 7; i >=0; --i)
        {
            sum += encoding_binary[i]*pow_2(7-i);
        }
        assert(sizeof(int) == sizeof(unsigned));
        memcpy(&u, &sum, sizeof(int));
        return u;
    }
    return 0;
}

int main()
{
    char str[100000];
    char mnemonic[8];
    int i=0;
    fscanf(stdin, "%[^\n]s", mnemonic);
    printf("0x""%x ", encoding_value(mnemonic));
    while (scanf("%c", str)==1)
    {
        for (i = 0; i < 8; ++i)
        {
            mnemonic[i] = 0;
        }
        fscanf(stdin, "%[^\n]s", mnemonic);
        if (encoding_value(mnemonic)!=0)
        {
            printf("0x""%x ", encoding_value(mnemonic));
        }
    }
    return 0;
}
