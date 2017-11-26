#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

/* Initalize default module parameters */
static int pid = 1;
static char* module_name = "pid_info";
module_param(pid, int, 0666);
module_param(module_name, charp, 0666);
MODULE_PARM_DESC(pid, "Process ID");

/* This module takes a process's id and displays its gid, uid,
 * children and their pids and names
*/
static int pid_info_init(void){

	/* Pointer for iterating through tasks list */
	struct task_struct* pos;

	/* Pointer for iterating through children list */
	struct task_struct* child;
	
	/* Set flags */
	int flags;

	/* Loop through the tasks if current is not the process requested */
	if(current->pid != pid){
        	list_for_each_entry(pos, &(current->tasks), tasks){
                	if(pos->pid == pid){
				/* Display process information */
                        	printk(KERN_NOTICE"PID: %d\nUID: %lu\nGID: %lu\nParentID: %d\nName: %s\nFlags:\n",pos->pid,
									     				pos->cred->uid,
                                	    	        	                                        pos->cred->gid,
                                        		                                                pos->real_parent->pid,
													pos->real_parent->comm);
				/* Display set flag names */
				flags = pos->flags;
				if(flags & 0x4){
					printk(KERN_NOTICE"\tPF_EXITING\n");
				}
				if(flags & 0x8){
					printk(KERN_NOTICE"\tPF_EXITPIDONE\n");
				}
				if(flags & 0x10){
					printk(KERN_NOTICE"\tPF_VCPU\n");
				}
				if(flags & 0x20){
					printk(KERN_NOTICE"\tPF_WQ_WORKER\n");
				}
				if(flags & 0x40){
					printk(KERN_NOTICE"\tPF_FORKNOEXEC\n");
				}
				if(flags & 0x80){
					printk(KERN_NOTICE"\tPF_MCE_PROCESS\n");
				}
				if(flags & 0x100){
					printk(KERN_NOTICE"\tPF_SUPERPRIV\n");
				}
				if(flags & 0x200){
					printk(KERN_NOTICE"\tPF_DUMPCORE\n");
				}
				if(flags & 0x400){
					printk(KERN_NOTICE"\tPF_SIGNALED\n");
				}
				if(flags & 0x800){
					printk(KERN_NOTICE"\tPF_MEMALLOC\n");
				}
				if(flags & 0x1000){
					printk(KERN_NOTICE"\tPF_NPROC_EXCEEDED\n");
				}
				if(flags & 0x2000){
					printk(KERN_NOTICE"\tPF_USED_MATH\n");
				}
				if(flags & 0x4000){
					printk(KERN_NOTICE"\tPF_USED_ASYNC\n");
				}
				if(flags & 0x8000){
					printk(KERN_NOTICE"\tPF_NOFREEZE\n");
				}
				if(flags & 0x10000){
					printk(KERN_NOTICE"\tPF_FROZEN\n");
				}
				if(flags & 0x20000){
					printk(KERN_NOTICE"\tPF_FSTRANS\n");
				}
				if(flags & 0x40000){
					printk(KERN_NOTICE"\tPF_KSWAPD\n");
				}
				if(flags & 0x80000){
					printk(KERN_NOTICE"\tPF_MEMALLOC_NOIO\n");
				}
				if(flags & 0x100000){
					printk(KERN_NOTICE"\tPF_LESS_THROTTLE\n");
				}
				if(flags & 0x200000){
					printk(KERN_NOTICE"\tPF_KTHREAD\n");
				}
				if(flags & 0x400000){
					printk(KERN_NOTICE"\tPF_RANDOMIZE\n");
				}
				if(flags & 0x800000){
					printk(KERN_NOTICE"\tPF_SWAPWRITE\n");
				}
				if(flags & 0x1000000){
					printk(KERN_NOTICE"\tPF_SPREAD_PAGE\n");
				}
				if(flags & 0x2000000){
					printk(KERN_NOTICE"\tPF_SPREAD_SLAB\n");
				}
				if(flags & 0x4000000){
					printk(KERN_NOTICE"\tPF_NO_SETAFFINITY\n");
				}
				if(flags & 0x8000000){
					printk(KERN_NOTICE"\tPF_MCE_EARLY\n");
				}
				if(flags & 0x20000000){
					printk(KERN_NOTICE"\tPF_MUTEX_TESTER\n");
				}
				if(flags & 0x40000000){
					printk(KERN_NOTICE"\tPF_FREEZER_SKIP\n");
				}
				if(flags & 0x80000000){
					printk(KERN_NOTICE"\tPF_SUSPEND_TASK\n");
				}
				printk(KERN_NOTICE"Children:\n");
        			list_for_each_entry(child, &(pos->children), sibling){
                			printk(KERN_NOTICE"\tChild PID:%d\n\tName: %s\n",child->pid, child->comm);
       				 }

                        	break;
               		}
        	}

	}

	/* Access informaiton directly from current */
	else{
		printk(KERN_NOTICE"PID: %d\nUID: %lu\nGID: %lu\nParentID: %d\nParent Name: %s\nFlags:\n",current->pid,
											current->cred->uid,
                                                                               		current->cred->gid,
                                       			                      		current->real_parent->pid,
		/* Display set flag name */				       current->real_parent->comm);
		flags = current->flags;
                if(flags & 0x4){
                	printk(KERN_NOTICE"\tPF_EXITING\n");
                }
                if(flags & 0x8){
                        printk(KERN_NOTICE"\tPF_EXITPIDONE\n");
                }
                if(flags & 0x10){
                        printk(KERN_NOTICE"\tPF_VCPU\n");
                }
                if(flags & 0x20){
                        printk(KERN_NOTICE"\tPF_WQ_WORKER\n");
                }
                if(flags & 0x40){
                	printk(KERN_NOTICE"\tPF_FORKNOEXEC\n");
                }
                if(flags & 0x80){
                        printk(KERN_NOTICE"\tPF_MCE_PROCESS\n");
                }
		if(flags & 0x100){
                        printk(KERN_NOTICE"\tPF_SUPERPRIV\n");
                }
                if(flags & 0x200){
                        printk(KERN_NOTICE"\tPF_DUMPCORE\n");
                }
                if(flags & 0x400){
                        printk(KERN_NOTICE"\tPF_SIGNALED\n");
                }
		if(flags & 0x800){
                        printk(KERN_NOTICE"\tPF_MEMALLOC\n");
                }
                if(flags & 0x1000){
                        printk(KERN_NOTICE"\tPF_NPROC_EXCEEDED\n");
                }
                if(flags & 0x2000){
                        printk(KERN_NOTICE"\tPF_USED_MATH\n");
                }
                if(flags & 0x4000){
                        printk(KERN_NOTICE"\tPF_USED_ASYNC\n");
                }
                if(flags & 0x8000){
                        printk(KERN_NOTICE"\tPF_NOFREEZE\n");
                }
		if(flags & 0x10000){
                        printk(KERN_NOTICE"\tPF_FROZEN\n");
                }
                if(flags & 0x20000){
                        printk(KERN_NOTICE"\tPF_FSTRANS\n");
                }
                if(flags & 0x40000){
                        printk(KERN_NOTICE"\tPF_KSWAPD\n");
                }
                if(flags & 0x80000){
                        printk(KERN_NOTICE"\tPF_MEMALLOC_NOIO\n");
                }
                if(flags & 0x100000){
                        printk(KERN_NOTICE"\tPF_LESS_THROTTLE\n");
                }
                if(flags & 0x200000){
                        printk(KERN_NOTICE"\tPF_KTHREAD\n");
            	}
		if(flags & 0x400000){
                        printk(KERN_NOTICE"\tPF_RANDOMIZE\n");
                }
                if(flags & 0x800000){
                        printk(KERN_NOTICE"\tPF_SWAPWRITE\n");
                }
                if(flags & 0x1000000){
                        printk(KERN_NOTICE"\tPF_SPREAD_PAGE\n");
                }
                if(flags & 0x2000000){
                        printk(KERN_NOTICE"\tPF_SPREAD_SLAB\n");
                }
                if(flags & 0x4000000){
                        printk(KERN_NOTICE"\tPF_NO_SETAFFINITY\n");
                }
		if(flags & 0x80000000){
                        printk(KERN_NOTICE"\tPF_SUSPEND_TASK\n");
                }
                printk(KERN_NOTICE"Children:\n");
        	list_for_each_entry(child, &(current->children), sibling){
                	printk(KERN_NOTICE"\tChild PID:%d\n\tChild Name: %s\n",child->pid, child->comm);
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
