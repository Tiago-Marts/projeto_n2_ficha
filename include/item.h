#ifndef ITEM_H
#define ITEM_H

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
int init_inventario(Inventario *inventario);


//Adiciona um item ao inventario do personagem. Retorna 1 se sucesso, 0 se falha
int add_item(Item *item, Inventario *inv);

//CREATE - Item
void criacao_item(Item *item_novo);

//READ - Item
//Busca o item por nome. Retorna o ponteiro para o item, caso o encontre. Se nao, retorna NULL
Item* busca_item_por_nome(char *nome, Inventario *inv);

//Busca o item por nome e retorna a posicao dele no aray. Se nao for encontrado, retorna -1;
int get_posicao_item_por_nome(char *nome, Inventario *inv);

//UPDATE - Item
int update_nome_item(Item *item);

int update_desc_item(Item *item);

int update_qnt_item(Item *item);

//DELETE - Item
int delete_item_por_nome(char *nome, Inventario *inv);

//Utilizada no final para desalocar o espaco dos itens e zerar os outros campos.
void desaloca_itens(Inventario *inv);
#endif