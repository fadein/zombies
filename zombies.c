#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	char c;
	printf("press 'w' to call wait()\n"
			"press 'q' to quit\n"
			"press the any key to spawn a new zombie\n\n");

	while (1) {
		read(fileno(stdin), &c, sizeof(char));
		switch (c) {
			case 'w':
			case 'q':
				while ( waitpid(-1, NULL, WNOHANG) > 0) {}
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
