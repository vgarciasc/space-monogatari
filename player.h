#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#define DISTANCIA_PASSO 5

enum DIRECAO { ESQUERDA, DIREITA, CIMA, BAIXO };

struct Player {
	double posicao_x, posicao_y;
	double delta_x;
	DIRECAO direcao_atual;

	int projetil_cooldown;

	int sprite_atual;
	ALLEGRO_BITMAP* sprites[10];
};

void inicializa_player (Player* player, double posicao_x, double posicao_y);

void finaliza_player (Player* player);

void desenha_player (Player* player);

void inicializa_sprites_player (Player* player);

void finaliza_sprites_player (Player* player);

void move_player (Player* player, DIRECAO direcao);

int get_posicao_x_max_player (Player* player);

int get_posicao_x_min_player (Player* player);

int get_posicao_x_centro_player (Player* player);

#endif