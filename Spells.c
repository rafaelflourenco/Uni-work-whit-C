#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum Escola_{
    Enchantment,
    Necromancy,
    Divination,
    Evocation,
    Abjuration,
    Transmutation,
    Illusion,
    Conjuration
} Escola;

typedef struct Feitico_{
    char *nome; 
    int nivel;      
    Escola escola;  
    int alcance;    
    int duracao;    
    int concentracao; 
} Feitico;

const char *escolaToString(Escola e){
    if(e == Enchantment) return "Enchantment";
    else if(e == Necromancy) return "Necromancy";
    else if (e == Divination) return "Divination";
    else if (e == Evocation) return "Evocation";
    else if (e == Abjuration) return "Abjuration";
    else if (e == Transmutation) return "Transmutation";
    else if (e == Illusion) return "Illusion";
    else return "Conjuration";   
}

Escola stringToEscola(char* c){
    if(strcmp("Enchantment", c) == 0) return Enchantment;
    else if(strcmp("Necromancy", c) == 0) return Necromancy;
    else if(strcmp("Divination", c) == 0) return Divination;
    else if(strcmp("Evocation", c) == 0) return Evocation;
    else if(strcmp("Abjuration", c) == 0) return Abjuration;
    else if(strcmp("Transmutation", c) == 0) return Transmutation;
    else if(strcmp("Illusion", c) == 0) return Illusion;
    else return Conjuration;
}

Feitico criarFeitico(char *nome, int nivel, Escola escola, int alcance, int duracao, int concentracao) {
    Feitico novoFeitico;
    novoFeitico.nome = strdup(nome);
    novoFeitico.nivel = nivel;
    novoFeitico.escola = escola;
    novoFeitico.alcance = alcance;
    novoFeitico.duracao = duracao;
    novoFeitico.concentracao = concentracao;

    return novoFeitico;
}
void feiticos_to_feiticos_ptr2(Feitico in[], Feitico *out[], int n) {
    for (int i = 0; i < n; i++) {
        out[i] = &in[i];
    }
}

void printFeitico(Feitico *f) {
    printf("------------------------------\n");
    printf("%s\n", f -> nome);
    printf("Level: %d, %s\n", f ->nivel, escolaToString(f -> escola));
    printf("Range: %d feet\n", f-> alcance);
    if(f->concentracao == 1){
        if (f->duracao == 0) {
        printf("Duration: Instantaneous (Concentration)\n");
        } else if (f->duracao >= 1 && f->duracao <= 10) {
        printf("Duration: %d rounds (Concentration)\n", f->duracao);
        } else if (f->duracao >= 11 && f->duracao <= 599) {
        printf("Duration: %d minutes (Concentration)\n", f->duracao / 10);
        } else if (f->duracao >= 600) {
        printf("Duration: %d hours (Concentration)\n", f->duracao / 600);
        }
    }
    else if(f->concentracao == 0){
        if (f->duracao == 0) {
        printf("Duration: Instantaneous\n");
        } else if (f->duracao >= 1 && f->duracao <= 10) {
        printf("Duration: %d rounds\n", f->duracao);
        } else if (f->duracao >= 11 && f->duracao <= 599) {
        printf("Duration: %d minutes\n", f->duracao / 10);
        } else if (f->duracao >= 600) {
        printf("Duration: %d hours\n", f->duracao / 600);
        }
    }

}
Feitico *pesquisa_feitico(Feitico *in[], int n, char *nome){
    for(int i = 0; i < n; i++){
        if(strcmp(in[i]->nome,nome) == 0) return in[i];
    }
    return NULL;
}

void atualiza_feitico(Feitico *f, int novoAlcance){
    if(novoAlcance >= 0){
        f->alcance = novoAlcance;
    }
}

int read_feiticos(Feitico *f, int n){
    char nome[100];
    int nivel;
    char escola[100];
    int alcance;
    int duracao;
    int concentracao;
    int i = 0;
    while(i < n && scanf("%s\n%d\n%s\n%d\n%d\n%d\n", nome, &nivel, escola, &alcance, &duracao, &concentracao)!=EOF)
    {
        f[i] = criarFeitico(nome,nivel,stringToEscola(escola),alcance,duracao,concentracao);
        i++;
    }

    return i;
}

void teste(){
    int numeroFeiticos;
    scanf("%d", &numeroFeiticos);
    char updateLido[20];
    char nomeLido[100];
    int alcanceLido;
    Feitico feiticosLidos[numeroFeiticos];
    int numFeiticosLidos = read_feiticos(feiticosLidos, numeroFeiticos);
    Feitico *pointerParaFeiticosLidos[numeroFeiticos];
    feiticos_to_feiticos_ptr2(feiticosLidos, pointerParaFeiticosLidos, numFeiticosLidos);

    while (scanf("%s %s %d", updateLido, nomeLido, &alcanceLido) != EOF) {
        if(strcmp(updateLido,"UPDATE")== 0)
        {
            Feitico *feiticosEncontrados = pesquisa_feitico(pointerParaFeiticosLidos, numFeiticosLidos, nomeLido);
            if(feiticosEncontrados == NULL) 
                printf("No such spell exists!\n");
            else {
                atualiza_feitico(feiticosEncontrados, alcanceLido);
                printFeitico(feiticosEncontrados);
            }
        }
    }
}

int main()
{
    teste();
    return 0;
}



