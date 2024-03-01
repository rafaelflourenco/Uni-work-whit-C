#include <stdio.h>
#include <math.h>
#include <assert.h>

const char *author = "Rafael Lourenço";

int ints_get(int *a)
{
    int result = 0;
    int x;
    while (scanf("%d", &x) != EOF)
    {
        a[result++] = x;
	}
    return result;
}

int soma(const int*a, int n)
{
    int resultado = 0;
    for(int i = 0; i < n; i++)
    {
        resultado += a[i];
    }
    return resultado;
}

int impar(const int *a, int n)
{
    int resultado1 = 0;
    for(int x = 0; n > x; x++)
    {   
        if( x % 2 != 0)
        {
            resultado1 += a[x];
        }
    }
    return resultado1;
}

int sum_positions_minus_odd_positions(const int*a, int n)
{
    return soma(a, n) - impar(a, n);
}


void teste_assert(void)
{
	int a[8] = {1,2,3,4,5,6,7,8};
    assert(sum_positions_minus_odd_positions(a, 8) == 16);
    int b[5] = {1, 3, 5, 7, 9};
    assert(sum_positions_minus_odd_positions(b, 5) == 15);
	int c[1] = {2};
   	assert(sum_positions_minus_odd_positions(c, 1) == 2);
    int d[3] = {10, 10, 10};
    assert(sum_positions_minus_odd_positions(d, 3) == 20);
}



void teste(void)
{
    int a[1000];
    int n = ints_get(a);
    printf("%d\n", sum_positions_minus_odd_positions(a, n));
}

int main(void)
{
    teste_assert();
	teste();
	return 0;
}