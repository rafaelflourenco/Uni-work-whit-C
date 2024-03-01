#include <stdio.h>
#include <math.h>
const char *author = "Rafael Lourenço";

double const simples = 0.23770;
double const dia = 0.26120;
double const noite = 0.20620;

double bi_hourly(double consumo_dia, double consumo_noite)
{
  double resultado = ((consumo_dia * dia) + (consumo_noite * noite));
  double taxa = (resultado * 1.25) + 18.551;
  double iva = taxa * 1.23;

  return iva;
}


double simple(double consumo_dia, double consumo_noite)
{
  double resultado_um = consumo_dia + consumo_noite;
  double taxa_um = ((resultado_um * simples) * 1.25) + 15.903;
  double iva_um = taxa_um * 1.23;

  return iva_um;
}



void teste(void)
{
    double consumo_dia;
    double consumo_noite;
    while (scanf("%lf%lf", &consumo_dia, &consumo_noite) != EOF)
    {
       printf("%.2f %.2f\n", simple(consumo_dia, consumo_noite), bi_hourly(consumo_dia, consumo_noite));
    }
}


int main(void)
{
  teste();
  return 0;
}