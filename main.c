#include <stdio.h>
#include "struct.h"
#include "environment.h"
#include "game.h"
#include "render.h"

#define HEIGHT 10
#define WIDTH 20

int main (int argc, char** argv) {

	Map* map = createMap(HEIGHT, WIDTH); //Criar mapa
	for (unsigned int i = 0; i < WIDTH; i++) { //Posicioar paredes horizontais do mapa
		setChunk(map, createChunk(WALL, i, 0));
		setChunk(map, createChunk(WALL, i, HEIGHT-1));
	}

	unsigned int limit = HEIGHT - 1;
	for (unsigned int i = 1; i < limit; i++) { //Posicionar paredes verticais do mapa
		setChunk(map, createChunk(WALL, 0, i));
		setChunk(map, createChunk(WALL, WIDTH-1, i));
	}
	
	Player* player = createPlayer(map); //Criar jogador
	
	char direction;
	placeBerry(map);
	do {
		render(map, player); //Renderizar mapa
		system("/bin/stty raw");
		direction = getchar(); //Ler somente um char
		system("/bin/stty cooked");
	} while(move(map, player, direction)); //mover jogador por enquanto nao e fim de jogo

	return 0;
}
