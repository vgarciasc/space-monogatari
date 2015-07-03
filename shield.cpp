#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

#include "game.h"
#include "shield.h"

void inicializa_shield (Shield* shield, double posicao_x, double posicao_y) {
	shield->posicao_x = posicao_x;
	shield->posicao_y = posicao_y;

	if (SCALE_BITMAPS) {
		shield->largura = LARGURA_SHIELD*(LARGURA_DISPLAY/640.0);
		shield->altura = ALTURA_SHIELD*(ALTURA_DISPLAY/480.0);
	}
	else {
		shield->largura = LARGURA_SHIELD;
		shield->altura = ALTURA_SHIELD;
	}

	inicializa_bitmap_shield (shield);

	for (int i = 0; i < PARTES_X; i++)
		for (int j = 0; j < PARTES_Y; j++)
			shield->part_state[i][j] = INTEIRO;
}

void desenha_shield (Shield* shield) {
	for (int i = 0; i < PARTES_X; i++) {
		for (int j = 0; j < PARTES_Y; j++) {
			if (shield->part_state[i][j] == INTEIRO) {
				al_draw_bitmap_region(shield->bitmap_inteiro,
			   						 (shield->largura / PARTES_X)*i,
			   						 (shield->altura / PARTES_Y)*j,
			   						 (shield->largura / PARTES_X),
			   						 (shield->altura / PARTES_Y),
			   						 shield->posicao_x + (shield->largura / PARTES_X)*i, 
			   						 shield->posicao_y + (shield->altura / PARTES_Y)*j, 
			   						 0);
			}

			else if (shield->part_state[i][j] == DANIFICADO) {
				al_draw_bitmap_region(shield->bitmap_danificado,
			   						 (shield->largura / PARTES_X)*i,
			   						 (shield->altura / PARTES_Y)*j,
			   						 (shield->largura / PARTES_X),
			   						 (shield->altura / PARTES_Y),
			   						 shield->posicao_x + (shield->largura / PARTES_X)*i, 
			   						 shield->posicao_y + (shield->altura / PARTES_Y)*j, 
			   						 0);
			}
		}
	}
}

void inicializa_bitmap_shield (Shield* shield) {
	ALLEGRO_BITMAP* resized_bmp, *loaded_bmp, *prev_target;
	prev_target = al_get_target_bitmap();

	shield->bitmap_inteiro = al_create_bitmap(shield->largura, shield->altura);
	loaded_bmp = al_load_bitmap("resources/shield_inteiro2.png");
	if (loaded_bmp == NULL) {
		puts("Erro ao carregar o arquivo \"resources/shield_inteiro2.png\"");
		exit(0);
	}

	al_set_target_bitmap(shield->bitmap_inteiro);
	al_draw_scaled_bitmap(loaded_bmp,
						  0, 0,
						  al_get_bitmap_width(loaded_bmp),
						  al_get_bitmap_height(loaded_bmp),
						  0, 0,
						  shield->largura,
						  shield->altura,
						  0);

	shield->bitmap_danificado = al_create_bitmap(shield->largura, shield->altura);
	loaded_bmp = al_load_bitmap("resources/shield_danificado2.png");
	if (loaded_bmp == NULL) {
		puts("Erro ao carregar o arquivo \"resources/shield_danificado2.png\"");
		exit(0);
	}

	al_set_target_bitmap(shield->bitmap_danificado);
	al_draw_scaled_bitmap(loaded_bmp,
						  0, 0,
						  al_get_bitmap_width(loaded_bmp),
						  al_get_bitmap_height(loaded_bmp),
						  0, 0,
						  shield->largura,
						  shield->altura,
						  0);

	al_destroy_bitmap(loaded_bmp);
	al_set_target_bitmap(prev_target);
}

void colisao_shield_vs_projetil (Jogo *jogo) {
    for (int k = 0; k < jogo->numero_shields; k++) {
		for (int i = 0; i < jogo->numero_de_projeteis; i++) {
			for (int j = 0; j < PARTES_X; j++) {
				for (int v = 0; v < PARTES_Y; v++) {
					if ((!(get_posicao_x_min_projetil(&jogo->conjunto_projeteis[i]) > get_posicao_x_max_part_n(&jogo->shields[k], j)
						|| get_posicao_y_min_projetil(&jogo->conjunto_projeteis[i]) > get_posicao_y_max_part_n(&jogo->shields[k], v)
						|| get_posicao_y_max_projetil(&jogo->conjunto_projeteis[i]) < get_posicao_y_min_part_n(&jogo->shields[k], v)
						|| get_posicao_x_max_projetil(&jogo->conjunto_projeteis[i]) < get_posicao_x_min_part_n(&jogo->shields[k], j)))
						&& jogo->shields[k].part_state[j][v] != DESTRUIDO) {

							copy_projetil (&jogo->conjunto_projeteis[i], &jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);
							desenha_projetil (&jogo->conjunto_projeteis[i]);
							finaliza_projetil (&jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);
							jogo->numero_de_projeteis--;

							if (jogo->shields[k].part_state[j][v] == INTEIRO)
								jogo->shields[k].part_state[j][v] = DANIFICADO;
							else if (jogo->shields[k].part_state[j][v] == DANIFICADO)
								jogo->shields[k].part_state[j][v] = DESTRUIDO;

							return;
					}
				}
			}
		}
	}
}

double get_posicao_x_min_part_n (Shield* shield, int n) {
	return shield->posicao_x + (shield->largura / PARTES_X)*n;
}

double get_posicao_y_min_part_n (Shield* shield, int n) {
	return shield->posicao_y + (shield->altura / PARTES_Y)*n;
}

double get_posicao_x_max_part_n (Shield* shield, int n) {
	return shield->posicao_x + (shield->largura / PARTES_X)*(n+1);
}

double get_posicao_y_max_part_n (Shield* shield, int n) {
	return shield->posicao_y + (shield->altura / PARTES_Y)*(n+1);
}
