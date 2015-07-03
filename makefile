all: game.o player.o projetil.o menu.o alien.o mothership.o hud.o shield.o
	g++ main.cpp game.o player.o projetil.o menu.o alien.o mothership.o hud.o shield.o -o main -g -std=c++11 -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
	rm game.o
	rm player.o
	rm projetil.o
	rm menu.o
	rm alien.o
	rm mothership.o
	rm hud.o
	rm shield.o
game.o:
	g++ -c -g game.cpp
player.o:
	g++ -c -g player.cpp
projetil.o:
	g++ -c -g projetil.cpp
menu.o:
	g++ -c -g menu.cpp
alien.o:
	g++ -c -g alien.cpp
mothership.o:
	g++ -c -g mothership.cpp
hud.o:
	g++ -c -g hud.cpp
shield.o:
	g++ -c -g shield.cpp