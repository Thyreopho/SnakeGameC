#include <stdlib.h>
#include <stdbool.h>

//CHUNK TYPE
#define HEAD	'0'
#define BODY	'o'
#define BERRY	'*'
#define WALL	'#'

//DIRECTIONS
#define UP	'w'
#define RIGHT	'd'
#define DOWN	's'
#define LEFT	'a'

Player* createPlayer(Map* map) {
	Player* player = (Player*) malloc(sizeof(Player)); //Instancia um novo jogador no mapa informado
	player->direction = UP;
	player->bodySize = 0;
	player->head = createChunk(HEAD, map->width/2, map->height/2);
	setChunk(map, player->head); //Posiciona a cabeca do jogador no mapa
	player->body = (Chunk**) calloc((map->width-1) * (map->height-1), sizeof(Chunk*)); //Instancia o vetor do corpo
}

void placeBerry(Map* map) {
	unsigned int x = rand() % map->width, y = rand() % map->height;
	while (getChunk(map, x, y) != NULL) { //Por enquanto a nova posicao da fruta estiver ocupada se continua procurando uma nova posicao
		x = rand() % map->width;
		y = rand() % map->height;
	}
	setChunk(map, createChunk(BERRY, x, y)); //Posiciona a fruta
}

bool move(Map* map, Player* player, char direction) {
	player->direction = direction; //Definit a nova direcao do jogador
	Chunk* head = removeChunk(map, player->head->x, player->head->y); //Se remove a cabeca para permitir a movimentacao do corpo
	unsigned int newX = head->x, newY = head->y; //Se armazena a posicao que a proxima parte do corpo sera inserida
	//#region body flow
	/*
		Utilizando o conteúdo disponibilizado 
		desenvolva um código que faça o corpo 
		do jogador seguir sua cabeça
	*/
	//#endregion
	//#region move
	switch (direction) { //Mover cabeca na direcao informada
		case UP:
			head->y--;
			break;
		case RIGHT:
			head->x++;
			break;
		case DOWN:
			head->y++;
			break;
		case LEFT:
			head->x--;
			break;
	}
	//#endregion
	//#region collision
	bool result = true; //Situacao do jogo ("true" para continua e "false" para fim de jogo)
	Chunk* element = replaceChunk(map, head); //Posicionar a cabeca e obter elemento colidido
	Chunk* newBodyPart;
	if (element != NULL) { //Caso seja:
		switch (element->icon) {
			case BODY: //Corpo = fim de jogo
				result = false;
				break;
			case WALL: //Parede = fim de jogo
				result = false;
				break;
			case BERRY: //Fruta
				newBodyPart = createChunk(BODY, newX, newY); //Criar e posicionar uma nova parte do corpo
				player->body[player->bodySize] = newBodyPart;
				setChunk(map, newBodyPart);
				player->bodySize++; //Acumular pontos
				placeBerry(map); //Posicionar uma nova fruta
				break;
		}
	}
	//#endregion
	free(element);
	return result;
}
