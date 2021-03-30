typedef struct Chunk {
	unsigned int x;
	unsigned int y;
	char icon;
} Chunk;

typedef struct Map {
	unsigned int height;
	unsigned int width;
	Chunk*** grid;
} Map;

typedef struct Player {
	char direction;
	unsigned int bodySize;
	Chunk* head;
	Chunk** body;
} Player;
