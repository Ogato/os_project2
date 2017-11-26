#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>

/* This module displays the state of the current process's VMA 
 * through a proc file named vm_proc
*/
static int vm_proc_show(struct seq_file *f){

	/* Variable to iterate over the current process's VMAs */
	struct vm_area_struct* vms;

	seq_printf(f, "PID: %d\nName: %s\nVM_AREAS:\n", current->pid,
					     		current->comm);
	/* Loop through list of VMAs until the end */
	vms = current->mm->mmap;
	while(vms != NULL){
		seq_printf(f, "Start Address: %lu\nEnd Address: %lu\nFlags: %lu\n",vms->vm_start,
								     vms->vm_end,
								     vms->vm_flags);
		vms = vms->vm_next;
	}
	return 0;
}

/* Open a new proc file when requested */
static int vm_proc_open(struct inode* inode, struct file* file){
	return single_open(file, vm_proc_show, NULL);
}

static const struct file_operations vm_proc_fops = {
	.owner = THIS_MODULE,
	.open = vm_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

/* Create the proc file when module is loaded */ 
static int __init vm_proc_init(void){
	proc_create("vm_proc", 0, NULL, &vm_proc_fops);
	return 0;
}

/* Remove the proc file when the module is removed */
static void __exit vm_proc_exit(void){
	remove_proc_entry("vm_proc", NULL);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Group 16");
module_init(vm_proc_init);
module_exit(vm_proc_exit);


