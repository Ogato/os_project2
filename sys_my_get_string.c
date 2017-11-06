#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include "../set_state/my_vars.h"

/* This syscall takes a string (pointer to a character buffer)
 * and the size of the string. Based on the bsize parameter,
 * the syscall copies my_string to buf upto bsize making sure
 * to NUL terminate the string
*/
asmlinkage long sys_my_get_string(char* buf, int bsize){

	int slen;	/* String length of my_string */
	int copylen;	/* Length to copy from my_string */
	int not_copied; /* Amount of characters not copied if any */

	/* Error if my_string is empty */
	if(strlen(my_string) == 0 || my_string == NULL){
		return -ENODATA;
	}

	slen = strlen(my_string);
	copylen = min(slen, bsize-1);

	/* Error if buf is NULL */
	if(buf == NULL){
		return -EFAULT;
	}

	/* Copy my_string to buf up to copylen */
	not_copied = copy_to_user(buf, my_string, copylen);

	/* Error if not all chars are copied up to copylen */
	if(not_copied > 0){
		return -not_copied;
	}

	/* Append terminating char to end of string */
	buf[copylen-1] = '\0';

	return copylen;
}
