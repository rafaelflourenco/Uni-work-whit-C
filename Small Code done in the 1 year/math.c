#include <math.h>
#include <stdio.h>

const char *author = "Rafael Lourenço";

double arredondar(double x) 
{ 
  return (round(x * 100)) / 100; 
}

double compras15(double x, int y, int z) 
{
  return z == 0 ? y * (x - (x * 0.15) - (x * 0.1)) : (y * (x - (x * 0.15) - (x * 0.1)) + z * (x - (x * 0.15)));
}

double promos(double x, int y, int z) 
{
  double a = 0;
  int b = floor((y + z) / 3);
  if (y >= b && b != 0) 
  {
    a =  b * (x - (x * 0.15) - (x * 0.1));
  }
  if (y < b && b != 0)
  {
    a = ((b - y) * (x - (x * 0.15))) + (y * (x - (x * 0.15) - (x * 0.1)));
  }
  return a;
}

void teste(void) 
{
  double x;
  int y;
  int z;
  while (scanf("%lf%d%d", &x, &y, &z) != EOF) 
  {  
    double h = arredondar(((compras15(x, y, z) - promos(x, y, z)) / (y + z)));
    printf("%f\n", h);
  }
}
 
int main(void) 
{
  teste();
  return 0;
}