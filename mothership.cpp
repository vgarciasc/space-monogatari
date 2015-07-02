#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game.h"
#include "mothership.h"

void inicializa_mothership (Mothership *mothership, Jogo *jogo) {
	mothership->bitmap = al_load_bitmap("resources/mothership.png");
	if (mothership->bitmap == NULL) {
		puts("Erro ao carregar o arquivo \"resources/mothership.png\"");
		exit(0);
	}

	if (SCALE_BITMAPS) {
		mothership->largura = LARGURA_MOTHERSHIP*(LARGURA_DISPLAY/640.0);
		mothership->altura = ALTURA_MOTHERSHIP*(ALTURA_DISPLAY/480.0);
	}
	else {
		mothership->largura = LARGURA_MOTHERSHIP;
		mothership->altura = ALTURA_MOTHERSHIP;
	}

	mothership->delta_x = mothership->largura/6;
	mothership->delta_y = mothership->altura/6;

	mothership->direcao = DIREITA;
	mothership->distancia_passo = VELOCIDADE_MOTHERSHIP;
	mothership->frequencia = FREQUENCIA_MOTHERSHIP;

	reinicia_mothership(mothership);
	inicializar_timer_mothership(mothership);
}

void reinicia_mothership (Mothership *mothership) {
	mothership->posicao_x = -mothership->largura;
	mothership->posicao_y = (mothership->altura);
	mothership->ativo = false;
}

void desenha_mothership (Mothership *mothership) {
	if (autoriza_mothership(mothership) || mothership->ativo) {
		al_draw_scaled_bitmap(mothership->bitmap,
							  0, 0,
							  al_get_bitmap_width(mothership->bitmap),
							  al_get_bitmap_height(mothership->bitmap),

							  mothership->posicao_x,
							  mothership->posicao_y,
							  mothership->largura,
							  mothership->altura,

							  0);
	 	
	 	if (mothership->direcao == DIREITA && mothership->posicao_x > LARGURA_DISPLAY) {
		 		reinicia_mothership (mothership);
			    return;
		 	}
		if (mothership->direcao == ESQUERDA && mothership->posicao_x < 0) {
		 		reinicia_mothership (mothership);
			    return;
		 	}	 	

	 	movimenta_mothership (mothership);
	}
}

void movimenta_mothership (Mothership *mothership) {
	if (mothership->direcao == DIREITA)
		mothership->posicao_x += mothership->distancia_passo;
	if (mothership->direcao == ESQUERDA)
		mothership->posicao_x -= mothership->distancia_passo;
}


void inicializar_timer_mothership(Mothership *mothership) {
    mothership->event_queue = al_create_event_queue();
    mothership->timer = al_create_timer(mothership->frequencia);

    al_register_event_source(mothership->event_queue, al_get_timer_event_source(mothership->timer));
	al_start_timer(mothership->timer);
}


void finaliza_mothership(Mothership *mothership){
	al_destroy_bitmap(mothership->bitmap);
}


bool autoriza_mothership(Mothership *mothership){
	if (!al_is_event_queue_empty(mothership->event_queue)){
	    ALLEGRO_EVENT evento;
        al_wait_for_event(mothership->event_queue, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER && !(mothership->ativo)){
           	mothership->ativo = true;
           	return true;
        }   	
	}
	
	return false;
}

void colisao_mothership_vs_projetil (Jogo *jogo) {
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {
		if (!(get_posicao_x_min_projetil(&jogo->conjunto_projeteis[i]) > get_posicao_x_max_mothership(&jogo->mothership)
			|| get_posicao_y_min_projetil(&jogo->conjunto_projeteis[i]) > get_posicao_y_max_mothership(&jogo->mothership)
			|| get_posicao_y_max_projetil(&jogo->conjunto_projeteis[i]) < get_posicao_y_min_mothership(&jogo->mothership)
			|| get_posicao_x_max_projetil(&jogo->conjunto_projeteis[i]) < get_posicao_x_min_mothership(&jogo->mothership))) {

				copy_projetil (&jogo->conjunto_projeteis[i], &jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);
				desenha_projetil (&jogo->conjunto_projeteis[i]);
				finaliza_projetil (&jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);
				jogo->numero_de_projeteis--;

				jogo->hud.score += PONTOS_MOTHERSHIP;
				reinicia_mothership(&jogo->mothership);

				return;
		}
	}
}

int get_posicao_x_max_mothership (Mothership *mothership) {
	return mothership->posicao_x + mothership->largura - mothership->delta_x;
}

int get_posicao_x_min_mothership (Mothership *mothership) {
	return mothership->posicao_x + mothership->delta_x;
}

int get_posicao_y_max_mothership (Mothership *mothership) {
	return mothership->posicao_y + mothership->altura - mothership->delta_y;
}

int get_posicao_y_min_mothership (Mothership *mothership) {
	return mothership->posicao_y + mothership->delta_y;
}
