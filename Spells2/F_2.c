#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "feiticos.h"


//este include tem como objetivo certificar-me de que quando invocarem um malloc, calloc, strdup, free
//aquilo que será invocado serão as funções de memória do leaks_checker que permitem mais tarde
//verificar se têm ou não fugas de memória




const char *escolaToString(School e){
    if(e == Enchantment) return "Enchantment";
    else if(e == Necromancy) return "Necromancy";
    else if (e == Divination) return "Divination";
    else if (e == Evocation) return "Evocation";
    else if (e == Abjuration) return "Abjuration";
    else if (e == Transmutation) return "Transmutation";
    else if (e == Illusion) return "Illusion";
    else if (e== Conjuration) return "Conjuration";
    else return "-1";  
}

School stringToEscola(char* c){
    if(strcmp("Enchantment", c) == 0) return Enchantment;
    else if(strcmp("Necromancy", c) == 0) return Necromancy;
    else if(strcmp("Divination", c) == 0) return Divination;
    else if(strcmp("Evocation", c) == 0) return Evocation;
    else if(strcmp("Abjuration", c) == 0) return Abjuration;
    else if(strcmp("Transmutation", c) == 0) return Transmutation;
    else if(strcmp("Illusion", c) == 0) return Illusion;
    else if(strcmp("Conjuration",c) == 0) return Conjuration;
    else return Invalid;
}


Feitico *create_feitico(char *name, char *casting_time, char *school, int lvl, int range, int duration, int concentration) {
    
    if (name == NULL || casting_time == NULL || lvl < 0 || lvl > 9 || stringToEscola(school)==Invalid || range < 0 || duration < 0 || (concentration != 0 && concentration != 1)) {
        return NULL;
    }
    Feitico *novoFeitico = malloc(sizeof(Feitico));
    strcpy(novoFeitico->name,name);
    novoFeitico->casting_time = strdup(casting_time);
    novoFeitico->level = lvl;
    novoFeitico->school = stringToEscola(school);
    novoFeitico->range = range;
    novoFeitico->duration = duration;
    novoFeitico->concentration = concentration;
    

    return novoFeitico;
}



void println_feitico(Feitico *f) {
    printf("------------------------------\n");
    printf("%s\n", f -> name);
    printf("Level: %d, %s\n", f ->level, escolaToString(f -> school));
    printf("Casting Time: %s\n", f->casting_time);
    printf("Range: %d feet\n", f-> range);

    if(f->concentration == 1){
        if (f->duration == 0) {
        printf("Duration: Instantaneous (Concentration)\n");
        } else if (f->duration >= 1 && f->duration <= 10) {
        printf("Duration: %d rounds (Concentration)\n", f->duration);
        } else if (f->duration >= 11 && f-> duration <= 599) {
        printf("Duration: %d minutes (Concentration)\n", f->duration / 10);
        } else if (f->duration >= 600) {
        printf("Duration: %d hours (Concentration)\n", f->duration / 600);
        }
    }
    else if(f->concentration == 0){
        if (f->duration == 0) {
        printf("Duration: Instantaneous\n");
        } else if (f->duration >= 1 && f->duration <= 10) {
        printf("Duration: %d rounds\n", f->duration);
        } else if (f->duration >= 11 && f->duration <= 599) {
        printf("Duration: %d minutes\n", f->duration / 10);
        } else if (f->duration >= 600) {
        printf("Duration: %d hours\n", f->duration / 600);
        }
    }

}

void println_feiticos(Feitico *f[], int n){
    for(int i = 0; i < n; i++){
        println_feitico(f[i]);
    }
}

Feitico *find_feitico(Feitico *in[], int n, char *nome){

    for(int i = 0; i < n; i++){
        if(strcmp(in[i]->name,nome) == 0) return in[i];
    }
    return NULL;
}


void update_feitico(Feitico *f, char *new_name, char *new_casting_time){
    strcpy(f->name,new_name);
    free(f->casting_time);
    f->casting_time = strdup(new_casting_time);

}

int filter_feiticos_lvl(Feitico *in[], Feitico *out[], int n, int min_lvl, int max_lvl){
    int count = 0;
    for(int i = 0; i < n ; i++){
        if(in[i]->level >= min_lvl && in[i]->level <= max_lvl)
        {
            out[count] = copy_feitico(in[i]);
            count++;
        }
    }
    return count;
}
 
Feitico *copy_feitico(Feitico *f){
    Feitico *copia = malloc(sizeof(Feitico));
    *copia = *f;
    strcpy(copia->name,f->name);
    copia->casting_time = strdup(f->casting_time);
    copia->level = f->level;
    copia->school = f->school;
    copia->range = f->range;
    copia->duration = f->duration;
    copia->concentration = f->concentration;
    return copia;

}

void free_feitico(Feitico *f){
   
    free(f->casting_time);
    free(f);
}

int delete_feitico(Feitico *feiticos[], int n, char *name) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(feiticos[i]->name, name) == 0) {
            found++;
            free_feitico(feiticos[i]); 
            for(int j = i; j < n -1 ;j++)
            {
                  feiticos[j] = feiticos[j + 1];

            } 
        }
    }
    
    return n-found; 
}


int read_feiticos(Feitico *f[], int n){
    char nome[100];
    char castTime[100];
    int nivel;
    char escola[100];
    int alcance;
    int duracao;
    int concentracao;
    int i = 0;
    char invalidos[n][100];
    int found = 0;
    int count = 0;
    while (i < n && scanf("%s %d %s %s %d %d %d", nome, &nivel, escola, castTime, &alcance, &duracao, &concentracao) == 7)
    {
        Feitico *new_feitico[n];
        new_feitico[i] = create_feitico(nome, castTime, escola, nivel, alcance, duracao, concentracao);
        
        if (new_feitico[i] == NULL) {
            strcpy(invalidos[found], nome);
            found++;
            
        } else {
            
            f[count] = copy_feitico(new_feitico[i]); 
            count++;
            free_feitico(new_feitico[i]);
        }
        
        i++;
    }
    
    for (int j = 0; j < found; j++) {
        printf("Invalid Spell: %s\n", invalidos[j]);
    }
    
    return count; 
}


void test_F(){
    int numeroFeiticos;
    scanf("%d", &numeroFeiticos);
    Feitico *feiticosLidos[numeroFeiticos];
    numeroFeiticos = read_feiticos(feiticosLidos, numeroFeiticos);
    char comando[20];
    while(scanf("%s", comando) != EOF)
    {
        if(strcmp("UPDATE", comando) == 0){
            char nomeLido[100];
            char novoNome[100];
            char novoCasting[50];
            scanf("%s %s %s", nomeLido, novoNome, novoCasting);
            Feitico *encontrado = find_feitico(feiticosLidos,numeroFeiticos,nomeLido);
            if(encontrado == NULL)
            {
                printf("No such spell exists!\n");
            }
            else{
                update_feitico(encontrado,novoNome,novoCasting);
                println_feitico(encontrado);
            }
            
        }
        else if (strcmp("DELETE",comando)==0){
            char nomeLido[100];
            scanf("%s", nomeLido);
            
            Feitico *encontrado = find_feitico(feiticosLidos,numeroFeiticos,nomeLido);
            if(encontrado == NULL){
                printf("No such spell exists!\n");
            }
            else {
                numeroFeiticos = delete_feitico(feiticosLidos,numeroFeiticos,nomeLido);
                printf("Spell deleted.\n");
            }
        }
        else if (strcmp("FILTER",comando)== 0){
            char lvl[3];
            int min_level;
            int max_level;
            scanf("%s %d %d", lvl,&min_level,&max_level);
            Feitico *feiticosNoLimite[numeroFeiticos];
            int encontrados = filter_feiticos_lvl(feiticosLidos,feiticosNoLimite,numeroFeiticos,min_level,max_level);
            if(encontrados == 0) printf("No Spells!\n");
            else {
                println_feiticos(feiticosNoLimite,encontrados);
                for(int i = 0; i < encontrados; i++) {
                    free_feitico(feiticosNoLimite[i]);
                }
            }
        }

    }
    for(int i = 0; i < numeroFeiticos; i++){
        free_feitico(feiticosLidos[i]);
    }
}