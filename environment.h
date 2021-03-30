#include <stdlib.h>

Map* createMap(unsigned int height, unsigned int width) {
	Map* map = (Map*) malloc(sizeof(Map));
	map->height = height;
	map->width = width;
	map->grid = (Chunk***) calloc(height, sizeof(Chunk**));

	for (unsigned int y = 0; y < height; y++) {
		map->grid[y] = (Chunk**) calloc(width, sizeof(Chunk*));
		for (unsigned int x = 0; x < width; x++) {
			map->grid[y][x] = NULL;
		}
	}

	return map;
}

Chunk* getChunk(Map* map, unsigned int x, unsigned int y) {
	return map->grid[y][x];
}
                                                                
Chunk* placeChunk(Map* map, char icon, unsigned int x, unsigned int y) {
	Chunk* result = (Chunk*) malloc(sizeof(Chunk));
	result->x = x;
	result->y = y;
	result->icon = icon;
	map->grid[y][x] = result;

	return result;
}
                                                                
Chunk* removeChunk(Map* map, unsigned int x, unsigned int y) {
	Chunk* result = map->grid[y][x];
	map->grid[y][x] = NULL;
	return result;
}


Chunk* replaceChunk(Map* map, Chunk* chunk) {
	Chunk* removed = removeChunk(map, chunk->x, chunk->y);
	map->grid[chunk->y][chunk->x] = chunk;
	return removed;
}
