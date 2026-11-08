#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//macros
#define MAX_NOME 50
#define MAX_CLASSE 50
#define MAX_DESC 100

//Structs
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
int add_personagem(Personagem *personagem, Personagens *array_personagens){
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

    personagem->id_personagem = array_personagens->contador;
    array_personagens->personagem_ptrs[array_personagens->contador] = *personagem;
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

//Cria item

//Cria personagem e retorna 1 se sucesso e 0 se falha em alguma etapa
int criacao_personagem(Personagem *personagem){
    personagem->nome = (char*)malloc((MAX_NOME) * sizeof(char)); //Aloca memoria pro nome
    personagem->id_personagem = 0;
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

        init_inventario(&personagem->inventario);
        int qnt_itens = 0;
        printf("Digite a quantidade de itens a ser adicionado: ");
        scanf("%d", &qnt_itens);

        for(int i = 0; i < qnt_itens; i++){
            Item novo_item;
            criacao_item(&novo_item);
            add_item(&novo_item, &personagem->inventario);
        }

        return 1;
    }

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
void delete_personagem_por_id(Personagens* banco_personagens, int id){
    //Busca o personagem, se nao existir da erro
    if(!busca_personagem_por_id(id, banco_personagens)){
        printf("ERRO: personagem nao existe no sistema. Retornando...\n");
        return;
    }

    //1 - Muda a posicao no array
    for(size_t i = id; i < banco_personagens->contador - 1; i++){
        banco_personagens->personagem_ptrs[i] = banco_personagens->personagem_ptrs[i+1];
    }

    //2 - Realoca o array
    realoc_array_personagens(banco_personagens);
}

//DELETE PERSONAGEM POR NOME: Verifica se o personagem existe, muda a posicao dos objetos no array e depois realoca a posicao da memoria dos ponteiros
void delete_personagem_por_nome(Personagens* banco_personagens, char* nome){
    //Busca o personagem, se nao existir da erro
    Personagem* busca = busca_personagem_por_nome(nome, banco_personagens);
    if(!busca){
        printf("ERRO: personagem nao existe no sistema. Retornando...\n");
        return;
    }

    //1 - Muda a posicao no array
    for(size_t i = busca->id_personagem; i < banco_personagens->contador - 1; i++){
        banco_personagens->personagem_ptrs[i] = banco_personagens->personagem_ptrs[i+1];
    }

    //2 - Realoca o array
    realoc_array_personagens(banco_personagens);
}

//Printa o ID e Nome do personagem, por comodidade
void print_array_personagens(Personagens* banco_personagens){
    for(size_t i = 0; i < banco_personagens->contador; i++){
        Personagem personagem = banco_personagens->personagem_ptrs[i];
        printf("ID: %d - Nome: %s", personagem.id_personagem, personagem.nome);
        
        printf("ATRIBUTOS: \n");
        for(int j = 0; j < 6; j++){
            printf("\t%d - %d\n", personagem.atributos[j], personagem.mod_atributos[j]);
        }

        int tamanho_inventario = personagem.inventario.contador;
        printf("INVENTARIO\n");
        for(int k = 0; k < tamanho_inventario; k++){
            Item item = personagem.inventario.itens[k];
            printf("\tNOME:%s \tDESC.:%s \tQUANTIDADE:%d\n", item.nome_item, item.descricao_item, item.quantidade);
        }
    }
}

int main(void){
    Personagens banco_personagens;
    create_personagens(&banco_personagens);


    //Teste temporario de criacao. Vou apagar depois
    Personagem teste_personagem;


    criacao_personagem(&teste_personagem);
    add_personagem(&teste_personagem, &banco_personagens);

    Personagem teste_2 = teste_personagem;
    teste_2.nome = "Nome legal\n";
    add_personagem(&teste_2, &banco_personagens);
    add_personagem(&teste_2, &banco_personagens);
    
    print_array_personagens(&banco_personagens);


    delete_personagem_por_id(&banco_personagens, 1);


    //Desaloca
    free(teste_personagem.nome);
    free(banco_personagens.personagem_ptrs);
    return 0;
}
