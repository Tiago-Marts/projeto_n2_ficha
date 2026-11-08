#ifndef MENU_H
#define MENU_H


#include <stdio.h>
#include "../include/item.h"
#include "../include/personagem.h"

//Menu do update do inventario do personagem
int update_inventario(Personagem *personagem);

//Menu do update de personagem
int update_personagem(Personagem *personagem);


//Printa o ID e Nome do personagem, por comodidade
void print_array_personagens(Personagens* banco_personagens);

//Menus
void menu_personagem(Personagem *personagem, Personagens *banco_personagens);

void acesso_personagem(Personagens *banco_personagens);

//Menu Geral
void menu(Personagens *banco_personagens);

#endif