#include <stdio.h>
#include <stdlib.h>

void render(Map* map, Player* player) {
	system("clear");
	char* row = (char*) calloc(map->width, sizeof(char));
	for (unsigned int y = 0; y < map->height; y++) {
		Chunk* value;
		for (unsigned int x = 0; x < map->width; x++) {
			value = map->grid[y][x];
			row[x] = value == NULL? ' ' : value->icon;
		}
		printf("%s\n", row);
	}
	printf("Pontos: %i\n", player->bodySize);
}
