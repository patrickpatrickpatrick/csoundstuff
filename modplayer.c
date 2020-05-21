#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MOD_NAME_SIZE 20
#define INSTRUMENT_SIZE 30
#define NUMBER_OF_INSTRUMENTS 31
#define PATTERN_TABLE_SIZE 128
#define BYTE 1
#define WORD 2
#define NUMBER_OF_PATTERNS 64
#define PATTERN_LENGTH 64
#define NOTE_LENGTH 4

int current_position = 0;

void readFileBuffer(char **buffer_to, char **pointer, int pointer_offset, int buffer_size) {
	*buffer_to = (char *) malloc(sizeof(char)*buffer_size);
	memcpy(*buffer_to, *pointer + pointer_offset, buffer_size);
	current_position = pointer_offset + buffer_size;
}

int main(int argc, char **argv) {
	FILE *fptr;
	long file_size;
	char *mod_file, *mod_name,
		 *instruments[NUMBER_OF_INSTRUMENTS],
		 *song_length, *pattern_table[NUMBER_OF_PATTERNS],
		 *initials,*patterns;

	fptr = fopen(argv[1], "rb");
	fseek(fptr, 0L, SEEK_END); 	// seek to end of file to get position of last byte
	file_size = ftell(fptr); // get current file pointer
	fseek(fptr, 0L, SEEK_SET); // seek to beginning of file again

	mod_file = (char *) malloc(sizeof(char)*file_size);
	fread(mod_file, sizeof(*mod_file), file_size, fptr);

	fclose(fptr);

	readFileBuffer(&mod_name, &mod_file, current_position, MOD_NAME_SIZE);

	for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++) {
		readFileBuffer(&instruments[i], &mod_file, current_position, INSTRUMENT_SIZE);		
	}


	readFileBuffer(&song_length, &mod_file, current_position, BYTE);

	current_position = current_position + 1;

	readFileBuffer(&pattern_table, &mod_file, current_position, PATTERN_TABLE_SIZE);

	readFileBuffer(&initials, &mod_file, current_position, WORD*2);

	for (int j = 0; j < PATTERN_LENGTH; j++) {
		readFileBuffer(&initials, &mod_file, current_position, WORD*2);
	}

	printf("%s\n", mod_name);
	// printf("%s\n", instrument);

	return 0;
}