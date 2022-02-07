#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 		  (8363)
#define FRAMES_PER_BUFFER 	  (1024)

#define MOD_NAME_SIZE 		  (20)
#define INSTRUMENT_SIZE 	  (30)

#define INSTRUMENT_NAME_SIZE  (22)
#define MAX_SAMPLE_SIZE 	  (131070)

#define NUMBER_OF_INSTRUMENTS (31)
#define PATTERN_TABLE_SIZE 	  (128)
#define BYTE 				  (1)
#define WORD 				  (2)
#define NUMBER_OF_PATTERNS    (64)
#define PATTERN_LENGTH 		  (64)
#define PATTERN_SIZE 		  (1024)
#define NOTE_LENGTH 		  (4)
#define NUMBER_OF_SAMPLES 	  (30)

int current_position = 0;
int8_t *mod_file;


// max size for a sample is 131070 bytes

/* yeah so all the samples should be available */
/* and all the sample lengths i guess */
// typedef struct
// {
// 	int8_t *samples[NUMBER_OF_SAMPLES];
// } paTestData;
typedef struct instrument{
	int8_t *name;
	int8_t *length;
	int8_t *finetune;
	int8_t *volume;
	int8_t *repeat_offset;
	int8_t *repeat_length;
	int8_t *data;
} instrument;

// readFileBuffer(&(instruments[i].name), &mod_file, current_position, INSTRUMENT_NAME_SIZE);
// readFileBuffer(&(instruments[i].length), &mod_file, current_position, WORD);
// readFileBuffer(&(instruments[i].finetune), &mod_file, current_position, BYTE);
// readFileBuffer(&(instruments[i].volume), &mod_file, current_position, BYTE);
// readFileBuffer(&(instruments[i].repeat_offset), &mod_file, current_position, WORD);
// readFileBuffer(&(instruments[i].repeat_length), &mod_file, current_position, WORD);

// typedef struct paTestData
// {
// 	instrument (*mod_instruments)[];
// }
// paTestData;

static float linearTransformToFloats(float val) {
  float oldMin = 128;
  float oldMax = -127;
  float newMin = -1;
  float newMax = 1;
  float oldRange = oldMax - oldMin;
  float newRange = newMax - newMin;
  return (((val - oldMin)*newRange) / oldRange) + newMin;
}

void readFileBuffer( int8_t **buffer_to,  int8_t **pointer, int pointer_offset, int buffer_size) {
	*buffer_to = ( int8_t *) malloc(sizeof( int8_t)*buffer_size);
	memcpy(*buffer_to, *pointer + pointer_offset, buffer_size);
	current_position = pointer_offset + buffer_size;
}

int main(int argc, char **argv) {
	FILE *fptr;
	long file_size;
	int8_t *instruments,
		   *mod_file, *mod_name,
		   *song_length, *pattern_table,
		   *initials, *patterns;


	// why did i do it like this

	// the whole point of memory addresses is so that you dont need arrays lol
	// especially because thing is a fixed length...
	// so u can multiply the length by the index to get the position you need
	// im so dujb lol

	// struct instrument instruments[NUMBER_OF_INSTRUMENTS];

	if (argc < 2) {
		printf("There's no file. Closing safely...");
		return 500;
	}

	fptr = fopen(argv[1], "rb");
	fseek(fptr, 0L, SEEK_END); 	// seek to end of file to get position of last byte
	file_size = ftell(fptr); // get current file pointer
	fseek(fptr, 0L, SEEK_SET); // seek to beginning of file again

	mod_file = (int8_t *) malloc(sizeof(int8_t)*file_size);
	fread(mod_file, sizeof(*mod_file), file_size, fptr);

	fclose(fptr);

	mod_name = &(mod_file[0]);

	for (int x = 0; x < 20; x++) {
		printf("%d\n", mod_name[x]);
	}

	// readFileBuffer(&mod_name, &mod_file, current_position, MOD_NAME_SIZE);

	// instruments = (int8_t *) malloc(sizeof(int8_t) * (NUMBER_OF_INSTRUMENTS * (INSTRUMENT_SIZE + MAX_SAMPLE_SIZE)));

	// for(int j = 0; j < NUMBER_OF_INSTRUMENTS; j++) {
	// 	int current_instrument = ((INSTRUMENT_SIZE + MAX_SAMPLE_SIZE) * j);
	// 	memcpy(instruments + current_instrument, mod_file + current_position, INSTRUMENT_SIZE);
	// 	current_position = current_position + INSTRUMENT_SIZE;
	// }

	// readFileBuffer(&song_length, &mod_file, current_position, BYTE);

	// // skip over irelevant bit
	// current_position = current_position + 1;

	// readFileBuffer(&pattern_table, &mod_file, current_position, PATTERN_TABLE_SIZE);

	// readFileBuffer(&initials, &mod_file, current_position, WORD*2);

	// int actual_number_of_patterns = -1;

	// for (int x = 0; x < PATTERN_TABLE_SIZE; x++) {
	// 	if (pattern_table[x] > actual_number_of_patterns) {
	// 		actual_number_of_patterns = pattern_table[x];
	// 	}
	// }

	// readFileBuffer(&patterns, &mod_file, current_position, PATTERN_SIZE*actual_number_of_patterns);

	// for(int j = 0; j < NUMBER_OF_INSTRUMENTS; j++) {
	// 	int current_instrument = ((INSTRUMENT_SIZE + MAX_SAMPLE_SIZE) * j);
	// 	int length_position = current_instrument + INSTRUMENT_NAME_SIZE;
	// 	int length = (*(instruments + length_position) << 8 | *(instruments + length_position + BYTE)) * 2;
	// 	memcpy(
	// 		instruments + current_instrument + INSTRUMENT_SIZE,
	// 		mod_file + current_position,
	// 		length
	// 	);
	// 	current_position = current_position + length;
		// (all_instruments->length[0] << 8 | all_instruments->length[1]) * 2
		// need to calculate length of each sample from the data stored at the pointer
		// and only incremenent the current position by that much

		// then also need to copy the data into the memory space allocated to each
		// instrument after
	// }

	// readFileBuffer(&patterns)

	// for(int k = 0; k < actual_number_of_patterns + 1; k++) {
	// 	readFileBuffer(&patterns[k], &mod_file, current_position, PATTERN_SIZE);
	// }

	// need to malloc number of instruements * (size of intrument header + size of insutr ment
	// instruments = (int8_t *) malloc(sizeof(int8_t) * (NUMBER_OF_INSTRUMENTS * (INSTRUMENT_SIZE + MAX_SAMPLE_SIZE)));

	// for(int j = 0; j < NUMBER_OF_INSTRUMENTS; j++) {
	// 	memcpy(instruments, mod_file + current_position, INSTRUMENT_SIZE);
	// 	current_position + MAX_SAMPLE_SIZE;
	// 	// memcpy(*buffer_to, *pointer + pointer_offset, buffer_size);
	// 	// current_position = pointer_offset + buffer_size;
	// 	// readFileBuffer(&instruments, &mod_file, current_position, ((*(instruments[j].length)) << 8 | (*(instruments[j].length+1))) * 2);
	// }

	// hhm these arent the same but rest of file could just be rash

	//aaa need to do hard stuff now lol
	printf("%d\n", current_position);
	printf("%ld\n", file_size);
}
