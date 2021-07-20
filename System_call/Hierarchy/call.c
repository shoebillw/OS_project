#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

long call(void)
{
	return syscall(441);
}

int main(int argc, char *argv[])
{
	long activity;
	activity = call();
	
	if (syscall < 0)
	{
		printf("System call failed\n");
	}
	else
	{
		printf("System call success, return %ld\n", activity);
	}
	return 0;
}
