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
    unsigned int id_personagem;
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
        array_personagens->personagem_ptrs = calloc(array_personagens->capacidade_array, sizeof(array_personagens->personagem_ptrs));

        if(!array_personagens->personagem_ptrs){
            printf("Erro no aumento do array de personagens!\n");
            return 0;
        }
    }

    array_personagens->personagem_ptrs[array_personagens->contador] = *personagem;
    personagem->id_personagem = array_personagens->contador;
    array_personagens->contador++;
    return 1;
}

int atributo__distribuicao_padrao(Personagem *personagem){

}

int atributo_soma_3d6(Personagem *personagem){

}

//Cria personagem
int criacao_personagem(Personagem *personagem){
    Personagem personagem_novo;

    printf("Digite o nome do personagem: ");
    fgets(personagem_novo.nome, MAX_NOME, stdin);

    printf("Digite a classe do personagem: ");
    fgets(personagem_novo.classe, MAX_CLASSE, stdin);

    printf("Digite uma descricao simples: ");
    fgets(personagem_novo.descricao, MAX_DESC, stdin);

    personagem_novo.nivel = 0;
    personagem_novo.exp = 0;

    int opt_atributos = 0;
    printf("OPCAO DE ATRIBUTOS: \n");
    printf("\t1. Definição padrão (15,14,13,12,10,8) \n");
    printf("\t2. Soma aleatoria de 3 dados de 6 \n");
    printf("Digite como deseja definir seus atributos: \n");
    scanf("%d", &opt_atributos);
}



int main(void){
    Personagens *banco_personagens = create_personagens();
    Personagem teste_personagem;
    
    printf("Digite o nome do personagem: ");
    fgets(teste_personagem.nome, MAX_NOME, stdin);

    add_personagem(&teste_personagem, banco_personagens);
    printf("%s", banco_personagens->personagem_ptrs[0].nome);

    //Desaloca
    free(banco_personagens->personagem_ptrs);
    return 0;
}