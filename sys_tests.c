#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "my_vars.h"

/* Intialize global vars defined in my_vars.h */
char* my_string = NULL;
int my_accumulator = 0;

/* This syscall takes a string and integer. The global variables
 * my_string and my_accumulator are then set to each of the args
 * respectively
*/
asmlinkage long sys_my_set_state(char* the_string, int accumulator){

	/* Error if accumulator is negative */
	if(accumulator < 0){
		return -EINVAL;
	}

	/* Error if the_string is NULL or is not terminated correctly */
	else if(the_string[strlen(the_string)] != '\0' || the_string == NULL){
		return -EINVAL;
	}
	
	else{
		my_accumulator = accumulator;

		/* Free my_string if it has already been set */
		if(my_string != NULL){
			kfree(my_string);
		}
		/* Allocate space for my_string from kernel memory*/
		my_string = (char*)kmalloc(strlen(the_string), GFP_KERNEL);

		/* Error if copy_from_user fails */
		if(copy_from_user(my_string, the_string, strlen(the_string)) != 0){
			return -EOVERFLOW;
		}
	}

	return 0;
}
