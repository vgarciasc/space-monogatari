#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "game.h"
#include "shield.h"

void inicializa_shield (Shield* shield, double posicao_x, double posicao_y) {
	shield->posicao_x = posicao_x;
	shield->posicao_y = posicao_y;

	shield->bitmap_inteiro = al_load_bitmap("resources/shield_inteiro.jpg");
	if (shield->bitmap_inteiro == NULL) {
		puts("Erro ao carregar o arquivo \"resources/shield_inteiro.jpg\"");
		exit(0);
	}

	shield->bitmap_danificado = al_load_bitmap("resources/shield_danificado.png");
	if (shield->bitmap_danificado == NULL) {
		puts("Erro ao carregar o arquivo \"resources/shield_danificado.png\"");
		exit(0);
	}

	for (int i = 0; i < PARTES_X; i++) {
		for (int j = 0; j < PARTES_Y; j++) {
			if (i == 1)
				shield->part_state[i][j] = DANIFICADO;
			else
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

void colisao_shield_vs_projetil (Jogo *jogo, Shield *shield) {
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {
		for (int j = 0; j < PARTES_Y; j++) {
			for (int v = 0; v < PARTES_X; v++) {
				if (!(jogo->projetil_stack[i].posicao_x > shield->posicao_x + (LARGURA_SHIELD / PARTES_X)*(v+1)
			|| jogo->projetil_stack[i].posicao_y > shield->posicao_y + (ALTURA_SHIELD / PARTES_Y)*(j)
			|| jogo->projetil_stack[i].posicao_y + jogo->projetil_stack[i].altura_sprite < shield->posicao_y + (ALTURA_SHIELD / PARTES_Y)*j+1
			|| jogo->projetil_stack[i].posicao_x + jogo->projetil_stack[i].largura_sprite < LARGURA_SHIELD / PARTES_X)*(v)) {

						copy_projetil (&jogo->projetil_stack[i], &jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						desenha_projetil (&jogo->projetil_stack[i]);
						finaliza_projetil (&jogo->projetil_stack[jogo->numero_de_projeteis-1]);
						jogo->numero_de_projeteis--;

						if (shield->part_state[j][v] == INTEIRO)
							shield->part_state[j][v] = DANIFICADO;
						else if (shield->part_state[j][v] == DANIFICADO)
							shield->part_state[j][v] = DESTRUIDO;

						// jogo->hud.score += PONTOS_MOTHERSHIP;
						// jogo->reinicia_mothershipp.segundos++;
						// reinicia_mothership(&jogo->mothership);

						return;
				}
			}
		}
	}
}
