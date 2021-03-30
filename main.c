#include <stdio.h>
#include "struct.h"
#include "environment.h"
#include "game.h"
#include "render.h"

#define HEIGHT 10
#define WIDTH 20

int main (int argc, char** argv) {

	Map* map = createMap(HEIGHT, WIDTH);
	for (unsigned int i = 0; i < WIDTH; i++) {
		placeChunk(map, WALL, i, 0);
		placeChunk(map, WALL, i, HEIGHT-1);
	}

	unsigned int limit = HEIGHT - 1;
	for (unsigned int i = 1; i < limit; i++) {
		placeChunk(map, WALL, 0, i);
		placeChunk(map, WALL, WIDTH-1, i);
	}

	Player* player = createPlayer(map);
	
	char direction;
	placeBerry(map);
	do {
		render(map, player);
		system("/bin/stty raw");
		direction = getchar();
		system("/bin/stty cooked");
	} while(move(map, player, direction));

	return 0;
}
