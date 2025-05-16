#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "dinamic_list.h"

#define MAX_FILENAME_LEN 100

bool todigit(char *c, int *result);
void fields(int index, FILE *f);

struct option {
    char opt;
    char *optarg;
};

int main(int argc, char *argv[]) {
    list_t *options_list = list_init();

    char *optstring = ":f:";
    int opt;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
	switch (opt) {
	    case 'f':
		struct option *opt = malloc(sizeof(struct option));
		if (opt == NULL) {
		    fprintf(stderr, "could not allocate more memory\n");
		    exit(1);
		}
		opt->opt = 'f';
		opt->optarg = optarg;
		list_append(options_list, opt);
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

    list_t *files_list = list_init();
    for (; optind < argc; optind++) {
	char *fname = malloc(MAX_FILENAME_LEN);
	strncpy(fname, argv[optind], MAX_FILENAME_LEN);
	fname[MAX_FILENAME_LEN - 1] = '\0';
	list_append(files_list, fname);
    }

    for (int i = 0; i < files_list->len; i++) {
	FILE *f = fopen(files_list->items[i], "r");
	if (f == NULL) {
	    if (errno == ENOENT) {
		printf("cut: No such file -- '%s'\n", (char *)files_list->items[i]);
		exit(4);
	    }
	    perror("fopen");
	    exit(4);
	}

	for (int j = 0; j < options_list->len; j++) {
	    struct option *opt = options_list->items[j];
	    switch (opt->opt) {
		case 'f':
		    int index = 0;
		    if (!todigit(opt->optarg, &index)) {
			printf("cut: invalid field value '%c'\n", opt->opt);
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
