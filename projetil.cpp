#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "projetil.h"

void cria_projetil (Projetil* projetil, double posicao_x, double posicao_y, DIRECAO direcao) {
	projetil->posicao_x = posicao_x;
	projetil->posicao_y = posicao_y;
	projetil->direcao = direcao;

	inicializa_sprite_projetil (projetil);

	projetil->altura_sprite = al_get_bitmap_height(projetil->sprite);
	projetil->largura_sprite = al_get_bitmap_width(projetil->sprite);

	desenha_projetil (projetil);
}

void desenha_projetil (Projetil* projetil) {
//funcao pode ser reutilizada pros aliens
	int flags = 0;

	if (projetil->direcao == BAIXO) {
		flags = ALLEGRO_FLIP_VERTICAL;
		al_draw_bitmap (projetil->sprite,
					projetil->posicao_x, 
					projetil->posicao_y,
					flags);
	}

	if (projetil->direcao == CIMA)
		al_draw_tinted_bitmap(projetil->sprite, al_map_rgba_f(1, 0.2, 0, 1), projetil->posicao_x,
													projetil->posicao_y, flags);


}

void move_projetil (Projetil* projetil) {
	if (projetil->direcao == CIMA)
		projetil->posicao_y -= VELOCIDADE_PROJETIL;

	if (projetil->direcao == BAIXO)
		projetil->posicao_y += VELOCIDADE_PROJETIL;
}

void finaliza_projetil (Projetil* projetil) {
	al_destroy_bitmap(projetil->sprite);
}

void inicializa_sprite_projetil (Projetil* projetil) {
	projetil->sprite = al_load_bitmap("resources/projetil.png");

	if (projetil->sprite == NULL) {
		puts("Erro ao carregar o arquivo resources/projetil.png");
		exit(0);
	}
}

void copy_projetil (Projetil* destino, Projetil* origem) {
	destino->direcao = origem->direcao;
	destino->posicao_x = origem->posicao_x;
	destino->posicao_y = origem->posicao_y;
}
