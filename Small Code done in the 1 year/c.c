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


int maximo (const int *a, int n)
{
	int resultado = 0;
	for (int i=0; i<n; i++)
	{
		if (a[i] >= resultado)
		{
			resultado = a[i];
		}
	}
    
	return resultado;
}

int ints_remove (const int*a, int n, int*b)
{
    int result = 0;
    for (int i = 0; i < n; i++) 
    {
        if (a[i] != maximo(a, n)) 
        {
            b[result++] = a[i]; 
        }
    }
    
    return result;
}


int maximo_um (const int *a, int n)
{
  int b[1000];
  int k = ints_remove(a, n, b);
  int resultado = 0;
    for (int i=0; i<k; i++)
    {
        if (b[i] >= resultado)
        {
            resultado = b[i];
        }
    }
    return resultado;
}


void teste_assert(void)
{
  int a[8] = {1,2,3,4,5,6,7,8};
  assert(maximo_um(a, 8) == 7);
  int b[5] = {1, 3, 5, 7, 9};
  assert(maximo_um(b, 5) == 7);
  int c[2] = {2, 3};
  assert(maximo_um(c, 2) == 2);
  int d[3] = {10, 10, 20};
  assert(maximo_um(d, 3) == 10);
}

void teste(void)
{
  int a[1000];
  int n = ints_get(a);
  int z = maximo_um(a, n);
  printf("%d\n", z);
}

int main(void)
{
  teste_assert();
  teste();
  return 0;
}
