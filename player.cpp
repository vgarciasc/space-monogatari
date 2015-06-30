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

						  player->posicao_x - player->delta_x,
						  player->posicao_y + player->delta_y,
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
				if((verificar_se_ponto_esta_dentro( jogo->projetil_stack[i].posicao_x,
												   jogo->projetil_stack[i].posicao_y + jogo->projetil_stack[i].altura_sprite,
												   &jogo->player) 	) ||
				(verificar_se_ponto_esta_dentro( jogo->projetil_stack[i].posicao_x + jogo->projetil_stack[i].largura_sprite,
												       jogo->projetil_stack[i].posicao_y + jogo->projetil_stack[i].altura_sprite,
												       &jogo->player)) 	)
				{
						copy_projetil (&jogo->projetil_stack[i], &jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						desenha_projetil (&jogo->projetil_stack[i]);
						finaliza_projetil (&jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						jogo->numero_de_projeteis--;
						jogo->hud.lives--;

						return;


				}
			}
		}
	}
}
/*
 *
 *
 * AQUI VAI FICAR A APROXIMAÇÃO PARA TRIANGULO
 *
 *
 */
bool verificar_se_ponto_esta_dentro(float x, float y, Player* player){

	float coordenada_1[2]={get_posicao_x_min_player(player), get_posicao_y_max_player(player)};
	float coordenada_2[2]={get_posicao_x_max_player(player), get_posicao_y_max_player(player)};
	float coordenada_3[2]={get_posicao_x_min_player(player)+LARGURA_SPRITES_PLAYER/2, get_posicao_y_min_player(player)};
	float coordenada_4[2]={x,y};

	if( calcular_area(coordenada_1,coordenada_2,coordenada_3) == calcular_area(coordenada_1,coordenada_2,coordenada_4)
																+ calcular_area(coordenada_1,coordenada_3, coordenada_4)
																+ calcular_area(coordenada_2, coordenada_3, coordenada_4)) {
		return true;
	}
	else
	return false;
}

float calcular_area(float coordenada1[], float coordenada2[], float coordenada3[]){
	float x = coordenada1[0]*coordenada2[1] + coordenada1[1]*coordenada3[0] + coordenada2[0]*coordenada3[1] - coordenada2[1]*coordenada3[0] - coordenada1[0]*coordenada3[1] - coordenada1[1]*coordenada2[0];
	if(x>=0)
		return x;
	else
		return -x;
}




/*
 * FIM DA APROXIMAÇÃO
 */
int get_posicao_x_min_player (Player* player){
	return player->posicao_x - player->delta_x;
}

int get_posicao_x_max_player (Player* player){
	return player->posicao_x + player->delta_x;
}

int get_posicao_y_min_player (Player* player){
	return player->posicao_y + player->delta_y + 4;
}

int get_posicao_y_max_player (Player* player){
	return player->posicao_y + 3*player->delta_y;
}

int get_posicao_x_centro_player (Player* player){
	return player->posicao_x - 3;
}
