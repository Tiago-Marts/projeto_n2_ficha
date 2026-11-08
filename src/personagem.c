
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/item.h"

//macros
#define MAX_NOME 50
#define MAX_CLASSE 50
#define MAX_DESC 100


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
    Inventario inventario;
} Personagem;


typedef struct {
    Personagem* personagem_ptrs;
    size_t capacidade_array;
    size_t contador;
} Personagens;




//PERSONAGEM
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

//Adiciona um personagem no array de personagens. Retorna 1 se sucesso, 0 se falha
int add_personagem(Personagem personagem, Personagens *array_personagens){
    //Se chegou no limite, dobra (arbitrario)
    if(array_personagens->contador == array_personagens->capacidade_array){
        size_t novo_limite = array_personagens->capacidade_array*2;
        Personagem* tmp = realloc(array_personagens->personagem_ptrs, novo_limite * sizeof(Personagem));
        if(!tmp){
            printf("Erro de alocacao de memoria para o array de personagens");
            return 0;
        }

        array_personagens->personagem_ptrs = tmp;
        array_personagens->capacidade_array = novo_limite;
    }

    
    array_personagens->personagem_ptrs[array_personagens->contador] = personagem;
    array_personagens->personagem_ptrs[array_personagens->contador].id_personagem = array_personagens->contador;
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

//Faz a distribuicao de valores predefinidos para os atributos. O jogador escolhe para qual atributo o valor ira
void atributo__distribuicao_padrao(Personagem *personagem){
    int distribuicao[6] = {15,14,13,12,10,8};
    int escolhas[6] = {0,0,0,0,0,0};
    int escolha_atributo = 0;
    for(int i = 1; i <= 6; i++){
        distribuicao_atributo:
            menu_atributos();
            printf("Para qual atributo o valor %d devera ir?\n", distribuicao[i-1]);
            printf("Digite o atributo escolhido: ");
            scanf("%d", &escolha_atributo);

            //Verifica se o atributo esta no intervalo correto
            if(escolha_atributo < 1 || escolha_atributo > 6){
                printf("\nNumero invalido, digite novamente\n");
                goto distribuicao_atributo;
            }

            //Verifico se o atributo ja foi escolhido (usa o array definido no inicio para isso)
            for(int j = 0; j < 6; j++){
                if(escolha_atributo == escolhas[j]) {
                    printf("\nAtributo ja foi escolhido anteriormente, tente novamente\n");
                    goto distribuicao_atributo;
                }
            }

            //Se passar, adicionamos no array de escolhas
            escolhas[i] = escolha_atributo;

            define_atributo(personagem, escolha_atributo, distribuicao[i-1]);
    }
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
    for(int i = 1; i <= 6; i++){
        int valor_atributo = roda_3d6();
        define_atributo(personagem, i, valor_atributo);
    }
}


//Cria personagem e retorna 1 se sucesso e 0 se falha em alguma etapa
int criacao_personagem(Personagens *banco_personagens){
    Personagem novo_personagem;
    novo_personagem.nome = (char*)malloc((MAX_NOME) * sizeof(char)); //Aloca memoria pro nome
    novo_personagem.id_personagem = 0;
    printf("Digite o nome do personagem: ");
    while(getchar() != '\n');
    fgets(novo_personagem.nome, MAX_NOME, stdin);

    printf("Digite a classe do personagem: ");
    fgets(novo_personagem.classe, MAX_CLASSE, stdin);

    printf("Digite uma descricao simples: ");
    fgets(novo_personagem.descricao, MAX_DESC, stdin);

    novo_personagem.nivel = 1;
    novo_personagem.exp = 0;

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
            atributo__distribuicao_padrao(&novo_personagem);
            break;

        case 2:
            atributo_soma_3d6(&novo_personagem);
            break;

        default:
            printf("Opcao invalida. Tente novamente\n");
            break;
        }

        //Define o modificador dos atributos
        calcula_mod_atributos(&novo_personagem);


    }


    init_inventario(&novo_personagem.inventario);
    int qnt_itens = 0;
    printf("Digite a quantidade de itens a ser adicionado: ");
    scanf("%d", &qnt_itens);

    for(int i = 0; i < qnt_itens; i++){
        Item novo_item;
        criacao_item(&novo_item);
        add_item(&novo_item, &novo_personagem.inventario);
    }

    add_personagem(novo_personagem, banco_personagens);
    return 1;
}

//BUSCA/READ (Necessaria para UPDATE e DELETE)
// Busca por id. Retorna o ponteiro do personagem encotrado.Se nao encontrar nada, retorna NULL
Personagem* busca_personagem_por_id(unsigned int id_busca, Personagens* banco_personagens){
    Personagem* resultado_busca = NULL;
    for(unsigned int i = 0; i < banco_personagens->contador; i++){
        if(id_busca == banco_personagens->personagem_ptrs[i].id_personagem){
            resultado_busca = &banco_personagens->personagem_ptrs[i];
            return resultado_busca;
        }
    }

    return resultado_busca;
}

int get_posicao_personagem_por_id(unsigned int id_busca, Personagens* banco_personagens){
    int resultado_busca = -1;
    for(unsigned int i = 0; i < banco_personagens->contador; i++){
        if(id_busca == banco_personagens->personagem_ptrs[i].id_personagem){
            resultado_busca = i;
            return resultado_busca;
        }
    }

    return resultado_busca;
}


// Busca o personagem por nome e retorna o ponteiro encontrado. Se nao encontrar nada retorna NULL
Personagem* busca_personagem_por_nome(char *nome_busca, Personagens* banco_personagens){
    Personagem* resultado_busca = NULL;
    for(unsigned int i = 0; i < banco_personagens->contador; i++){
        if(!strcmp(nome_busca, banco_personagens->personagem_ptrs[i].nome)){
            resultado_busca = &banco_personagens->personagem_ptrs[i];
            return resultado_busca;
        }
    }

    return resultado_busca;
}

int get_posicao_personagem_por_nome(char *nome_busca, Personagens* banco_personagens){
    int resultado_busca = -1;
    for(unsigned int i = 0; i < banco_personagens->contador; i++){
        if(!strcmp(nome_busca, banco_personagens->personagem_ptrs[i].nome)){
            resultado_busca = i;
            return resultado_busca;
        }
    }

    return resultado_busca;
}

//UPDATE
//UPDATE do nome. Retorna 1 se sucesso, 0 se falha
int update_nome_personagem(Personagem* personagem){

    char* novo_nome = (char*) malloc((MAX_NOME) * sizeof(char));
    if(!novo_nome){
        printf("Erro na alocacao de atualizacao\n");
        return 0;
    }

    printf("O nome atual do persoangem eh: %s", personagem->nome);
 
    int n;
    while((n = getchar() != '\n' && n != EOF)); //Outra limpeza de buffer

    printf("Digite o novo nome do personagem: \n");
    fgets(novo_nome, MAX_NOME, stdin);

    char* resultado_copia = NULL;
    resultado_copia = strcpy(personagem->nome, novo_nome);
    free(novo_nome); //Desaloca o espaco da memoria

    if(!resultado_copia){
        printf("Erro na atualizacao do nome\n");
        return 0;
    }


    return 1;
    
}


//UPDATE da classe. Retorna 1 se sucesso, 0 se falha
int update_classe_personagem(Personagem* personagem){

    char* nova_classe = (char*) malloc((MAX_CLASSE) * sizeof(char));
    if(!nova_classe){
        printf("Erro na alocacao de atualizacao\n");
        return 0;
    }

    printf("A classe atual do persoangem eh: %s", personagem->classe);
 
    int n;
    while((n = getchar() != '\n' && n != EOF)); //Outra limpeza de buffer

    printf("Digite a nova classe do personagem: \n");
    fgets(nova_classe, MAX_CLASSE, stdin);

    char* resultado_copia = NULL;
    resultado_copia = strcpy(personagem->classe, nova_classe);
    free(nova_classe); //Desaloca o espaco da memoria

    if(!resultado_copia){
        printf("Erro na atualizacao da classe\n");
        return 0;
    }


    return 1;
    
}

//UPDATE da descricao. Retorna 1 se sucesso, 0 se falha
int update_descricao_personagem(Personagem* personagem){

    char* nova_desc = (char*) malloc((MAX_DESC) * sizeof(char));
    if(!nova_desc){
        printf("Erro na alocacao de atualizacao\n");
        return 0;
    }

    printf("A descricao atual do persoangem eh: %s", personagem->descricao);
 
    int n;
    while((n = getchar() != '\n' && n != EOF)); //Outra limpeza de buffer

    printf("Digite a nova descricao do personagem: \n");
    fgets(nova_desc, MAX_DESC, stdin);

    char* resultado_copia = NULL;
    resultado_copia = strcpy(personagem->descricao, nova_desc);
    free(nova_desc); //Desaloca o espaco da memoria

    if(!resultado_copia){
        printf("Erro na atualizacao da descricao\n");
        return 0;
    }


    return 1;
    
}

//UPDATE do atributo. Retorna 1 se sucesso, 0 se falha
int update_atributo_personagem(Personagem* personagem){

    int atributo = 0;
    int novo_atributo = 0;

    menu_atributos();
    printf("Digite o atributo que deseja atualizar: ");
    scanf("%d", &atributo);

    if(atributo < 1 || atributo > 6){
        printf("ERRO: atributo nao localizado. Retornando...\n");
        return 0;
    }

    printf("O valor do atributo atual do persoangem eh: %d\n", personagem->atributos[atributo]);
 
    int n;
    while((n = getchar() != '\n' && n != EOF)); //Outra limpeza de buffer

    printf("Digite o novo valor do atributo do personagem: ");
    scanf("%d", &novo_atributo); //TODO: Adicionar tratamento de erro aqui

    define_atributo(personagem, atributo, novo_atributo);
    define_mod_atributos(personagem, atributo, ((personagem->atributos[atributo-1]-10)/2)); //Faz a modificacao manualmente, mais simples


    return 1;
    
}

//UPDATE do nivel. Retorna 1 se sucesso, 0 se falha
int update_nivel_personagem(Personagem* personagem){

    int novo_nivel = 0;

    printf("O nivel atual do persoangem eh: %d\n", personagem->nivel);
 
    int n;
    while((n = getchar() != '\n' && n != EOF)); //Outra limpeza de buffer

    printf("Digite o novo nivel do personagem: ");
    scanf("%d", &novo_nivel); //TODO: Adicionar tratamento de erro aqui

    personagem->nivel = novo_nivel;


    return 1;
    
}


//UPDATE da exp. Retorna 1 se sucesso, 0 se falha
int update_exp_personagem(Personagem* personagem){

    int nova_exp = 0;

    printf("A experiencia atual do persoangem eh: %d\n", personagem->exp);
 
    int n;
    while((n = getchar() != '\n' && n != EOF)); //Outra limpeza de buffer

    printf("Digite a nova experiencia do personagem: ");
    scanf("%d", &nova_exp); //TODO: Adicionar tratamento de erro aqui

    personagem->exp = nova_exp;


    return 1;
    
}


//DELETE: o processo acontece em duas etapas. Primero, a gente muda a posicao dos objetos no array. Depois a gente realoca as posicoes dos ponteiros na memoria
//Realoca os ponteiros do array, necessario depois que a gente apaga um elemento dele. 
void realoc_array_personagens(Personagens* banco_personagens){

    Personagem* tmp_personagens = realloc(banco_personagens->personagem_ptrs, (banco_personagens->contador-1) * sizeof(Personagem));

    if(tmp_personagens==NULL && banco_personagens->contador > 1){
        perror("ERRO: Nao ha memoria disponivel para ser usada...\n");
        exit(EXIT_FAILURE);
    }


    banco_personagens->contador -= 1; 
    banco_personagens->personagem_ptrs = tmp_personagens;
}

//DELETE PERSONAGEM: Verifica se o personagem existe, muda a posicao dos objetos no array e depois realoca a posicao da memoria dos ponteiros
void delete_personagem(Personagem *personagem, Personagens *banco_personagens){
    int index = get_posicao_personagem_por_id(personagem->id_personagem, banco_personagens);
    if(index == -1){
        printf("Personagem nao encontrado...\n");
        return;
    }

        //1 - Muda a posicao no array
    for(size_t i = index; i < banco_personagens->contador - 1; i++){
        banco_personagens->personagem_ptrs[i] = banco_personagens->personagem_ptrs[i+1];
    }

    //2 - Realoca o array
    realoc_array_personagens(banco_personagens);
}

//Desaloca a memoria que foi alocada dinamicamente durante a execucao do programa
void desaloca(Personagens *banco_personagens){
    size_t contador = banco_personagens->contador;
    for(size_t i = 0; i < contador; i++){
        free(banco_personagens->personagem_ptrs[i].nome); //O nome foi alocado dinamicamente na criacao do personagem
        desaloca_itens(&banco_personagens->personagem_ptrs[i].inventario);
    }
    free(banco_personagens->personagem_ptrs);
    banco_personagens->personagem_ptrs = NULL;
    banco_personagens->contador = 0;
    banco_personagens->capacidade_array = 0;
}
