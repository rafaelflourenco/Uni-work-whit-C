//este operador serve para dizer ao compilador de C, que este ficheiro header so deve ser processado
//se ainda nao sido processado anteriormente
//le-se "se ainda nao tiver sido definido FEITICOS_H, define FEITICOS_H".
//Se o teste falhar (i.e. FEITICOS_H ja foi definido), o compilador salta para o #endif e tudo o que esta
//dentro do #if e ignorado
#ifndef FEITICOS_H
#define FEITICOS_H

//este include tem como objetivo certificar-me de que quando invocarem um malloc, calloc, strdup, free
//aquilo que será invocado serão as funções de memória do leaks_checker que permitem mais tarde
//verificar se têm ou não fugas de memória
#include "leaks_checker.h"

//Definicao do enumerado School
typedef enum school {Enchantment, Necromancy, Divination, Evocation, Abjuration, Transmutation, Illusion, Conjuration, Invalid=-1} School;

/******Tarefa 1 *********/
//Dada uma string, retorna a escola correspondente à string recebida
//caso a string recebida não corresponda a uma das escolas válidas, deve ser 
//retornado a escola inválida (-1)
School string_2_school(char *s);

//Dada uma escola, retorna uma String correspondente à escola
//Se o valor correspondente ao enumerado recebido não for válido,
//deve ser retornado o ponteiro NULL
const char * school_2_string(School t);

//Define o Tipo Estruturado Feitico, e os seus membros
//para os mais distraidos, existe um membro novo (casting time),
//que corresponde a uma cadeia de caracteres que é guardada como
//um ponteiro
typedef struct S_Feitico {
	char name[100];
	char *casting_time;
	School school;
	int level;
	int range;
	int duration;
	int concentration;
} Feitico;

/******Tarefa 2 *********/
//Construtor do tipo Feitico, recebe os membros, e cria um novo feitico f, e inicializa-o. Devolve
//um ponteiro para o Feitico criado. Se algum dos argumentos recebidos não for válido, o Feitiço não
//deve ser criado, e é retornado o ponteiro NULL.
Feitico *create_feitico(char *name, char *casting_time, char *school, int lvl, int range, int duration, int concentration);


/******Tarefa 3 *********/
//Dado um vetor de ponteiros para feitiços, e um numero n de feitiços a ler, lê do standard input os n feiticos.
//Caso algum dos feitiços lidos tenha informação inválida, deverá ser impresso no ecrã: "Invalid Spell: <nome do feitiço>\n",
//e a função deverá continuar a leitura do próximo feitiço.
//A função retorna o numero de feiticos válidos efetivamente lidos.
int read_feiticos(Feitico *feiticos[], int n);


/******Tarefa 4 *********/
//Imprime um Feitico para o standard input, de acordo com o formato especificado no enunciado.
void println_feitico(Feitico *f);

//Recebe um vetor de ponteiros para feiticos, e o numero de elementos no vetor n, e imprime
//todos os Feiticos, pela ordem em que aparecem no vetor. Caso nao existam elementos no vetor
//imprime "No Spells!\n"
void println_feiticos(Feitico *feiticos[], int n);


/******Tarefa 5 *********/
//Dado um vetor de ponteiros para feiticos, um numero n de feiticos, uma string com o nome de um feitiço, 
//esta funcao procura no vetor feiticos pelo primeiro feitico com nome igual ao nome recebido,
// e retorna o ponteiro para esse feitico.
//Caso nao exista tal feitico, retorna-se o ponteiro NULL
Feitico *find_feitico(Feitico *feiticos[], int n, char *name);

//Recebe um ponteiro para um feitico, um novo nome para o feitiço, e um novo tempo de lançamento,
//e altera os membros correspondentes do feitico.
void update_feitico(Feitico *f, char *new_name, char *new_casting_time);

/******Tarefa 6 *********/
//dado um vetor de entrada de ponteiros de feiticos in, um vetor de saida de ponteiros de feiticos out,
//um inteiro n que corresponde ao numero de elementos de in, e dois inteiros que correspondem
//a um nível mínimo e máximo, esta funcao procura no vetor in todos
//os feiticos com nível compreendido entre os valores minimo e maximo (inclusive),
//colocando-os no vetor de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int filter_feiticos_lvl(Feitico *in[], Feitico *out[], int n, int min_lvl, int max_lvl);

/******Tarefa 7 *********/
//Recebe um ponteiro para um feitico, e cria uma cópia (ou clone) profunda do feitico. Devolve um
//ponteiro para a cópia criada
Feitico *copy_feitico(Feitico *f);


/******Tarefa 8 *********/
//Recebe um ponteiro para um feitico, e liberta a memória usada pelo tipo.
//Deve libertar toda a memória reservada (direta ou indiretamente) pelo construtor.
void free_feitico(Feitico *f);

//dado um vetor de ponteiros para feiticos, um inteiro n representando o tamanho do vetor,
//e uma string com o nome do feitiço, procura pelo feitiço no vetor, e caso o encontre,
//remove-o do vetor, e apaga o feitiço. O vetor é reorganizado, passando todos os
//elementos à direita do feitiço apagado uma posição para a sua esquerda.
//Retorna o número de elementos no vetor final, depois de apagado o feitiço. Caso o feitiço
//não exista, nada é apagado, e é retornado o mesmo número n recebido.
int delete_feitico(Feitico *feiticos[], int n, char *name);


/******Tarefa 9 *********/
//funcao de teste, a espeficicação detalhada está no enunciado.
void test_F(void);

#endif