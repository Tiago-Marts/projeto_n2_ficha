#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//macros
#define MAX_NOME 50
#define MAX_CLASSE 50
#define MAX_DESC 100


typedef struct {
    char nome_item[MAX_NOME];
    char descricao_item[MAX_DESC];
} Item;


//Personagem
typedef struct {
    unsigned int id_personagem;
    char *nome;
    char classe[MAX_CLASSE];
    int nivel;
    int exp;
    int atributos[6];
    int mod_atributos[6];
    char descricao[MAX_DESC];
} Personagem;


typedef struct {
    Personagem *personagem_ptrs;
    size_t capacidade_array;
    size_t contador;
} Personagens;

//CREATE
//Inicializa o array de personagens
void create_personagens(Personagens *personagens){
    personagens->capacidade_array = 100; //Arbitrario
    personagens->contador = 0;
    personagens->personagem_ptrs = calloc(personagens->capacidade_array, sizeof(personagens->personagem_ptrs));

    //Trativa
    if(!personagens->personagem_ptrs){
        printf("Erro na criacao do array de personagens!\n");
        return;
    }

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

void menu_atributos(){
    printf("ATRIBUTOS: \n");
    printf("\t1.Constituicao\n");
    printf("\t2.Destreza\n");
    printf("\t3.Sabedoria\n");
    printf("\t4.Carisma\n");
    printf("\t5.Inteligencia\n");
    printf("\t6.Forca\n");
}

void define_atributo(Personagem* personagem, int atributo, int valor){
    personagem->atributos[atributo-1] = valor;
}

void define_mod_atributos(Personagem* personagem, int atributo, int valor){
    personagem->mod_atributos[atributo-1] = valor;
}

//Todo: Nao pode repedir atributo
void atributo__distribuicao_padrao(Personagem *personagem){

}

//A gente usa o metodo do D&D 5e para calcular os modificadores de atributos
void calcula_mod_atributos(Personagem *personagem){
    for(int i = 1; i <= 6; i++){
        int atributo = personagem->atributos[i-1];
        define_mod_atributos(personagem, i, (atributo-10)/2);
    }
}

//Retorna a soma de 3 valores de 1 à 6
int roda_3d6(){
    int d1, d2, d3;
    d1 = rand()%6 + 1;
    d2 = rand()%6 + 1;
    d3 = rand()%6 + 1;

    int soma = (d1+d2+d3);

    printf("Resultados: %d - %d - %d - SOMA: %d\n", d1,d2,d3, soma);
    return soma;
}

//Executa a seleção de valores aleatorios e define os atributos a partir deles
void atributo_soma_3d6(Personagem *personagem){
    int cons = roda_3d6();
    int dex = roda_3d6();
    int sab = roda_3d6();
    int car = roda_3d6();
    int intel = roda_3d6();
    int forc = roda_3d6();

    define_atributo(personagem, 1, cons);
    define_atributo(personagem, 2, dex);
    define_atributo(personagem, 3, sab);
    define_atributo(personagem, 4, car);
    define_atributo(personagem, 5, intel);
    define_atributo(personagem, 6, forc);
}

//Cria item

//Cria personagem e retorna 1 se sucesso e 0 se falha em alguma etapa
int criacao_personagem(Personagem *personagem){
    personagem->nome = (char*)malloc((MAX_NOME) * sizeof(char)); //Aloca memoria pro nome
    printf("Digite o nome do personagem: ");
    fflush(stdin);
    fgets(personagem->nome, MAX_NOME, stdin);

    printf("Digite a classe do personagem: ");
    fgets(personagem->classe, MAX_CLASSE, stdin);

    printf("Digite uma descricao simples: ");
    fgets(personagem->descricao, MAX_DESC, stdin);

    personagem->nivel = 1;
    personagem->exp = 0;

    int opt_atributos = 0;
    while(opt_atributos != 1 && opt_atributos != 2){
        printf("OPCAO DE ATRIBUTOS: \n");
        printf("\t1. Definição padrão (15,14,13,12,10,8) \n");
        printf("\t2. Soma aleatoria de 3 dados de 6 \n");
        printf("Digite como deseja definir seus atributos: \n");
        scanf("%d", &opt_atributos);

        switch (opt_atributos)
        {
        case 1:
            atributo__distribuicao_padrao(personagem);
            break;

        case 2:
            atributo_soma_3d6(personagem);
            break;

        default:
            printf("Opcao invalida. Tente novamente\n");
            break;
        }

        //Define o modificador dos atributos
        calcula_mod_atributos(personagem);

        return 1;
    }

    return 1;
}

//BUSCA (Necessaria para UPDATE e DELETE)
// Busca por id. Retorna o ponteiro do personagem encotrado.Se nao encontrar nada, retorna NULL
Personagem* busca_personagem_por_id(unsigned int id_busca, Personagens* banco_personagens){
    Personagem* resultado_busca = NULL;
    for(size_t i = 0; i < banco_personagens->contador; i++){
        if(id_busca == banco_personagens->personagem_ptrs[i].id_personagem){
            printf("Personagem encontrado!\n");
            resultado_busca = &banco_personagens->personagem_ptrs[i];
            return resultado_busca;
        }
    }

    return resultado_busca;
}

// Busca o personagem por nome e retorna o ponteiro encontrado. Se nao encontrar nada retorna NULL
Personagem* busca_personagem_por_nome(char *nome_busca, Personagens* banco_personagens){
    Personagem* resultado_busca = NULL;
    for(size_t i = 0; i < banco_personagens->contador; i++){
        if(!strcmp(nome_busca, banco_personagens->personagem_ptrs[i].nome)){
            printf("Personagem encontrado!\n");
            resultado_busca = &banco_personagens->personagem_ptrs[i];
            return resultado_busca;
        }
    }

    return resultado_busca;
}

//UPDATE

//DELETE


int main(void){
    Personagens *banco_personagens;
    create_personagens(banco_personagens);

    Personagem teste_personagem;


    criacao_personagem(&teste_personagem);
    add_personagem(&teste_personagem, banco_personagens);
    printf("ID: %d - NOME: %s",banco_personagens->personagem_ptrs[0].id_personagem, banco_personagens->personagem_ptrs[0].nome);
    printf("NIVEL: %d\n", banco_personagens->personagem_ptrs[0].nivel);


    printf("DEX: %d ", banco_personagens->personagem_ptrs[0].atributos[1]);
    int mod = banco_personagens->personagem_ptrs[0].mod_atributos[1];
    if( mod > 0 ){
        printf("(+%d)\n", mod );
    } else if ( mod < 0){
        printf("(-%d)\n", mod);
    } else {
        printf("(%d)\n", mod);
    }


    Personagem* teste_busca = busca_personagem_por_nome("tigas\n", banco_personagens);

    if(teste_busca){
        printf("NOME DO PERSONAGEM BUSCADO POR ID: %s", teste_busca->nome);
    } else {
        printf("Peronsagem NAO ENCONTRADO!\n");
    }

    //Desaloca
    free(teste_personagem.nome);
    free(banco_personagens->personagem_ptrs);
    return 0;
}
