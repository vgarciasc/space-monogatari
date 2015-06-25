#ifndef PROJETIL_H
#define PROJETIL_H

#include <stdio.h>
#include <stdlib.h>

#include "player.h"

#define VELOCIDADE_PROJETIL 10

struct Projetil {
	double posicao_x, posicao_y;
	DIRECAO direcao;

	int altura_sprite, largura_sprite;
	int cooldown;
	ALLEGRO_BITMAP* sprite;
};

void cria_projetil (Projetil* projetil, double posicao_x, double posicao_y, DIRECAO direcao);

void desenha_projetil (Projetil* projetil);

void move_projetil (Projetil* projetil);

void finaliza_projetil (Projetil* projetil);

void inicializa_sprite_projetil (Projetil* projetil);

void copy_projetil (Projetil* destino, Projetil* origem);

#endif