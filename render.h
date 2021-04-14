#include <stdio.h>
#include <stdlib.h>

void render(Map* map, Player* player) {
	system("clear");
	char* row = (char*) calloc(map->width, sizeof(char)); //Se instancia um vetor de chars (string) para reprensetar as linhas da matriz do mapa
	Chunk* value;
	for (unsigned int y = 0; y < map->height; y++) { //Percorre-se todas as linhas do mapa
		for (unsigned int x = 0; x < map->width; x++) { //Para cada coluna, ou seja, Chunk dentro da linha
			value = getChunk(map, x, y);
			row[x] = value == NULL? ' ' : value->icon; //Caso seja NULL se escreve um ' ', caso contrario o icone do Chunk
		}
		printf("%s\n", row); //Imprimir a linha gerada
	}
	printf("Pontos: %i\n", player->bodySize); //Imprimit pontuacao do jogador
}
