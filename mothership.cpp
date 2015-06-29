#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game.h"
#include "mothership.h"

void desenha_mothership (Mothership *mothership) {

	if (autoriza_mothership(mothership) || mothership->ativo) {
		al_draw_scaled_bitmap(mothership->imagem,
							  0, 
							  0,
							  al_get_bitmap_width(mothership->imagem),
							  al_get_bitmap_height(mothership->imagem),

							  mothership->posicao_x,
							  mothership->posicao_y,
							  LARGURA_SPRITES_MOTHERSHIP,
							  ALTURA_SPRITES_MOTHERSHIP,

							  0);
	 	
	 	if (mothership->posicao_x >= mothership->largura_tela) {
	 		reinicia_mothership (mothership);
		    return;
	 	}
	 	
	 	movimenta_mothership (mothership);
	}
}

void movimenta_mothership (Mothership *mothership) {
	mothership->posicao_x += VELOCIDADE_MOTHERSHIP;
}

void reinicia_mothership (Mothership *mothership) {
	mothership->posicao_x = -LARGURA_SPRITES_MOTHERSHIP;
	mothership->posicao_y = (ALTURA_SPRITES_MOTHERSHIP + mothership->delta_y);
	mothership->ativo = false;
}

void inicializa_mothership (Mothership *mothership, Jogo *jogo) {
	mothership->imagem = al_load_bitmap("resources/mothership.png");
	if (mothership->imagem == NULL) {
		puts("Erro ao carregar o arquivo \"resources/mothership.png\"");
		exit(0);
	}

	mothership->largura_tela = jogo->largura;

	mothership->delta_x = (LARGURA_SPRITES_MOTHERSHIP)/3;
	mothership->delta_y = (ALTURA_SPRITES_MOTHERSHIP)/6;

	reinicia_mothership(mothership);
	inicializar_timer_mothership(mothership);
}

void inicializar_timer_mothership(Mothership *mothership) {
    mothership->fila_evento = al_create_event_queue();
    mothership->tempo = al_create_timer(FREQUENCIA_MOTHERSHIP);

    al_register_event_source(mothership->fila_evento, al_get_timer_event_source(mothership->tempo));
	al_start_timer(mothership->tempo);
}


void finaliza_mothership(Mothership *mothership){
	al_destroy_bitmap(mothership->imagem);
}


bool autoriza_mothership(Mothership *mothership){
	if (!al_is_event_queue_empty(mothership->fila_evento)){
	    ALLEGRO_EVENT evento;
        al_wait_for_event(mothership->fila_evento, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER && !(mothership->ativo)){
           	mothership->ativo = true;
           	return true;
        }   	
	}
	
	return false;
}

int get_posicao_x_max_mothership (Mothership *mothership) {
	return mothership->posicao_x + LARGURA_SPRITES_MOTHERSHIP - mothership->delta_x;
}

int get_posicao_x_min_mothership (Mothership *mothership) {
	return mothership->posicao_x + mothership->delta_x;
}

int get_posicao_y_max_mothership (Mothership *mothership) {
	return mothership->posicao_y + ALTURA_SPRITES_MOTHERSHIP - mothership->delta_y;
}

int get_posicao_y_min_mothership (Mothership *mothership) {
	return mothership->posicao_y + mothership->delta_y;
}



void colisao_mothership_vs_projetil (Jogo *jogo) {
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {
		if (!(jogo->projetil_stack[i].posicao_x > get_posicao_x_max_mothership(&jogo->mothership)
			|| jogo->projetil_stack[i].posicao_y > get_posicao_y_max_mothership(&jogo->mothership)
			|| jogo->projetil_stack[i].posicao_y + jogo->projetil_stack[i].altura_sprite < get_posicao_y_min_mothership(&jogo->mothership)
			|| jogo->projetil_stack[i].posicao_x + jogo->projetil_stack[i].largura_sprite < get_posicao_x_min_mothership(&jogo->mothership))) {

				copy_projetil (&jogo->projetil_stack[i], &jogo->projetil_stack[jogo->numero_de_projeteis-1]);
				desenha_projetil (&jogo->projetil_stack[i]);
				finaliza_projetil (&jogo->projetil_stack[jogo->numero_de_projeteis-1]);

				jogo->numero_de_projeteis--;
				jogo->hud.score += PONTOS_MOTHERSHIP;
				reinicia_mothership(&jogo->mothership);

				return;
		}
	}
}