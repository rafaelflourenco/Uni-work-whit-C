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

int new_array (int *a , int n , int *b)
{
    for( int i = 0 ; i < n-1 ; i++ )
    {
        b[i] = a[i] * a[i+1];
    }
        
    b[n-1] = a[n-1]*a[n-1];
    return n;   
}


int sum_arrays(int *a , int *b , int*c, int n )
{    
    int soma = 0;
    new_array(a , n , b);
    for( int i = 0 ; i < n-1 ; i++)
    {
        c[i]=a[i]+b[i];
        soma += c[i];
    }
    c[n-1] = a[n-1]+b[n-1];
    soma += c[n-1];
    return soma;
}


void teste (void)
{
    int a[1000];
    int b[1000];
    int c[1000];
    int n = ints_get(a);
    int z = sum_arrays(a , b , c , n );
    printf("%d ", z);
    for (int i = 0 ; i < n ; i++)
    {
      if(i < n-1)
        printf("%d ", c[i]);
      else
        printf("%d\n", c[i]);
    }
}

int main()
{
    teste();
    return 0;
}