#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "game.h"
#include "player.h"

void inicializa_player (Player* player, double posicao_x, double posicao_y) {
	player->posicao_x = posicao_x;
	player->posicao_y = posicao_y;
	player->projetil_cooldown = PROJETIL_COOLDOWN;

	player->sprites[0] = al_load_bitmap("resources/player4.png");

	if (player->sprites[0] == NULL) {
		puts("Erro ao carregar o arquivo \"resources/player4.png\"");
		exit(0);
	}

	player->sprites[0] = al_load_bitmap("resources/player4.png");

	if (player->sprites[0] == NULL) {
		puts("Erro ao carregar o arquivo \"resources/player4.png\"");
		exit(0);
	}

	player->delta_x = LARGURA_SPRITES_PLAYER/2;
	player->delta_y = ALTURA_SPRITES_PLAYER/2;
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

						  player->posicao_x ,
						  player->posicao_y ,
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

void colisao_player_vs_projetil (Jogo *jogo) {
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {
		for (int j = 0; j < COLUNAS_TROPA; j++) {
			for (int v = 0; v < LINHAS_TROPA; v++) {
				if ((!(jogo->projetil_stack[i].posicao_x > get_posicao_x_max_player(&jogo->player)
					|| jogo->projetil_stack[i].posicao_y > get_posicao_y_max_player(&jogo->player)
					|| jogo->projetil_stack[i].posicao_y + jogo->projetil_stack[i].altura_sprite < get_posicao_y_max_player(&jogo->player)
					|| jogo->projetil_stack[i].posicao_x + jogo->projetil_stack[i].largura_sprite < get_posicao_x_min_player(&jogo->player)))) {

						copy_projetil (&jogo->projetil_stack[i], &jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						desenha_projetil (&jogo->projetil_stack[i]);
						finaliza_projetil (&jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						jogo->numero_de_projeteis--;

						puts("A");

						return;
				}
			}
		}
	}
}

int get_posicao_x_min_player (Player* player){
	return player->posicao_x;
}

int get_posicao_x_max_player (Player* player){
	return player->posicao_x + al_get_bitmap_width(player->sprites[0]);
}

int get_posicao_y_min_player (Player* player){
	return player->posicao_y;
}

int get_posicao_y_max_player (Player* player){
	return player->posicao_y + al_get_bitmap_height(player->sprites[0]);
}

int get_posicao_x_centro_player (Player* player){
	return player->posicao_x - 3;
}
