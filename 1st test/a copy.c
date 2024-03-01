#include <stdio.h>
#include <math.h>
const char *author = "Rafael Lourenço";



double distancia(double latitude_origem, double longitude_origem) 
{
  return sqrt(pow((38.72 - latitude_origem), 2) + pow((9.14 - longitude_origem), 2)) * 100;
}

double tempo(double latitude_origem, double longitude_origem)
{
  if((distancia(latitude_origem, longitude_origem)) <= 1000)
  {
    return (distancia(latitude_origem, longitude_origem) * 1.12);
  }
  else if(distancia(latitude_origem, longitude_origem) > 3000)
  {
    return distancia(latitude_origem, longitude_origem) * 1.18;
  }
  else
  {
    return distancia(latitude_origem, longitude_origem) * 0.75;
  }
}






void teste(void)
{
    double latitude_origem;
    double longitude_origem;
    while (scanf("%lf%lf", &latitude_origem, &longitude_origem ) != EOF)
    {  
       if((distancia(latitude_origem, longitude_origem)) <= 1000)
       {
        printf("%.3f VT %.3f\n", distancia(latitude_origem, longitude_origem), tempo(latitude_origem, longitude_origem));
       }
       else if(distancia(latitude_origem, longitude_origem) > 3000)
       {
        printf("%.3f VM %.3f\n", distancia(latitude_origem, longitude_origem), tempo(latitude_origem, longitude_origem));
       }
       else
       {
        printf("%.3f VA %.3f\n", distancia(latitude_origem, longitude_origem), tempo(latitude_origem, longitude_origem));
       }
    }
}

int main(void)
{
  teste();
  return 0;
}