#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "game.h"
#include "nave_mae.h"

void desenha_nave(NaveMae *nave,Jogo *jogo, Projetil *projetil){
	if(autoriza_nave(nave,jogo) || nave->status==1){
	 	 al_draw_bitmap(nave->imagem, nave->posicao_x,nave->posicao_y,0);
	 	 if(nave->posicao_x>=jogo->largura){
	 		 reinicia_nave(nave);
	 		 return;
	 	 }
	 	 detecta_colisao(nave, jogo);
	 	 movimenta_nave(nave);

	}

}
void movimenta_nave(NaveMae *nave){
	nave->posicao_x +=nave->velocidade;
}
void reinicia_nave(NaveMae *nave){
	nave->posicao_x = -35;
	nave->posicao_y = 0;
	nave->status = 0;
}
void inicializa_nave(NaveMae *nave){
	nave->imagem = al_load_bitmap("resources/nave.png");
	if (nave->imagem == NULL) {
			puts("Erro ao carregar o arquivo resources/nave.png");
			exit(0);
	}
	nave->velocidade=3;
	nave->largura=35;
	nave->altura=35;
	reinicia_nave(nave);
}
void finaliza_nave(NaveMae *nave){
	al_destroy_bitmap(nave->imagem);
}
void detecta_colisao(NaveMae *nave, Jogo *jogo){
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {

		if(!(jogo->projetil_stack[i].posicao_x > nave->posicao_x + nave->largura ||
				jogo->projetil_stack[i].posicao_y > nave->posicao_y + nave->altura  ||
				jogo->projetil_stack[i].posicao_y + jogo->projetil_stack[i].altura_sprite< nave->posicao_y ||
				jogo->projetil_stack[i].posicao_x + jogo->projetil_stack[i].largura_sprite < nave->posicao_x))
		{

				reinicia_nave(nave);

				return ;
		}

	}

}
int autoriza_nave(NaveMae *nave, Jogo *jogo){
	if(((jogo->segundos)/FPS)%10 == 0){
		nave->status=1;
		return 1;
	}
	else
		return 0;
}
