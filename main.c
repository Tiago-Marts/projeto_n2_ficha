#include <stdio.h>
#include <stdlib.h>

//macros
#define MAX_NOME 50
#define MAX_CLASSE 50
#define MAX_DESC 100


typedef struct {
    int cons;
    int dex;
    int sab;
    int charis;
    int intelig;
    int forc;
} Atributos;

typedef struct {
    char descricao_item[MAX_DESC];
} Item;


//Personagem
typedef struct {
    char nome[MAX_NOME];
    char classe[MAX_CLASSE];
    int nivel;
    int exp;
    Atributos atributos;
    Atributos modificadores_atributos;
    char descricao[MAX_DESC];
    Item *equipamentos;
} Personagem;


typedef struct {
    Personagem *personagem_ptrs;
    size_t capacidade_array;
    size_t contador;
} Personagens;

//Inicializa o array de personagens
Personagens *create_personagens(){
    Personagens *personagens;
    personagens->capacidade_array = 100; //Arbitrario
    personagens->contador = 0;
    personagens->personagem_ptrs = calloc(personagens->capacidade_array, sizeof(personagens->personagem_ptrs));

    //Trativa
    if(!personagens->personagem_ptrs){
        printf("Erro na criacao do array de personagens!\n");
        return NULL;
    } 

    return personagens;
}

//Adiciona um personagem no array de personagens
int add_personagem(Personagem *personagem, Personagens *array_personagens){
    //Se chegou no limite, dobra (arbitrario)
    if(array_personagens->contador == array_personagens->capacidade_array){
        array_personagens->capacidade_array *= 2;
        
    }
}


int main(void){
    Personagens *banco_personagens = create_personagens();
    return 0;
}