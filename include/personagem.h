#ifndef PERSONAGEM_H
#define PERSONAGEM_H


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
void create_personagens(Personagens *personagens);

//Adiciona um personagem no array de personagens. Retorna 1 se sucesso, 0 se falha
int add_personagem(Personagem personagem, Personagens *array_personagens);

void menu_atributos();

void define_atributo(Personagem* personagem, int atributo, int valor);

void define_mod_atributos(Personagem* personagem, int atributo, int valor);

//Faz a distribuicao de valores predefinidos para os atributos. O jogador escolhe para qual atributo o valor ira
void atributo__distribuicao_padrao(Personagem *personagem);

//A gente usa o metodo do D&D 5e para calcular os modificadores de atributos
void calcula_mod_atributos(Personagem *personagem);

//Retorna a soma de 3 valores de 1 à 6
int roda_3d6();

//Executa a seleção de valores aleatorios e define os atributos a partir deles
void atributo_soma_3d6(Personagem *personagem);


//Cria personagem e retorna 1 se sucesso e 0 se falha em alguma etapa
int criacao_personagem(Personagens *banco_personagens);

//BUSCA/READ (Necessaria para UPDATE e DELETE)
// Busca por id. Retorna o ponteiro do personagem encotrado.Se nao encontrar nada, retorna NULL
Personagem* busca_personagem_por_id(unsigned int id_busca, Personagens* banco_personagens);

int get_posicao_personagem_por_id(unsigned int id_busca, Personagens* banco_personagens);


// Busca o personagem por nome e retorna o ponteiro encontrado. Se nao encontrar nada retorna NULL
Personagem* busca_personagem_por_nome(char *nome_busca, Personagens* banco_personagens);

int get_posicao_personagem_por_nome(char *nome_busca, Personagens* banco_personagens);

//UPDATE
//UPDATE do nome. Retorna 1 se sucesso, 0 se falha
int update_nome_personagem(Personagem* personagem);


//UPDATE da classe. Retorna 1 se sucesso, 0 se falha
int update_classe_personagem(Personagem* personagem);

//UPDATE da descricao. Retorna 1 se sucesso, 0 se falha
int update_descricao_personagem(Personagem* personagem);

//UPDATE do atributo. Retorna 1 se sucesso, 0 se falha
int update_atributo_personagem(Personagem* personagem);


//UPDATE do nivel. Retorna 1 se sucesso, 0 se falha
int update_nivel_personagem(Personagem* personagem);


//UPDATE da exp. Retorna 1 se sucesso, 0 se falha
int update_exp_personagem(Personagem* personagem);

//DELETE PERSONAGEM: Verifica se o personagem existe, muda a posicao dos objetos no array e depois realoca a posicao da memoria dos ponteiros
void delete_personagem(Personagem *personagem, Personagens *banco_personagens);

void desaloca(Personagens *banco_personagens);


#endif