#include <stdio.h>
#include "../include/item.h"
#include "../include/personagem.h"

//Menu do update do inventario do personagem
int update_inventario(Personagem *personagem){
    char nome[MAX_NOME];
    while(getchar() != '\n'); //limpando buffer
    printf("Digite o nome do item a ser atualizado: ");
    fgets(nome, MAX_NOME, stdin);

    Item *novo_item = busca_item_por_nome(nome, &personagem->inventario);
    if(!novo_item){
        printf("Item nao encontrado\n");
        return 0;
    }

    printf("Opcoes de atualizacao: \n");
    printf("\t1.Atualizar nome do item\n");
    printf("\t2.Atualizar descricao do item\n ");
    printf("\t3.Atualizar quantidade do item\n");
    printf("\t4.Adicionar item\n");
    printf("\t5.Deletar item\n");
    printf("Digite a opcao escolhida: ");
    int escolha = 0;
    scanf("%d", &escolha);
    switch(escolha){
        case 1:
            update_nome_item(novo_item);
            break;
        case 2:
            update_desc_item(novo_item);
            break;
        case 3:
            update_qnt_item(novo_item);
            break;
        case 4:
            add_item(novo_item, &personagem->inventario);
            break;
        case 5:
            delete_item_por_nome(novo_item->nome_item, &personagem->inventario);
            printf("Item deletado\n");
            break;
        default:
            printf("Opcao invalida. Retornando...\n");
            break;
    }
    return 1;
}

//Menu do update de personagem
int update_personagem(Personagem *personagem){
    printf("Opcoes de atualizao de personagem: \n");
    printf("\t1.Atualizar nome\n");
    printf("\t2.Atualizar classe\n");
    printf("\t3.Atualizar descricao\n");
    printf("\t4.Atualizar atributos\n");
    printf("\t5.Atualizar nivel\n");
    printf("\t6.Atualizar experiencia\n");
    printf("\t7.Atualizar inventario\n");
    int escolha = 0;
    printf("Digite a opcao escolhida: ");
    scanf("%d", &escolha);
    switch(escolha){
        case 1:
            update_nome_personagem(personagem);
            break;
        case 2:
            update_classe_personagem(personagem);
            break;
        case 3:
            update_descricao_personagem(personagem);
            break;
        case 4:
            update_atributo_personagem(personagem);
            break;
        case 5:
            update_nivel_personagem(personagem);
            break;
        case 6:
            update_exp_personagem(personagem);
            break;
        case 7:
            update_inventario(personagem);
            break;
        default:
            printf("Opcao invalida. Retornando...\n");
            break;
    }
    return 1;
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

//Menus
void menu_personagem(Personagem *personagem, Personagens *banco_personagens){
    printf("Personagem acessado: %s", personagem->nome);
    printf("Opcoes: \n");
    printf("\t1.Modificar personagem \n");
    printf("\t2.Deletar personagem\n");
    printf("Digite a opcao a ser escolhida: ");
    int escolha = 0;
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        update_personagem(personagem);
        break;
    case 2:
        delete_personagem(personagem, banco_personagens);
        printf("Personagem deletado.\n");
        break;
    
    default:
        break;
    }
}

void acesso_personagem(Personagens *banco_personagens){
    printf("Formas de acesso: \n");
    printf("\t1.Acessar por ID \n");
    printf("\t2.Acessar por nome\n");
    printf("Digite a forma escolhida: ");
    int escolha = 0;
    scanf("%d", &escolha);

    Personagem *personagem_acessado = NULL;
    switch (escolha)
    {
    case 1:
        unsigned int id_busca = 0;
        printf("Digite o ID a ser buscado: ");
        scanf("%d", &id_busca);
        personagem_acessado = busca_personagem_por_id(id_busca, banco_personagens);
        if(!personagem_acessado){
            printf("Personagem nao encontrado.Retornando...\n");
            return;
        }
        menu_personagem(personagem_acessado, banco_personagens);
        break;
    case 2:
        char nome_busca[MAX_NOME];
        while(getchar() != '\n'); //limpando buffer
        printf("Digite o Nome a ser buscado: ");
        fgets(nome_busca, MAX_NOME, stdin);
        personagem_acessado = busca_personagem_por_nome(nome_busca, banco_personagens);
        if(!personagem_acessado){
            printf("Personagem nao encontrado.Retornando...\n");
            return;
        }
        menu_personagem(personagem_acessado, banco_personagens);
        break;

    
    default:
        printf("Opcao invalida. Retornando...\n");
        break;
    }
}

//Menu Geral
void menu(Personagens *banco_personagens){

    int escolha = 0;

    while(escolha != 4){
        printf("FICHA DE RPG (D&D 5e)\n");
        printf("Opcoes:\n");
        printf("\t1.Criar personagem\n");
        printf("\t2.Acessar personagem\n");
        printf("\t3.Mostrar personagens cadastrados\n");
        printf("\t4.Sair\n");
        printf("Digite a opcao escolhida: ");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            criacao_personagem(banco_personagens);
            break;
        case 2:
            acesso_personagem(banco_personagens);
            break;
        case 3:
            print_array_personagens(banco_personagens);
            break;
        case 4:
            printf("Saindo do programa...\n");
            break;
        
        default:
            break;
        }
    }
}