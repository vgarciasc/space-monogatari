#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

struct Jogo;

struct Player {
	double posicao_x, posicao_y;
	double delta_x, delta_y;
	DIRECAO direcao_atual;

	int projetil_cooldown;

	int sprite_atual;
	ALLEGRO_BITMAP* sprites[10];
};

void inicializa_player (Player* player, double posicao_x, double posicao_y);

void finaliza_player (Player* player);

void desenha_player (Player* player);

ALLEGRO_BITMAP* inicializa_sprites_player (Player* player, const char *filename, int largura, int altura);

void finaliza_sprites_player (Player* player);

void move_player (Player* player, DIRECAO direcao);

void colisao_player_vs_projetil (Jogo *jogo);

int get_posicao_x_min_player (Player* player);

int get_posicao_x_max_player (Player* player);

int get_posicao_y_min_player (Player* player);

int get_posicao_y_max_player (Player* player);

int get_posicao_x_centro_player (Player* player);

/*
 *
 *
 * AQUI VAI FICAR A APROXIMAÇÃO PARA TRIANGULO
 *
 *
 */


float calcular_area(float*, float *, float *);
bool verificar_se_ponto_esta_dentro(float x, float y, Player* player);


/*
 * FIM DA APROXIMAÇÃO
 */

#endif
