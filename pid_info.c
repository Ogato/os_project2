#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

static int pid = 1;
static char* module_name = "pid_info";
module_param(pid, int, 0666);
module_param(module_name, charp, 0666);
MODULE_PARM_DESC(pid, "Process ID");

static int pid_info_init(void){
	printk(KERN_NOTICE"Loading Module");
	if(current->pid != pid){
		printk(KERN_NOTICE"Finding Task");
        	struct task_struct* pos;
        	list_for_each_entry(pos, &(current->tasks), tasks){
                	if(pos->pid == pid){
                        	printk(KERN_NOTICE"PID: %d\nUID: %d\nGID: %d\nParentID: %d\nName: %s\nFlags: %d\nChildren:\n",pos->pid,
									     				pos->cred->uid,
                                	    	        	                                        pos->cred->gid,
                                        		                                                pos->real_parent->pid,
													pos->real_parent->comm,
													pos->flags);
			        struct task_struct*  child;
        			list_for_each_entry(child, &(pos->children), sibling){
                			printk(KERN_NOTICE"\tChild PID:%d\nName: %s\n",child->pid, child->comm);
       				 }

                        	break;
               		}
        	}

	}
	else{
		printk(KERN_NOTICE"PID: %d\nUID: %d\nGID: %d\nParentID: %d\nParent Name: %s\nFlags: %d\nChildren:\n",current->pid,
											current->cred->uid,
                                                                               		current->cred->gid,
                                       			                      		current->real_parent->pid,
											current->real_parent->comm,
											current->flags);
	        struct task_struct*  child;
        	list_for_each_entry(child, &(current->children), sibling){
                	printk(KERN_NOTICE"\tChild PID:%d\nChild Name: %s\n",child->pid, child->comm);
        	}
	}

	return 0;
}

static void pid_info_exit(void){}

module_init(pid_info_init);
module_exit(pid_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Group 16");
MODULE_DESCRIPTION("Displays informaiton regarding a particular process given its process id.");
