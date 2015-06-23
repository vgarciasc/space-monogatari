#ifndef PROJETIL_H
#define PROJETIL_H

#include <stdio.h>
#include <stdlib.h>

#include "player.h"

#define VELOCIDADE_PROJETIL 5

struct Projetil {
	int posicao_x, posicao_y;
	DIRECAO direcao;

	ALLEGRO_BITMAP* sprite;
};

void cria_projetil (Projetil* projetil, int posicao_x, int posicao_y, DIRECAO direcao);

void desenha_projetil (Projetil* projetil);

void move_projetil (Projetil* projetil);

void finaliza_projetil (Projetil* projetil);

void inicializa_sprite_projetil (Projetil* projetil);

void copy_projetil (Projetil* destino, Projetil* origem);

#endif