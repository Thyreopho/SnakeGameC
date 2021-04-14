typedef struct Chunk {
	unsigned int x;
	unsigned int y;
	char icon; //Indicador de tipo (tipos definidos em game.h)
} Chunk;

typedef struct Map {
	unsigned int height;
	unsigned int width;
	Chunk*** grid; //matriz de chunks, representacao logica do mapa
} Map;

typedef struct Player {
	char direction; //Direcao em que o jogador se movimenta
	unsigned int bodySize; //Tamanho do corpo do jogador e consequentimente contador de pontos
	Chunk* head;
	Chunk** body;
} Player;
