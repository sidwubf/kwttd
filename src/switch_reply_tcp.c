#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define NOTIFY 001
#define TURN_ON 101
#define TURN_OFF 102
#define GET_INFO 201

int
main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <Port> <Mac>\n", argv[0]);
		exit(1);
	}

	printf("saaaaa\n");
	exit(0);
}