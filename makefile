all: game.o player.o projetil.o menu.o alien.o mothership.o
	g++ main.cpp game.o player.o projetil.o menu.o alien.o mothership.o -o main -std=c++11 -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
	rm game.o
	rm player.o
	rm projetil.o
	rm menu.o
	rm alien.o
	rm mothership.o
game.o:
	g++ -c game.cpp
player.o:
	g++ -c player.cpp
projetil.o:
	g++ -c projetil.cpp
menu.o:
	g++ -c menu.cpp
alien.o:
	g++ -c alien.cpp
mothership.o:
	g++ -c mothership.cpp