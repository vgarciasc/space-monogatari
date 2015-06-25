#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define FPS 60

enum BOTAO { CONTINUE = 1, QUIT };

struct Menu {
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	int numero_de_botoes;
	int botao_selecionado;
};

void inicializa_menu (Menu* menu);

void desenha_fundo_menu ();

void desenha_menu (Menu* menu);

void loop_menu (Menu* menu);

void inicializa_event_queue_menu (Menu* menu);

void inicializa_timer_menu (Menu* menu);

#endif