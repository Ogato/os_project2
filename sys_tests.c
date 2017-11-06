#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <assert.h>


/* This program tests three syscalls:
 *	sys_my_set_state
 *	sys_my_get_and_sum
 *	sys_my_get_string
*/
int main(){
	/* Declare Variables */
	long int set_state_val;
	long int get_and_sum_val;
	long int get_string_val;
	char* enter_str;
	char* receive_str;
	int receive_len;
	int enter_val;
	int receive_val;
	int* receive_val_pointer;
	int inc_val;

	enter_str = "Hello World\0";
	receive_len = strlen(enter_str)/2;
	receive_str = (char*)malloc(receive_len);
	enter_val = 10;
	receive_val = 0;
	receive_val_pointer = &receive_val;
	inc_val = 5;

	/* First test of sys_my_set_state */
	set_state_val = syscall(354, enter_str, enter_val);
	assert(set_state_val == 0);
	printf("sys_my_set_state first successful attempt\n");

	/* First test of sys_my_get_and_sum */
	get_and_sum_val = syscall(355, receive_val_pointer, inc_val);
	assert(get_and_sum_val == 0);
	assert(receive_val == (enter_val + inc_val));
	printf("sys_my_get_and_sum 2nd int set: %d\n", receive_val);

	/* First test of sys_my_get_string */
	get_string_val = syscall(356, receive_str, receive_len);
	assert(get_string_val == receive_len-1);
	printf("First copied string: %s\nFirst received string: %s\n", enter_str, receive_str);

	return 0;
}
