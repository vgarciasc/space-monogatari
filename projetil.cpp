#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game.h"
#include "projetil.h"

void inicializa_projetil (Projetil* projetil, double posicao_x, double posicao_y, DIRECAO direcao) {
	projetil->posicao_x = posicao_x;
	projetil->posicao_y = posicao_y;
	projetil->direcao = direcao;
	projetil->velocidade = VELOCIDADE_PROJETIL*(LARGURA_DISPLAY)/640.0;

	inicializa_bitmap_projetil (projetil);

	if (SCALE_BITMAPS) {
		projetil->largura = LARGURA_PROJETIL*(LARGURA_DISPLAY/640.0);
		projetil->altura = ALTURA_PROJETIL*(ALTURA_DISPLAY/480.0);
	}
	else {
		projetil->largura = LARGURA_PROJETIL;
		projetil->altura = ALTURA_PROJETIL;
	}

	desenha_projetil (projetil);
}

void inicializa_bitmap_projetil (Projetil* projetil) {
	projetil->bitmap = al_load_bitmap("resources/projetil.png");

	if (projetil->bitmap == NULL) {
		puts("Erro ao carregar o arquivo \"resources/projetil.png\"");
		exit(0);
	}
}

void desenha_projetil (Projetil* projetil) {
	int flags = 0;

	if (projetil->direcao == BAIXO) {
		flags = ALLEGRO_FLIP_VERTICAL;
		al_draw_scaled_bitmap (projetil->bitmap,
							   0, 0,
							   al_get_bitmap_width(projetil->bitmap),
							   al_get_bitmap_height(projetil->bitmap),

							   projetil->posicao_x, 
							   projetil->posicao_y,
							   projetil->largura,
							   projetil->altura,

							   flags);
	}

	if (projetil->direcao == CIMA)
		al_draw_tinted_scaled_bitmap(projetil->bitmap, 
									 al_map_rgba_f(1, 0.2, 0, 1),
									 0, 0,
								     al_get_bitmap_width(projetil->bitmap),
								     al_get_bitmap_height(projetil->bitmap),

								     projetil->posicao_x, 
								     projetil->posicao_y,
								     projetil->largura,
								     projetil->altura,

								     flags);
}

void move_projetil (Projetil* projetil) {
	if (projetil->direcao == CIMA)
		projetil->posicao_y -= projetil->velocidade;

	if (projetil->direcao == BAIXO)
		projetil->posicao_y += projetil->velocidade;
}

void finaliza_projetil (Projetil* projetil) {
	al_destroy_bitmap(projetil->bitmap);
}

void copy_projetil (Projetil* destino, Projetil* origem) {
	destino->direcao = origem->direcao;
	destino->posicao_x = origem->posicao_x;
	destino->posicao_y = origem->posicao_y;
}

int get_posicao_x_min_projetil (Projetil* projetil) {
	return projetil->posicao_x;
}

int get_posicao_x_max_projetil (Projetil* projetil) {
	return projetil->posicao_x + projetil->largura;
}

int get_posicao_y_min_projetil (Projetil* projetil) {
	return projetil->posicao_y;
}

int get_posicao_y_max_projetil (Projetil* projetil) {
	return projetil->posicao_y + projetil->altura;
}