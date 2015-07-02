#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

struct Jogo;

struct Player {
	double posicao_x, posicao_y;
	double delta_x, delta_y;
	double largura, altura;

	ALLEGRO_BITMAP* bitmap;
	DIRECAO direcao_atual;

	int projetil_cooldown;
};

void inicializa_player (Player* player, double posicao_x, double posicao_y);

void finaliza_player (Player* player);

void desenha_player (Player* player);

void move_player (Player* player, DIRECAO direcao);

void colisao_player_vs_projetil (Jogo *jogo);

int get_posicao_x_min_player (Player* player);

int get_posicao_x_max_player (Player* player);

int get_posicao_y_min_player (Player* player);

int get_posicao_y_max_player (Player* player);

int get_posicao_x_centro_player (Player* player);

bool verifica_se_ponto_dentro(float x, float y, Player* player);

float calcular_area(float*, float *, float *);

#endif
