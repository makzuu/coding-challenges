#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILENAME_LEN 100

bool todigit(char *c, int *result);
void fields(int index, char *filename);

struct option {
    char opt;
    char *optarg;
};

int main(int argc, char *argv[]) {
    int options_cap = 0;
    int options_len = 0;
    struct option *options = NULL;

    int files_cap = 0;
    int files_len = 0;
    char **files = NULL;

    char *optstring = ":f:";
    int opt;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
	switch (opt) {
	    case 'f':
		if (options_len == options_cap) {
		    options_cap += 10;
		    if ((options = realloc(options, sizeof(struct option) * options_cap)) == NULL) {
			printf("cut: could not initialize option list\n");
			exit(3);
		    }
		}

		options[options_len].opt = 'f';
		options[options_len].optarg = optarg;

		options_len++;
		break;
	    case '?':
		printf("cut: invalid option -- '%c'\n", optopt);
		exit(1);
		break;
	    case ':':
		printf("cut: option requires an argument -- '%c'\n", optopt);
		exit(2);
		break;
	}
    }

    for (; optind < argc; optind++) {
	if (files_len == files_cap) {
	    files_cap += 10;
	    files = realloc(files, files_cap);
	    if (files == NULL) {
		printf("cut: could not initialize file list\n");
		exit(3);
	    }

	    for (int i = files_len; i < files_cap; i++) {
		files[i] = malloc(MAX_FILENAME_LEN);
		if (files == NULL) {
		    printf("cut: could not initialize file list\n");
		    exit(3);
		}
	    }
	}

	strncpy(files[files_len], argv[optind], MAX_FILENAME_LEN);
	files_len++;
    }

    return 0;
}

bool todigit(char *c, int *result) {
    char *value = c;
    for (; *c != '\0'; ++c) {
	if (*c < '0' || *c > '9') {
	    return false;
	}
    }
    *result = atoi(value);
    return true;
}

void fields(int index, char *filename) {
}
