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
    int quantidade;
} Item;

typedef struct {
    Item *itens;
    size_t contador;
    size_t capacidade_array;
} Inventario;

//ITENS
//Inicializa o array de itens. Retorna 1 se sucesso, 0 se falha
int init_inventario(Inventario *inventario){
    inventario->capacidade_array = 100; //Escolha arbitraria tambem
    inventario->contador = 0;
    inventario->itens = calloc(inventario->capacidade_array, sizeof(inventario->itens));

    if(!inventario->itens){
        printf("Erro na cricao do inventario\n");
        return 0;
    }

    return 1;
}

//Adiciona um item ao inventario do personagem. Retorna 1 se sucesso, 0 se falha
int add_item(Item *item, Inventario *inv){
    //Verifica o limite
    if(inv->contador == inv->capacidade_array){
        size_t novo_limite = inv->capacidade_array * 2;
        Item *tmp = realloc(inv->itens, novo_limite * sizeof(Item)); //Eh mais seguro alterar um array temp do que alterar diretamente o que usamos
        if(!tmp){
            printf("Erro na adicao de item\n");
            return 0;
        }
        inv->itens = tmp;
        inv->capacidade_array = novo_limite;
    }

    inv->itens[inv->contador] = *item;
    inv->contador++;
    return 1;
}

//CREATE - Item
void criacao_item(Item *item_novo){
    while(getchar() != '\n'); //limpa o buffer
    printf("Digite o nome do item: ");
    fgets(item_novo->nome_item, MAX_NOME, stdin);

    printf("Digite uma descricao para o item: ");
    fgets(item_novo->descricao_item, MAX_DESC, stdin);

    int qnt_item = 0;
    printf("Digite a quantidade de itens: ");
    scanf("%d", &qnt_item);
    item_novo->quantidade = qnt_item;
}

//READ - Item
//Busca o item por nome. Retorna o ponteiro para o item, caso o encontre. Se nao, retorna NULL
Item* busca_item_por_nome(char *nome, Inventario *inv){
    Item *resultado_busca = NULL;
    
    for(size_t i = 0; i < inv->contador; i++){
        if(!strcmp(nome, inv->itens[i].nome_item)){
            resultado_busca = &inv->itens[i];
            return resultado_busca;
        }
    }

    return resultado_busca;
}

//Busca o item por nome e retorna a posicao dele no aray. Se nao for encontrado, retorna -1;
int get_posicao_item_por_nome(char *nome, Inventario *inv){
    int resultado_busca = -1; //-1 nao eh uma posicao valida no array, assim fica mais facil de verificar erro na utilizacao da funcao

    for(size_t i = 0; i < inv->contador; i++){
        if(!strcmp(nome, inv->itens[i].nome_item)){
            resultado_busca = i;
            return resultado_busca;
        }
    }

    return resultado_busca;
}

//UPDATE - Item
int update_nome_item(Item *item){
    char novo_nome[MAX_NOME];
    printf("O nome atual do item eh: %s", item->nome_item);
    printf("Digite o novo nome do item: ");
    while(getchar() != '\n'); //limpando buffer
    fgets(novo_nome, MAX_NOME, stdin);
    char* resultado_copia = NULL;

    resultado_copia = strcpy(item->nome_item, novo_nome);
    if(!resultado_copia){
        printf("Erro na atualizacao do nome do item\n");
        return 0;
    }

    return 1;
}

int update_desc_item(Item *item){
    char nova_desc[MAX_DESC];
    printf("A descricao atual do item eh: %s", item->descricao_item);
    printf("Digite a nova descricao do item: ");
    while(getchar() != '\n'); //limpando buffer
    fgets(nova_desc, MAX_DESC, stdin);
    char* resultado_copia = NULL;

    resultado_copia = strcpy(item->descricao_item, nova_desc);
    if(!resultado_copia){
        printf("Erro na atualizacao da descricao do item\n");
        return 0;
    }

    return 1;
}

int update_qnt_item(Item *item){
    int nova_qnt = 0;
    
    printf("A quantidade atual do item eh: %d\n", item->quantidade);
    printf("Digite a nova quantidade do item: ");
    while(getchar() != '\n'); //limpando buffer
    scanf("%d", &nova_qnt);

    item->quantidade = nova_qnt;



    return 1;
}

//DELETE - Item
int delete_item_por_nome(char *nome, Inventario *inv){
    int index = get_posicao_item_por_nome(nome, inv);

    //Se nao acha o item
    if(index == -1) {
        printf("ERRO: Item nao encontrado\n");
        return 0;
    }

    //O memmove copia bytes de um espaço na memoria pra outro, podendo ocorrer sobreposicao. 
    //Aqui o utilizamos para sobrepor o item de posicao n pelo n+1
    memmove(&inv->itens[index], &inv->itens[index+1], (inv->contador - index - 1) * sizeof(Item));
    inv->contador--;
    return 1;
}

//Utilizada no final para desalocar o espaco dos itens e zerar os outros campos.
void desaloca_itens(Inventario *inv){
    free(inv->itens);
    inv->itens = NULL;
    inv->capacidade_array = 0;
    inv->contador = 0;
}