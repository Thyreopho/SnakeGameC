#include <stdlib.h>

Map* createMap(unsigned int height, unsigned int width) {
	Map* map = (Map*) malloc(sizeof(Map)); //Instancia-se um novo mapa com os dados informados
	map->height = height;
	map->width = width;

	//Instancia por completo a matriz do mapa, preenchendo-a com NULLs
	map->grid = (Chunk***) calloc(height, sizeof(Chunk**));
	for (unsigned int y = 0; y < height; y++) {
		map->grid[y] = (Chunk**) calloc(width, sizeof(Chunk*));
		for (unsigned int x = 0; x < width; x++) {
			map->grid[y][x] = NULL;
		}
	}

	return map;
}

Chunk* createChunk(char icon, unsigned int x, unsigned int y) {
	Chunk* result = (Chunk*) malloc(sizeof(Chunk)); //Instancia-se um novo Chunk com os dados informados
	result->x = x;
	result->y = y;
	result->icon = icon;

	return result;
}

Chunk* getChunk(Map* map, unsigned int x, unsigned int y) {
	return map->grid[y][x]; //Retorna o Chunk na posicao informada
}

void setChunk(Map* map, Chunk* chunk) {
	free(getChunk(map, chunk->x, chunk->y)); //Deleta antigo Chunk
	map->grid[chunk->y][chunk->x] = chunk; //Posiciona o novo Chunk
}
                                                                
Chunk* removeChunk(Map* map, unsigned int x, unsigned int y) {
	Chunk* result = getChunk(map, x, y); //Pega elemento que sera removido
	map->grid[y][x] = NULL; //Define posicao com valor igual a NULL
	return result; //Retorna elemento removodo
}


Chunk* replaceChunk(Map* map, Chunk* chunk) {
	Chunk* removed = removeChunk(map, chunk->x, chunk->y); //Remove elemento na mesma posicao do Chunk informado
	setChunk(map, chunk); //Posiciona novo Chunk
	return removed; //Retorna elemento removido
}
