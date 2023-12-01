#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* number_strings[10] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
};

char* rstrstr(const char* haystack, const char* needle) {
	char* result = NULL;
	for(int i = strlen(haystack) - 2; i >= 0; i--) {
		result = strstr(haystack + i, needle);
		if(result != NULL) {
			return result;
		}
	}
	return result;
}

int print_first_and_last(const char* input) {
	int numbers[2]	   = {-1, -1};
	char* lowestIndex  = (char*)LONG_MAX;
	char* highestIndex = 0;
	printf("%s\n", input);
	for(int i = 0; i < 10; i++) {
		char* found_string		= strstr(input, number_strings[i]);
		char* found_last_string = rstrstr(input, number_strings[i]);

		if(found_string == NULL) {
			continue;
		}
		if(lowestIndex == NULL) {
			lowestIndex = found_string;
			numbers[0]	= i;
		}
		if(highestIndex == NULL) {
			highestIndex = found_last_string;
			numbers[1]	 = i;
		}

		if(found_string < lowestIndex) {
			lowestIndex = found_string;
			numbers[0]	= i;
		}

		if(found_last_string > highestIndex) {
			highestIndex = found_last_string;
			numbers[1]	 = i;
		}
	}

	bool lowest_found = false;
	for(int i = 0; i < strlen(input); i++) {
		char c = input[i];
		if(c < '0' || c > '9') {
			continue;
		}

		if(!lowest_found && (numbers[0] == -1 || i < (lowestIndex - input))) {
			numbers[0]	 = c - '0';
			lowest_found = true;

			if(numbers[1] == -1) {
				numbers[1] = numbers[0];
			}
			continue;
		}
		if(i > (highestIndex - input)) {
			numbers[1] = c - '0';
		}
	}
	printf("%i%i\n", numbers[0], numbers[1]);
	return numbers[0] * 10 + numbers[1];
}

int main(int argc, char* argv[]) {
	FILE* fptr = fopen("input.txt", "r");
	if(!fptr) {
		return 1;
	}

	const size_t line_size = 300;
	char* line			   = malloc(line_size);
	int result;
	while(fgets(line, line_size, fptr)) {
		int number = print_first_and_last(line);
		result += number;
	}
	printf("%d", result);
	free(line);
}
