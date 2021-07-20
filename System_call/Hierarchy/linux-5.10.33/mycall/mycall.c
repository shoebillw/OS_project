#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/init.h>

SYSCALL_DEFINE0(mycall)
{
	printk(" This message is from the new system call.");
	return 0;
}
