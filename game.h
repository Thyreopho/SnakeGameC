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
	Player* player = (Player*) malloc(sizeof(Player));
	player->direction = UP;
	player->bodySize = 0;
	player->head = placeChunk(map, HEAD, map->width/2, map->height/2);
	player->body = (Chunk**) calloc((map->width-1) * (map->height-1), sizeof(Chunk*));
}

void placeBerry(Map* map) {
	unsigned int x = rand() % map->width, y = rand() % map->height;
	while (getChunk(map, x, y) != NULL) {
		x = rand() % map->width;
		y = rand() % map->height;
	}
	placeChunk(map, BERRY, x, y);
}

bool move(Map* map, Player* player, char direction) {
	player->direction = direction;		
	Chunk* head = removeChunk(map, player->head->x, player->head->y);
	unsigned int newX = head->x, newY = head->y;
	//#region body flow
	if (player->bodySize > 0) {
		Chunk *curr, *next;
		for (unsigned int i = player->bodySize - 1; i > 0; i--) {
			curr = player->body[i];
			next = player->body[i-1];
			removeChunk(map, curr->x, curr->y);
			curr->x = next->x;
			curr->y = next->y;

		}

		curr = player->body[0];
		removeChunk(map, curr->x, curr->y);
		curr->x = head->x;
		curr->y = head->y;
		for (unsigned int i = 0; i < player->bodySize; i++) {
			replaceChunk(map, player->body[i]);
		}
	}
	//#endregion
	//#region move
	switch (direction) {
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
	bool result = true;
	Chunk* element = replaceChunk(map, head);
	if (element != NULL) {
		switch (element->icon) {
			case BODY:
				result = false;
				break;
			case WALL:
				result = false;
				break;
			case BERRY:
				//Increase size
				player->body[player->bodySize] = placeChunk(map, BODY, newX, newY);
				player->bodySize++;
				placeBerry(map);
				break;
		}
	}
	//#endregion
	return result;
}
