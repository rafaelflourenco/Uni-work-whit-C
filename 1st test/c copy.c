#include <stdio.h>
#include <math.h>

const char *author = "Rafael Lourenço";

int ints_get(int *contest)
{
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF)
	{
    contest[result++] = x;
	}
  return result;
}

int pontos_programas(const int *contest, int n)
{
  int resultado_um = 0;
  
  for (int i = (n / 2); i < n; i++)
  {
    resultado_um = resultado_um + contest[i];
  }
  return resultado_um * 3;
}




int bonus(const int*contest, int n)

{
  int resultado = 0;
  for (int i = 0; i < n / 2; i++)
  {
    
    if(contest[i] <= (contest[i + (n / 2)]) * 2)
    {
      resultado++;
    }
  }
  return resultado;
}





void teste(void)
{
int contest[1000];
int n = ints_get(contest);
printf("%d\n", (pontos_programas(contest, n) + bonus(contest, n)));
}

int main(void)
{
	teste();
	return 0;
}