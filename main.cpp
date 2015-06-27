#include <stdio.h>
#include <allegro5/allegro.h>

#include "game.h"
#include "player.h"
#include "alien.h"

int main(int argc, char **argv) {

    Jogo jogo;

	Alien alien[LINHAS_TROPA][COLUNAS_TROPA];

	inic_funcoes_allegro();

   	inicializa_display (&jogo, 640, 480);

    // TITLE SCREEN
	inicializa_menus(&jogo.menu);
	loop_menu(&jogo.menu, 3);

	// finaliza_jogo (&jogo);

    while (jogo.menu.new_game == 1) {

    	inicializa_jogo (&jogo);

    	loop_de_jogo (&jogo);

    	finaliza_jogo (&jogo);
    }

	finaliza_display (&jogo);

    return 0;
}