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

void readFileBuffer( uint8_t **buffer_to,  uint8_t **pointer, int pointer_offset, int buffer_size) {
	*buffer_to = ( uint8_t *) malloc(sizeof( uint8_t)*buffer_size);
	memcpy(*buffer_to, *pointer + pointer_offset, buffer_size);
	current_position = pointer_offset + buffer_size;
}

int main(int argc, char **argv) {
	FILE *fptr;
	long file_size;
	 uint8_t *mod_file, *mod_name,
		 *instruments[NUMBER_OF_INSTRUMENTS],
		 *song_length, *pattern_table,
		 *initials,*patterns[NUMBER_OF_PATTERNS];

	if (argc < 2) {
		printf("There's no file. Closing safely...");
		return 500;
	}

	fptr = fopen(argv[1], "rb");
	fseek(fptr, 0L, SEEK_END); 	// seek to end of file to get position of last byte
	file_size = ftell(fptr); // get current file pointer
	fseek(fptr, 0L, SEEK_SET); // seek to beginning of file again

	mod_file = (uint8_t *) malloc(sizeof(uint8_t)*file_size);
	fread(mod_file, sizeof(*mod_file), file_size, fptr);

	fclose(fptr);

	readFileBuffer(&mod_name, &mod_file, current_position, MOD_NAME_SIZE);

	for (int i = 0; i < NUMBER_OF_INSTRUMENTS; i++) {
		readFileBuffer(&instruments[i], &mod_file, current_position, INSTRUMENT_SIZE);		
	}

	readFileBuffer(&song_length, &mod_file, current_position, BYTE);

	// skip over irelevant bit
	current_position = current_position + 1;

	readFileBuffer(&pattern_table, &mod_file, current_position, PATTERN_TABLE_SIZE);

	readFileBuffer(&initials, &mod_file, current_position, WORD*2);

	// for (int j = 0; j < PATTERN_LENGTH; j++) {
	// 	readFileBuffer(&initials, &mod_file, current_position, WORD*2);
	// }

	for(int k = 0; k < NUMBER_OF_PATTERNS; k++) {
		readFileBuffer(&patterns[k], &mod_file, current_position, PATTERN_LENGTH);
	}


	for(int j = 0; j < NUMBER_OF_INSTRUMENTS; j++) {
		uint8_t *x;
		// x = &instruments[j][0];
		x = ( uint8_t *)malloc(sizeof( uint8_t)*WORD);
		memcpy(x, &instruments[j], WORD);


		// x += 23;
		printf("%d\n", x[0]);
		printf("%d\n", x[1]);
		// printf("%d\n", x[0] << 8 | x[1]);
		printf("%s\n", instruments[j]);
	}
	//aaa need to do hard stuff now lol

	printf("%s\n", mod_name);
	// printf("%s\n", instrument);

	return 0;
}