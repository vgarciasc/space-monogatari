#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "game.h"
#include "shield.h"

void inicializa_shield (Shield* shield, double posicao_x, double posicao_y) {
	shield->posicao_x = posicao_x;
	shield->posicao_y = posicao_y;

	inicializa_sprite_shield (shield);

	for (int i = 0; i < PARTES_X; i++) {
		for (int j = 0; j < PARTES_Y; j++) {
			shield->part_state[i][j] = INTEIRO;
		}
	}	
}

void desenha_shield (Shield* shield) {
	for (int i = 0; i < PARTES_X; i++) {
		for (int j = 0; j < PARTES_Y; j++) {
			if (shield->part_state[i][j] == INTEIRO) {
				al_draw_bitmap_region(shield->bitmap_inteiro,
			   						 (LARGURA_SHIELD / PARTES_X)*i,
			   						 (ALTURA_SHIELD / PARTES_Y)*j,
			   						 (LARGURA_SHIELD / PARTES_X),
			   						 (ALTURA_SHIELD / PARTES_Y),
			   						 shield->posicao_x + (LARGURA_SHIELD / PARTES_X)*i, 
			   						 shield->posicao_y + (ALTURA_SHIELD / PARTES_Y)*j, 
			   						 0);
			}

			else if (shield->part_state[i][j] == DANIFICADO) {
				al_draw_bitmap_region(shield->bitmap_danificado,
			   						 (LARGURA_SHIELD / PARTES_X)*i,
			   						 (ALTURA_SHIELD / PARTES_Y)*j,
			   						 (LARGURA_SHIELD / PARTES_X),
			   						 (ALTURA_SHIELD / PARTES_Y),
			   						 shield->posicao_x + (LARGURA_SHIELD / PARTES_X)*i, 
			   						 shield->posicao_y + (ALTURA_SHIELD / PARTES_Y)*j, 
			   						 0);
			}
		}
	}
}

void inicializa_sprite_shield (Shield* shield) {
	ALLEGRO_BITMAP* resized_bmp, *loaded_bmp, *prev_target;
	prev_target = al_get_target_bitmap();

	shield->bitmap_inteiro = al_create_bitmap(LARGURA_SHIELD, ALTURA_SHIELD);
	loaded_bmp = al_load_bitmap("resources/shield_inteiro.png");
	if (loaded_bmp == NULL) {
		puts("Erro ao carregar o arquivo \"resources/shield_inteiro.png\"");
		exit(0);
	}
	al_set_target_bitmap(shield->bitmap_inteiro);
	al_draw_scaled_bitmap(loaded_bmp,
						  0, 0,
						  al_get_bitmap_width(loaded_bmp),
						  al_get_bitmap_height(loaded_bmp),
						  0, 0,
						  LARGURA_SHIELD,
						  ALTURA_SHIELD,
						  0);
	// al_destroy_bitmap(loaded_bmp);

	shield->bitmap_danificado = al_create_bitmap(LARGURA_SHIELD, ALTURA_SHIELD);
	loaded_bmp = al_load_bitmap("resources/shield_danificado.png");
	if (loaded_bmp == NULL) {
		puts("Erro ao carregar o arquivo \"resources/shield_danificado.png\"");
		exit(0);
	}
	al_set_target_bitmap(shield->bitmap_danificado);
	al_draw_scaled_bitmap(loaded_bmp,
						  0, 0,
						  al_get_bitmap_width(loaded_bmp),
						  al_get_bitmap_height(loaded_bmp),
						  0, 0,
						  LARGURA_SHIELD,
						  ALTURA_SHIELD,
						  0);

	al_destroy_bitmap(loaded_bmp);
	al_set_target_bitmap(prev_target);
}

void colisao_shield_vs_projetil (Jogo *jogo, Shield *shield) {
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {
		for (int j = 0; j < PARTES_X; j++) {
			for (int v = 0; v < PARTES_Y; v++) {
				if ((!(jogo->projetil_stack[i].posicao_x > get_posicao_x_max_part_n(shield, j)
					|| jogo->projetil_stack[i].posicao_y > get_posicao_y_max_part_n(shield, v)
					|| jogo->projetil_stack[i].posicao_y + jogo->projetil_stack[i].altura_sprite < get_posicao_y_min_part_n(shield, v)
					|| jogo->projetil_stack[i].posicao_x + jogo->projetil_stack[i].largura_sprite < get_posicao_x_min_part_n(shield, j)))
					&& shield->part_state[j][v] != DESTRUIDO) {

						copy_projetil (&jogo->projetil_stack[i], &jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						desenha_projetil (&jogo->projetil_stack[i]);
						finaliza_projetil (&jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						jogo->numero_de_projeteis--;

						if (shield->part_state[j][v] == INTEIRO)
							shield->part_state[j][v] = DANIFICADO;
						else if (shield->part_state[j][v] == DANIFICADO)
							shield->part_state[j][v] = DESTRUIDO;

						return;
				}
			}
		}
	}
}

double get_posicao_x_min_part_n (Shield* shield, int n) {
	return shield->posicao_x + (LARGURA_SHIELD / PARTES_X)*n;
}

double get_posicao_y_min_part_n (Shield* shield, int n) {
	return shield->posicao_y + (LARGURA_SHIELD / PARTES_X)*n;
}

double get_posicao_x_max_part_n (Shield* shield, int n) {
	return shield->posicao_x + (LARGURA_SHIELD / PARTES_X)*(n+1);
}

double get_posicao_y_max_part_n (Shield* shield, int n) {
	return shield->posicao_y + (LARGURA_SHIELD / PARTES_X)*(n+1);
}
