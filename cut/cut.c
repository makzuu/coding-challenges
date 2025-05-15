#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_FILENAME_LEN 100

bool todigit(char *c, int *result);
void fields(int index, FILE *f);

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

    for (int i = 0; i < files_len; i++) {
	FILE *f = fopen(files[i], "r");
	if (f == NULL) {
	    if (errno == ENOENT) {
		printf("cut: No such file -- '%s'\n", files[i]);
		exit(4);
	    }
	    perror("fopen");
	    exit(4);
	}

	for (int j = 0; j < options_len; j++) {
	    switch (options[j].opt) {
		case 'f':
		    int index = 0;
		    if (!todigit(options[j].optarg, &index)) {
			printf("cut: invalid field value '%c'\n", options[j].opt);
			exit(5);
		    }
		    fields(index, f);
		    break;
	    }
	}
	
	fclose(f);
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

#define MAX_LINE_LEN 500

void fields(int index, FILE *f) {
    char *line = malloc(MAX_LINE_LEN);
    char c = 0;
    int idx = 0;
    while (fread(&c, 1, 1, f)) {
	if (c == '\n') {
	    line[idx] = '\0';
	    idx = 0;
	    printf("%s\n", line);
	} else {
	    if (idx == MAX_LINE_LEN - 1) {
		printf("cut: max number of characters per line exceded\n");
		exit(6);
	    }
	    line[idx++] = c;
	}
    }
    line[idx] = '\0';
    printf("%s\n", line);
	
    if (ferror(f)) {
	printf("cut: error while reading file\n");
	exit(6);
    }
}
