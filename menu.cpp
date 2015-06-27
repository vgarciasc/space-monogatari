#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "menu.h"

const ALLEGRO_COLOR MARROM_CLARO = al_map_rgb(247, 180, 109);
const ALLEGRO_COLOR BRANCO = al_map_rgb(255, 255, 255);

void inicializa_menu (Menu* menu) {
  //botoes funcionam com logica de array (primeiro botao 0, segundo botao 1, etc)
  menu->numero_de_botoes = 1;
  menu->event_queue = NULL;
  menu->timer = NULL;
  menu->botao_selecionado = 0;
  
  inicializa_timer_menu (menu);
  inicializa_event_queue_menu(menu);

	menu->font_title = al_load_font("resources/verdana.ttf", 48, 0);
  menu->font_items = al_load_font("resources/verdana.ttf", 24, 0);

	if (menu->font_title == NULL || menu->font_items == NULL) {
		puts("Erro ao carregar o arquivo resources/verdana.ttf");
		exit(0);
	}
}

void desenha_fundo_menu () {
	al_clear_to_color(al_map_rgb(20,20,12));
}

void desenha_menu (Menu* menu) {
	desenha_fundo_menu ();
  al_draw_text(menu->font_title, al_map_rgb(255,255,255), 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "PAUSE");

  if (menu->botao_selecionado == 0)
    al_draw_text(menu->font_items, al_map_rgb(247,150,220), 640/2, 240, ALLEGRO_ALIGN_CENTRE, "RESUME");
  else
    al_draw_text(menu->font_items, al_map_rgb(255,255,255), 640/2, 240, ALLEGRO_ALIGN_CENTRE, "RESUME");
  
  if (menu->botao_selecionado == 1)
    al_draw_text(menu->font_items, al_map_rgb(150,150,220), 640/2, 240 + 30, ALLEGRO_ALIGN_CENTRE, "EXIT GAME");
  else
    al_draw_text(menu->font_items, al_map_rgb(255,255,255), 640/2, 240 + 30, ALLEGRO_ALIGN_CENTRE, "EXIT GAME");
}

bool loop_menu (Menu* menu) {
  al_start_timer(menu->timer);
  bool doexit = false;
  bool redraw = true;

  while (!doexit) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(menu->event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
      redraw = true;
    }
    	
    	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	break;
      	}

      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        	switch(ev.keyboard.keycode) {
            	case ALLEGRO_KEY_UP: 
            		  if (menu->botao_selecionado == 0) {
                    menu->botao_selecionado = menu->numero_de_botoes;
                  }
                  else {
                    menu->botao_selecionado--;
                	}
                  break;
 
            	case ALLEGRO_KEY_DOWN:
               		if (menu->botao_selecionado == menu->numero_de_botoes) {
                    menu->botao_selecionado = 0;
                  }
                  else {
                    menu->botao_selecionado++;
               		}
                  break;

              case ALLEGRO_KEY_Z:
                  if (menu->botao_selecionado == 0) {
                    doexit = true;
                    return false;
                  }
                  if (menu->botao_selecionado == 1) {
                    doexit = true;
                    return true;
                  }
                  break;

              case ALLEGRO_KEY_ESCAPE:
                  doexit = true;
                  break;
        }
    }
 
    	if (redraw && al_is_event_queue_empty(menu->event_queue)) {
        	redraw = false;

          desenha_menu(menu);

        	al_flip_display();
      	}
   }
}

void inicializa_event_queue_menu (Menu* menu) {
	menu->event_queue = al_create_event_queue();

	if(!menu->event_queue) {
		fprintf(stderr, "Falha em executar lista de eventos do menu!\n");
		exit(-1);
	}
  al_install_keyboard();
  al_register_event_source(menu->event_queue, al_get_keyboard_event_source());
  al_register_event_source(menu->event_queue, al_get_timer_event_source(menu->timer));
}

void inicializa_timer_menu (Menu* menu) {
	menu->timer = al_create_timer(1.0/FPS);

	if(!menu->timer){
		fprintf(stderr, "Falha em executar timer do menu!\n");
		exit(-1);
	}
}