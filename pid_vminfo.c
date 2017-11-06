#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>

static int vm_proc_show(struct seq_file *f){
	seq_printf(f, "PID: %d\nName: %s\nVM_AREAS:\n", current->pid,
					     		current->comm);

	struct vm_area_struct* temp = current->mm->mmap;
	while(temp != NULL){
		seq_printf(f, "Start Address: %lu\nEnd Address: %lu\nFlags: %lu\n",temp->vm_start,
								     temp->vm_end,
								     temp->vm_flags);
		temp = temp->vm_next;
	}
	return 0;
}

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

static int __init vm_proc_init(void){
	proc_create("vm_proc", 0, NULL, &vm_proc_fops);
	return 0;
}

static void __exit vm_proc_exit(void){
	remove_proc_entry("vm_proc", NULL);
}

MODULE_LICENSE("GPL");
module_init(vm_proc_init);
module_exit(vm_proc_exit);


