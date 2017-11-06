#include <linux/kernel.h>
#include <linux/errno.h>
#include "../set_state/my_vars.h"

/* This syscall takes a pointer to an integer and
 * an integer to add to the global my_accumulator
 * variable. Sets my_value to my_accumulator's new
 * value
*/
asmlinkage long sys_my_get_and_sum(int* my_value, int inc_value){
	/*Error if sum is greater than INT_MAX */
	if(my_accumulator + inc_value > INT_MAX){
		return -EOVERFLOW;
	}

	/*Error if pointer to my_value is NULL*/
	if(my_value == NULL){
		return -EFAULT;
	}

	/*Dereference my_value and set its new value*/
	*my_value = my_accumulator + inc_value;

	/*Increment my_accumulator's value*/
	my_accumulator += inc_value;
	return 0;
}
