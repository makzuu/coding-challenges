#include "args.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int parse_indexes(char *indexes) {
    static int i = 0;
    char buff[BUFF_LEN];
    int buff_idx = 0;
    while (i < strlen(indexes)) {
	if (buff_idx == BUFF_LEN) {
	    return 0;
	}
	if (indexes[i] == ' ' || indexes[i] == ',') {
	    buff[buff_idx] = '\0';
	    i++;
	    return atoi(buff);
	}
	buff[buff_idx++] = indexes[i];
	i++;
    }
    if (buff_idx != 0) {
	buff[buff_idx] = '\0';
	return atoi(buff);
    }

    return 0;
}

args_t *parse_args(int argc, char *argv[]) {
    args_t *args = malloc(sizeof(args_t));
    args->files.items = NULL;
    args->indexes.items = NULL;
    args->delimiter = '\t';

    int opt = 0;
    while ((opt = getopt(argc, argv, "-:f:d:")) != -1) {
	switch (opt) {
	    case 'f':
		int index = 0;
		while (index = parse_indexes(optarg)) {
		    if (indexes_append(&args->indexes, index) == -1) {
			free(args);
			return NULL;
		    }
		}
		break;
	    case 'd':
		args->delimiter = *optarg;
		break;
	    case 1:
		if (files_append(&args->files, optarg) == NULL) {
		    free(args);
		    return NULL;
		}
		break;
	    case '?':
		fprintf(stderr, "cut: unknown option -- %c\n", optopt);
		return NULL;
		break;
	    case ':':
		fprintf(stderr, "cut: option requires an argument -- %c\n", optopt);
		return NULL;
		break;
	}
    }

    return args;
}

char *files_append(file_list_t *files, char *filename) {
    int new_len = files->len + 1;
    files->items = realloc(files->items, new_len * sizeof(char *));
    if (files->items == NULL) {
	return NULL;
    }

    size_t filename_len = strlen(filename) + 1;
    char *tmp = malloc(filename_len);
    if (tmp == NULL) {
	free(files->items);
	return NULL;
    }
    strcpy(tmp, filename);
    files->items[files->len] = tmp;

    files->len = new_len;

    return tmp;
}

int indexes_append(index_list_t *indexes, int item) {
    int new_len = indexes->len + 1;
    indexes->items = realloc(indexes->items, new_len * sizeof(int));
    if (indexes->items == NULL) {
	return -1;
    }

    indexes->items[indexes->len] = item;

    indexes->len = new_len;

    return indexes->len - 1;
}

void free_arguments(args_t *args) {
    assert(args != NULL);
    if (args->files.items != NULL) {
	for (int i = 0; i < args->files.len; i++) {
	    free(args->files.items[i]);
	}
	free(args->files.items);
    }
    if (args->indexes.items != NULL) {
	free(args->indexes.items);
    }
    free(args);
}
