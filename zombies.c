#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void usage(void) {
		printf("\nINSTRUCTIONS:\n"
						"=============\n"
						"press 'w' to call wait()\n"
						"press 'q' to quit\n"
						"press '?' to read these instructions again\n"
						"press the any key to spawn a new zombie\n\n");
}

int main(void) {
	char c;
	usage();

	while (1) {
		read(fileno(stdin), &c, sizeof(char));
		switch (c) {
			case 'w':
			case 'q':
				{
					pid_t child;
					while ( (child = waitpid(-1, NULL, WNOHANG)) > 0)
						printf("Reaped child %d\n", child);
				}
				break;
			case '?':
				usage();
				break;
			default:
				{
					pid_t child = fork();
					if (!child)
						c = 'q';
					else
						printf("Forked a child %d\n", child);
				}
		}
		if (c == 'q')
			break;
	}

	return 0;
}
