#include <stdio.h>
#include <assert.h>

const char *author = "Rafael Lourenço";


int ints_get(int *a)
{
    int result = 0;
    int x ;
    while(scanf("%d" , &x) !=EOF)
    {
        a[result] = x;
        result++;
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

int ints_argsmax(int *a , int n , int *b)
{
    int result = 0;
    int max = maximo(a , n);
    for(int i = 0 ; i < n ; i++)
    {
        if( max == a[i])
        {
            b[result]= i;
            result++;
        }
    }    
    return result;

}



void teste_assert(void)
{    
    int b[9];
    int a[9] = {7,9,11,2,5,1,11,8,11};
    assert(ints_argsmax(a , 9 ,b) == 3);
    assert(ints_argsmax(a , 7 ,b) == 2);
    assert(ints_argsmax(a , 5 ,b) == 1);
    assert(ints_argsmax(a , 2 ,b) == 1);
}



void  teste(void)
{    
    int b[1000];
    int a[1000];
    int n = ints_get(a);
    int result =  ints_argsmax(a , n , b);
    printf("%d ", result);
    for (int i = 0 ; i < result ; i++)
    {
        if(i < result-1)
            printf("%d ", b[i]);
        else
            printf("%d\n", b[i]);
    }

}

int main()
{
    teste_assert();
    teste();
    return 0;
}