#ifndef NAVE_MAE_H
#define NAVE_MAE_H

struct Jogo;

struct NaveMae{
	ALLEGRO_BITMAP *imagem=NULL;
	int posicao_x;
	int posicao_y;
	int velocidade;
	int status;
};

//desenha a nave de acordo com as coordenadas
//apenas essa aqui será usada no loop do jogo
void desenha_nave(NaveMae*, Jogo*);

// por enquanto apenas coloca posicao_x=0 e posicao_y=0[depois faz mais]
// AINDA PRECISA REINICIAR O CONTADOR AQUI
void reinicia_nave(NaveMae*);

// responsável pela mudança nas coordenadas
void movimenta_nave(NaveMae*);

// carrega a imagem em nave->imagem, reinicia as posições e define a velocidade
//utilizar antes da inicialização do loop do jogo
void inicializa_nave(NaveMae*);

//função que controla se a nave mae aparece ou n
int autoriza_nave(NaveMae*, Jogo*);

//destroi a nave mae
void finaliza_nave(NaveMae*);

#endif
