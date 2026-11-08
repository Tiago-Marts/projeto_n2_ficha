
#include "../include/personagem.h"
#include "../include/menu.h"




int main(void){
    Personagens banco_personagens;
    create_personagens(&banco_personagens);

    menu(&banco_personagens);

    //Desaloca
    desaloca(&banco_personagens);
    return 0;
}
