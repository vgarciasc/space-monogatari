#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "player.h"

#define altura_sprites 64
#define largura_sprites 64

void inicializa_player (Player* player, int posicao_x, int posicao_y) {
	player->posicao_x = posicao_x;
	player->posicao_y = posicao_y;

	inicializa_sprites_player (player);

	player->delta_x = al_get_bitmap_width(player->sprites[0])/2;
}

void finaliza_player (Player* player) {
	finaliza_sprites_player(player);
}

void desenha_player (Player* player) {
	int flags = 0;
  
	if (player->direcao_atual == DIREITA)
		flags = ALLEGRO_FLIP_HORIZONTAL;

	al_draw_bitmap (player->sprites[0], 
					player->posicao_x - player->delta_x, 
					player->posicao_y,
					flags);
}

void inicializa_sprites_player (Player* player) {
	player->sprites[0] = al_load_bitmap("resources/player4.png");

	if (player->sprites[0] == NULL) {
		puts("Erro ao carregar o arquivo resources/player4.png");
		exit(0);
	}
}

void finaliza_sprites_player (Player* player) {
	al_destroy_bitmap(player->sprites[0]);
}

void move_player (Player* player, DIRECAO direcao) {
	if (direcao == ESQUERDA) {
		player->posicao_x -= DISTANCIA_PASSO;
		player->direcao_atual = ESQUERDA;
	}
	if (direcao == DIREITA) {
		player->posicao_x += DISTANCIA_PASSO;
		player->direcao_atual = DIREITA;
	}
}

int get_posicao_x_max_player (Player* player){
	return player->posicao_x + player->delta_x;
}

int get_posicao_x_min_player (Player* player){
	return player->posicao_x - player->delta_x;
}