#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "player.h"

#define ALTURA_SPRITES_PLAYER 48
#define LARGURA_SPRITES_PLAYER 48

void inicializa_player (Player* player, double posicao_x, double posicao_y) {
	player->posicao_x = posicao_x;
	player->posicao_y = posicao_y;
	player->projetil_cooldown = 10;

	// player->sprites[0] = inicializa_sprites_player (player, "resources/player4.png", 16, 16);

	player->sprites[0] = al_load_bitmap("resources/player4.png");

	if (player->sprites[0] == NULL) {
		puts("Erro ao carregar o arquivo \"resources/player4.png\"");
		exit(0);
	}

	player->delta_x = LARGURA_SPRITES_PLAYER/2;
}

void finaliza_player (Player* player) {
	finaliza_sprites_player(player);
}

void desenha_player (Player* player) {
	int flags = 0;
  
	if (player->direcao_atual == DIREITA)
		flags = ALLEGRO_FLIP_HORIZONTAL;

	al_draw_scaled_bitmap(player->sprites[0],
						  0, 
						  0,
						  al_get_bitmap_width(player->sprites[0]),
						  al_get_bitmap_height(player->sprites[0]),

						  player->posicao_x - player->delta_x,
						  player->posicao_y,
						  LARGURA_SPRITES_PLAYER,
						  ALTURA_SPRITES_PLAYER,

						  flags);

}

ALLEGRO_BITMAP* inicializa_sprites_player (Player* player, const char *filename, int largura, int altura) {
	ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

	resized_bmp = al_create_bitmap(largura, altura);

	loaded_bmp = al_load_bitmap(filename);

	prev_target = al_get_target_bitmap();
	al_set_target_bitmap(resized_bmp);

	if (loaded_bmp == NULL) {
		puts("Erro ao carregar o arquivo \"resources/player4.png\"");
		exit(0);
	}

	// al_draw_scaled_bitmap(loaded_bmp,

	// 					  155,
	// 					  posicao_x,
	// 					  al_get_bitmap_width(loaded_bmp),
	// 					  al_get_bitmap_height(loaded_bmp),

	// 					  320,
	// 					  240,
	// 					  largura,
	// 					  altura,

	// 					  0);

    al_set_target_bitmap(prev_target);
  	al_destroy_bitmap(loaded_bmp);

	return resized_bmp;	  
}

void finaliza_sprites_player (Player* player) {
	al_destroy_bitmap(player->sprites[0]);
}

void move_player (Player* player, DIRECAO direcao) {
	if (direcao == ESQUERDA) {
		player->posicao_x -= DISTANCIA_PASSO_PLAYER;
		player->direcao_atual = ESQUERDA;
	}
	if (direcao == DIREITA) {
		player->posicao_x += DISTANCIA_PASSO_PLAYER;
		player->direcao_atual = DIREITA;
	}
}

int get_posicao_x_max_player (Player* player){
	return player->posicao_x + player->delta_x;
}

int get_posicao_x_min_player (Player* player){
	return player->posicao_x - player->delta_x;
}

int get_posicao_x_centro_player (Player* player){
	return player->posicao_x - 3;
}