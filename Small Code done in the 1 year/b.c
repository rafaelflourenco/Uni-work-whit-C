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



int ints_all_equal(const int*a, int n)
{
	for(int i = 0; n - 1 > i ; i++)
		if(a[i] != a[i + 1])
			return 0;
	return 1;
}

void teste_assert(void)
{
	int a[8] = {1,2,3,4,5,6,7,8};
    assert(ints_all_equal(a, 8) == 0);
    int b[5] = {1, 3, 5, 7, 9};
    assert(ints_all_equal(b, 5) == 0);
	int c[1] = {2};
   	assert(ints_all_equal(c, 1) == 1);
    int d[3] = {10, 10, 10};
    assert(ints_all_equal(d, 3) == 1);
} 



void teste(void)
{
	int a[1000];
	int n = ints_get(a);
	int z = ints_all_equal(a, n);
	printf("%d\n", z);
}


int main(void)
{
	teste_assert();
	teste();
	return 0;
}