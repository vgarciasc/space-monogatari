#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "menu.h"

void inicializa_menu (Menu* menu) {
  menu->numero_de_botoes = 2;
  menu->event_queue = NULL;
  menu->timer = NULL;
  menu->botao_selecionado = 1;
  
  inicializa_timer_menu (menu);
  inicializa_event_queue_menu(menu);

	menu->font = al_load_font("resources/verdana.ttf", 48, 0);
	if (menu->font == NULL) {
		puts("Erro ao carregar o arquivo resources/verdana.ttf");
		exit(0);
	}
}

void desenha_fundo_menu () {
	al_clear_to_color(al_map_rgb(20,20,12));
}

void desenha_menu (Menu* menu) {
	desenha_fundo_menu ();
    al_draw_text(menu->font, al_map_rgb(255,255,255), 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "PAUSE");
}

void loop_menu (Menu* menu) {
  al_start_timer(menu->timer);
  bool doexit = false;
  bool redraw = true;

  while (!doexit) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(menu->event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
    	}
    	
    	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	break;
      	}

      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        	switch(ev.keyboard.keycode) {
            	case ALLEGRO_KEY_UP: 
            		  if (menu->botao_selecionado == 1)
                    menu->botao_selecionado = menu->numero_de_botoes - 1;
                  else
                    menu->botao_selecionado--;
                	break;
 
            	case ALLEGRO_KEY_DOWN:
               		if (menu->botao_selecionado == menu->numero_de_botoes)
                    menu->botao_selecionado = 1;
                  else
                    menu->botao_selecionado++;
               		break;

              case ALLEGRO_KEY_Z:
                  if (menu->botao_selecionado == 1)
                    doexit = true;
                  if (menu->botao_selecionado == 2)
                    doexit = true;
                  break;

              case ALLEGRO_KEY_ESCAPE:
                  puts("A");
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