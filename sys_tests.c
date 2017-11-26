#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Define syscall macros for convenience */
#define SET_STATE	354
#define GET_AND_SUM 	355
#define GET_STRING 	356


int main(){
	/* Define testing vars */
	const char* the_string = "Hello World";
	const char* the_string_2 = "Who, what, when, where, why, and how?";
	int accumulator = 10;
	int accumulator_2 = -1;
	int my_val = 0;
	int* my_val_ptr = &my_val;
	int inc_value = 5;
	char* buf = (char*)malloc(sizeof(the_string));
	int bsize = 6;

	/* Test my_set_state syscall with negative value*/
	printf("\nCalling my_set_state syscall with args: %s, %d\n", the_string_2, accumulator_2);
	assert(syscall(SET_STATE, the_string_2, accumulator_2) != 0);
	printf("my_set_state syscall passed!\n");

	/* Test my_set_state syscall with acceptable  values*/
        printf("\nCalling my_set_state syscall with args: %s, %d\n", the_string, accumulator);
        assert(syscall(SET_STATE, the_string, accumulator) == 0);
        printf("my_set_state syscall passed!\n");

	/* Test my_get_and_sum */
	printf("\nCalling my_get_and_sum with inc_value of: %d\n", inc_value);
	assert(syscall(GET_AND_SUM, my_val_ptr, inc_value) == 0);
	assert(my_val == 15);
	printf("New accumulator: %d\n", my_val);
	printf("my_get_and_sum syscall passed!\n");

	/* Test my_get_string */
	printf("\nCalling my_get_string with bsize (including NUL): %d\n", bsize);
	assert(syscall(GET_STRING, buf, bsize) == bsize-1);
	printf("Returned string: %s\n", buf);
	printf("my_get_string syscall passed!\n");
	return 0;
}
