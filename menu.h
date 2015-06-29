#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "config.h"

struct Menu {
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	ALLEGRO_FONT* font_title;
	ALLEGRO_FONT* font_items;
	int font_size;

	//Telas e Botões funcionam com lógica de array: o primeiro é 0, o segundo é 1, etc
	int numero_de_botoes[MAX_BOTOES];
	int botao_selecionado;

	TELA tela_selecionada;

	int new_game;

	bool key[N_KEYS];
};

void inicializa_menus (Menu* menu);

void desenha_fundo_menu_pause ();

void desenha_menu_pause (Menu* menu);

bool loop_menu (Menu* menu, TELA tela);

void seleciona_nova_tela (Menu* menu, TELA tela);

void navega_botoes (Menu* menu, DIRECAO direcao);

void inicializa_event_queue_menu_pause (Menu* menu);

void inicializa_timer_menu_pause (Menu* menu);

#endif