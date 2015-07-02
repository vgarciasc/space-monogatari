#include <stdio.h>
#include <allegro5/allegro.h>

#include "game.h"
#include "player.h"
#include "alien.h"

int main(int argc, char **argv) {

    Jogo jogo;
    int fase = 0;

	inic_allegro();
   	inicializa_display (&jogo);

    // TITLE SCREEN
	tela_boot_jogo(&jogo);
	inicializa_menus(&jogo.menu);
	loop_menu(&jogo.menu, &jogo.hud, TITLE_SCREEN);

    while (jogo.menu.new_game == 1) {
    	inicializa_jogo (&jogo, fase);

    	if (loop_de_jogo (&jogo))
            fase++;

    	finaliza_jogo (&jogo);
    }

	finaliza_display (&jogo);

    return 0;
}
