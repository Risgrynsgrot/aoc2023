#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

void removeChar(char removeChar, const char* string, char* outString) {
	int outIndex = 0;
	for(int i = 0; i < strlen(string); i++) {
		if(string[i] == removeChar) {
			continue;
		}
		outString[outIndex] = string[i];
		outIndex++;
	}
}

int possible_game(char* line) {
	char* game_split;
	char* round_split;
	char* cube_split;
	char* value_split;
	int index = 0;

	char* game_tok = strtok_r(line, ":", &game_split);
	int game_index = 0;
	while(game_tok != NULL) {
		printf("game: %s\n", game_tok);
		if(game_index == 0) {
			game_tok = strtok_r(NULL, ":", &game_split);
			game_index++;
			continue;
		}

		char* round_tok = strtok_r(game_tok, ";", &round_split);
		while(round_tok != NULL) {
			//printf("round: %s\n", round_tok);

			char* cube_tok = strtok_r(round_tok, ",", &cube_split);
			while(cube_tok != NULL) {
				//printf("cubes: %s %i\n", cube_tok, index);

				int activeValue = -1;
				index			= 0;
				char* value_tok = strtok_r(cube_tok, " ", &value_split);
				while(value_tok != NULL) {
					//printf("value: %s\n", value_tok);
					if(index == 0) {
						activeValue = atoi(value_tok);
						//printf("active value: %i\n", activeValue);
					}

					if(index == 1) {
						//printf("comparing %s\n", value_tok);
						char trimmed[300];
						removeChar(' ', value_tok, trimmed);
						//int result = strncmp(trimmed, "red", 3);
						////printf("result: %d\n", result);
						if(strncmp(trimmed, "red", 3) == 0) {
							//printf("it's red! %d\n", activeValue);
							if(activeValue > MAX_RED) {
								printf("invalid round\n");
								return 0;
							}
						}
						if(strncmp(trimmed, "green", 5) == 0) {
								//printf("it's green! %d \n", activeValue);
							if(activeValue > MAX_GREEN) {
								printf("invalid round\n");
								return 0;
							}
						}
						if(strncmp(trimmed, "blue", 4) == 0) {
								//printf("it's blue! %d\n", activeValue);
							if(activeValue > MAX_BLUE) {
								printf("invalid round\n");
								return 0;
							}
						}
					}
					index++;
					value_tok = strtok_r(NULL, " ", &value_split);
				}
				activeValue = -1;
				cube_tok = strtok_r(NULL, ",", &cube_split);
			}

			round_tok	= strtok_r(NULL, ";", &round_split);
		}

		game_tok = strtok_r(NULL, ":", &game_split);
		game_index++;
	}

	printf("valid round\n");
	return 1;
}

int main() {
	FILE* fptr = fopen("input.txt", "r");
	if(!fptr) {
		return 1;
	}

	const size_t line_size = 300;
	char* line			   = malloc(line_size);
	int result;
	int id = 1;
	while(fgets(line, line_size, fptr)) {
		if(strlen(line) <= 1) {
			continue;
		}
		//printf("%s\n", line);
		int add = id * possible_game(line);
		result += add;
		printf("adding: %d %li\n", add, strlen(line));
		id++;
	}
	printf("%d", result);
	free(line);
}
