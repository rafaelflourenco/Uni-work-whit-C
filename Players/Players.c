#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#ifndef JOGADOR_H
#define JOGADOR_H

typedef enum e_Posicao 
{
    GR,
    Defesa,
    Medio,
    Avancado
}Posicao;

Posicao string_to_posicao(char *s)
{
	if(strcmp("Guarda-redes", s) == 0)
		return GR;
	else if(strcmp("Defesa", s) == 0)
		return Defesa;
	else if (strcmp( "Medio", s)== 0)
		return Medio;
	else
		return Avancado;
} 

const char * posicao_to_string(Posicao p)
{
	if (p == GR)
		return "Guarda-redes";
	else if(p == Defesa)
		return "Defesa";
	else if (p == Medio)
		return "Medio";
	else
		return "Avancado";
}


typedef struct S_Jogador
{
    char *primeiro_nome;
    char *ultimo_nome;
    char *clube;
    int ano;
    Posicao pos;
    int internacionalizacoes;
    int golos;
} Jogador;


Jogador *jogador(char *primeiro_nome,char *ultimo_nome, int ano, Posicao p, int inter, int golos, char *clube)
{
    Jogador *j = malloc(sizeof(Jogador));
    j->primeiro_nome = strdup(primeiro_nome);
    j->ultimo_nome = strdup(ultimo_nome);
    j->ano = ano;
    j->pos = p;
    j->internacionalizacoes = inter;
    j->golos = golos;
    j->clube = strdup(clube);

    return j;
}

void free_jogador(Jogador *j) 
{
    free(j->primeiro_nome);
    free(j->ultimo_nome);
    free(j->clube);
    free(j); 
}


Jogador *jogador_dup(Jogador *j)
{
	Jogador *copia = malloc(sizeof(Jogador));
	*copia= *j;
	copia->primeiro_nome = strdup(j->primeiro_nome);
	copia->ultimo_nome = strdup(j->ultimo_nome);
	copia->clube = strdup(j->clube);
	return copia;
}


void adiciona_internacionalizacao(Jogador *j, int golos)
{
	j->internacionalizacoes+=1;
	j->golos += golos;
}


void println_jogador(Jogador *j)
{
	printf("[%s][%s][%d][%s][%d][%d][%s]\n" , j->primeiro_nome, j->ultimo_nome, j->ano, posicao_to_string(j->pos), j->internacionalizacoes, j->golos, j->clube);
}


void println_jogadores(Jogador *jogadores[], int n)
{
    if(n == 0)
        printf("*\n");
    else
        for (int i = 0; i < n; i++)
            println_jogador(jogadores[i]);
}



int get_jogadores(Jogador *jogadores[], int n)
{
	int i = 0;
	char primeiro_nome[100];
	char ultimo_nome[100];
	int ano;
	int internacionalizacoes;
	int golos;
	char posicao[100];
	char clube[100];
	while(i < n && scanf("%s %s %d %s %d %d %s", primeiro_nome, ultimo_nome, &ano, posicao, &internacionalizacoes, &golos, clube)!=EOF)
	{
		jogadores[i] = jogador(primeiro_nome, ultimo_nome, ano, string_to_posicao(posicao),internacionalizacoes, golos, clube);
		i++;
	}
	return i;
}


int get_jogadores_from_file(FILE *f, Jogador *jogadores[], int n) 
{
        char primeiro_nome[100], ultimo_nome[100], posicao[100], clube[100];
        int ano, internacionalizacoes, golos;
        Posicao pos;
        int i = 0;
        while (i < n && fscanf(f, "%s\t%s\t%d\t%s\t%d\t%d\t%[^\n]\n", primeiro_nome, ultimo_nome, &ano, posicao, &internacionalizacoes, &golos, clube)!= EOF)
        {
            pos = string_to_posicao(posicao);
            jogadores[i++] = jogador(primeiro_nome,ultimo_nome,ano,pos,internacionalizacoes,golos,clube);
        }
        return i;
}

Jogador *pesquisa_jogador(Jogador *jogadores[], int n, char *primeiro_nome, char *ultimo_nome)
{
	for(int i = 0 ; i < n ; i++)
		if(strcmp(jogadores[i]->primeiro_nome, primeiro_nome) == 0 && strcmp(jogadores[i]->ultimo_nome , ultimo_nome) == 0)
			return jogadores[i];
	return NULL;
}


Jogador *pesquisa_melhor_marcador(Jogador *jogadores[], int n)
{   
    if (n == 0)
        return NULL;
    Jogador* melhor_marcador = jogadores[0];
    for(int i = 1; i < n ; i++)
    {
        if(jogadores[i]->golos > melhor_marcador->golos)
            melhor_marcador = jogadores[i];
    }
    return melhor_marcador;
}




int pesquisa_jogadores(Jogador *in[], Jogador *out[], int n, int (*p) (Jogador*))
{
    int count = 0;
    for (int i = 0; i < n; i++) 
    {
        if (p(in[i]) == 1) 
        {
            out[count] = in[i];
            count++;
        }
    }
    return count;
}

int avancado_e_golos20menos(Jogador *j) 
{
    return (j->pos == Avancado) && (j->golos < 20);
}

int cmp_jogadores(const void *a, const void *b) 
{
    Jogador *ja = *(Jogador **)a;
    Jogador *jb = *(Jogador **)b;

    if (ja->internacionalizacoes > jb->internacionalizacoes)
        return -1;
    else if (ja->internacionalizacoes < jb->internacionalizacoes)
        return 1;
    else         
        return ja->golos > jb->golos ? -1 : 1;
}

int pesquisa_jogadores_clube(Jogador *in[], Jogador *out[], int n, char* clube)
{
	int contador = 0;
	for(int i = 0 ; i < n ; i++)
	{
		if (strcmp(in[i]->clube, clube) == 0)
		{
			out[contador] = in[i];
			contador++;
		}

	}
	return contador;
}

int pesquisa_jogadores_inter(Jogador *in[], Jogador *out[], int n, int min_inter, int max_inter)
{
	int contador = 0;
	for(int i = 0 ; i < n ; i++)
	{
		if(min_inter <= in[i]->internacionalizacoes && in[i]->internacionalizacoes <= max_inter)
		{
			out[contador] = in[i];
			contador++;
		}
	}
	return contador;
}


void test_Jogador_File_Loading(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    int n = 0;
    fscanf(f, "%d", &n);
    fgetc(f);
    
    Jogador *j[n];
    n = get_jogadores_from_file(f, j, n);
    fclose(f);

    char primeiro_nome[100];
    char ultimo_nome[100];
    int golos;
    char clube[100];
    char caminho;
    while(scanf("\n%c", &caminho)!=EOF)
    {
        if(caminho == '+')
        {  
            scanf("%s %s %d", primeiro_nome ,ultimo_nome, &golos);
            if (pesquisa_jogador(j,n,primeiro_nome,ultimo_nome) == NULL)
                printf("Not found!\n");
            else
            {
                adiciona_internacionalizacao(pesquisa_jogador(j,n,primeiro_nome,ultimo_nome), golos);
                println_jogador(pesquisa_jogador(j,n,primeiro_nome,ultimo_nome));
            }
        }
        else if(caminho == '?')
        {
            scanf("%s", clube);
            Jogador *b[n * sizeof(Jogador *)];
            int verdadeiro = pesquisa_jogadores_clube(j,b,n,clube);
            if(verdadeiro > 0)
            {
                for (int i = 0; i < verdadeiro; i++)
                    println_jogador(b[i]);                  
            }
            else
                printf("*\n");
            }
    }
}

void test_Jogador_Sorting(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    int n = 0;
    fscanf(f, "%d", &n);
    fgetc(f);

    Jogador *jogadores[n];
    int n_jogadores = get_jogadores_from_file(f, jogadores, n);
    fclose(f);

    qsort(jogadores, n_jogadores, sizeof(Jogador *), cmp_jogadores);
    println_jogadores(jogadores, n_jogadores);
}

void test_Jogador_Pesquisa(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    int n = 0;
    fscanf(f, "%d", &n);
    fgetc(f);

    Jogador *jogadores[n];
    int n_jogadores = get_jogadores_from_file(f, jogadores, n);
    fclose(f);

    Jogador *jogadores_out[100];
    int num_jogadores_out = pesquisa_jogadores(jogadores, jogadores_out, n_jogadores, avancado_e_golos20menos);

    println_jogadores(jogadores_out, num_jogadores_out);
}

#endif


   char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    Submissao *s[1000];
    int n = get_submissoes_from_file(f, s);

    ch
    
    
    
    int main(void)
{
    teste_leitura_simples();
    return 0;
}


void teste_estatisticas(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    Submissao *s[1000];
    int n = get_submissoes_from_file(f, s);
    char scan[30];
    char comando[30];
    int total_sumbissions = 0;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    int n6 = 0;
    int n7 = 0;
    int n8 = 0;
    while(scanf("%s %s", scan, comando) != EOF)
    {
        for(int i = 0; i < n; i++)
        {   
            if(strcmp(s[i]->problema, comando) == 0)
            {
                total_sumbissions++;
                if
            }
            if(strcmp(s[i]->resultado, "Accepted") == 0 && strcmp(s[i]->problema, comando) == 0)
            {  
                n1++;
            }
            if(strcmp(s[i]->resultado, "Presentation Error") == 0 && strcmp(s[i]->problema, comando) == 0)
            {
                n2++;
            }
            if(strcmp(s[i]->resultado, "Wrong Answer") == 0 && strcmp(s[i]->problema, comando) == 0)
            {
                n3++;
            }
            if(strcmp(s[i]->resultado, "Memory Limit Exceeded") == 0 && strcmp(s[i]->problema, comando) == 0)
            {
                n4++;
            }
            if(strcmp(s[i]->resultado, "Time Limit Exceeded") == 0 && strcmp(s[i]->problema, comando) == 0)
            {
                n5++;
            }
            if(strcmp(s[i]->resultado, "Run Time Error") == 0 && strcmp(s[i]->problema, comando) == 0)
            {
                n6++;
            }
            if(strcmp(s[i]->resultado, "Compile Time Error") == 0 && strcmp(s[i]->problema, comando) == 0)
            {
                n7++;
            }
            else if(strcmp(s[i]->problema, comando) == 0)
            {
                n8++;
            }
            
        }
    printf("Problem: %s\n", comando);
    printf("Total Submissions: %d\n", total_sumbissions);
    printf("Accepted: %d\n", n1);
    printf("Presentation Error: %d\n", n2);
    printf("Wrong Answer: %d\n", n3);
    printf("Memory Limit Exceeded: %d\n", n4);
    printf("Time Limit Exceeded: %d\n", n5);
    printf("Run Time Error: %d\n", n6);
    printf("Compile Time Error: %d\n", n7);
    printf("Other Errors: %d\n", n8);        
    } 
}

/*void teste_estatisticas(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    Submissao *s[1000];
    int n = get_submissoes_from_file(f, s);
    char scan[30];
    char comando[30];
    int total_sumbissions = 0;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    int n6 = 0;
    int n7 = 0;
    int n8 = 0;
    while(scanf("%s %s", scan, comando) != EOF)
    {
        for(int i = 0; i < n; i++)
        {   
            if(strcmp(s[i]->problema, comando) == 0)
            {
                total_sumbissions++;
                if(strcmp(s[i]->resultado, "Accepted") == 0)
                {
                    n1++;
                }
                if(strcmp(s[i]->resultado, "Presentation Error") == 0)
                {
                    n2++;
                }
                if(strcmp(s[i]->resultado, "Wrong Answer") == 0)
                {
                    n3++;
                }
                if(strcmp(s[i]->resultado, "Wrong Answer") == 0)
                {
                    n4++;
                }
                if(strcmp(s[i]->resultado, "Time Limit Exceeded") == 0)
                {
                    n5++;
                }
                if(strcmp(s[i]->resultado, "Run Time Error") == 0)
                {
                    n6++;
                }
                if(strcmp(s[i]->resultado, "Compile Time Error") == 0)
                {
                    n7++;
                }
                else if(strcmp(s[i]->problema, comando) == 0)
                {
                    n8++;
                }
            }
           

        

            
        }
    printf("Problem: %s\n", comando);
    printf("Total Submissions: %d\n", total_sumbissions);
    printf("Accepted: %d\n", n1);
    printf("Presentation Error: %d\n", n2);
    printf("Wrong Answer: %d\n", n3);
    printf("Memory Limit Exceeded: %d\n", n4);
    printf("Time Limit Exceeded: %d\n", n5);
    printf("Run Time Error: %d\n", n6);
    printf("Compile Time Error: %d\n", n7);
    printf("Other Errors: %d\n", n8);        
    } 
}*/