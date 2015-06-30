#include <stdio.h>
#include <allegro5/allegro.h>

#include "game.h"
#include "player.h"
#include "alien.h"

int main(int argc, char **argv) {

    Jogo jogo;

	Alien alien[LINHAS_TROPA][COLUNAS_TROPA];

	inic_allegro();

   	inicializa_display (&jogo, LARGURA_DISPLAY, ALTURA_DISPLAY);

    // TITLE SCREEN
	tela_boot_jogo(&jogo);

	inicializa_menus(&jogo.menu);

	loop_menu(&jogo.menu, TITLE_SCREEN);

    while (jogo.menu.new_game == 1) {
    	inicializa_jogo (&jogo);

    	loop_de_jogo (&jogo, &jogo.hud);

    	finaliza_jogo (&jogo);
    }

	finaliza_display (&jogo);

    return 0;
}
