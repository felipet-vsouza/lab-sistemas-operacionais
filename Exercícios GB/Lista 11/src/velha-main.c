#include <stdio.h>
#include <mqueue.h>
#include "../include/velha-lib.h"

#define clear_screen() printf("\033[H\033[J")

int main(void)
{
	mqd_t queue;
	char* buffer = NULL;
	ssize_t tam_buffer;
	ssize_t nbytes;

	queue = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, 0660, NULL);
	if (queue == (mqd_t) -1) {
		perror("mq_open");
		exit(2);
	}
	return 0;
}
