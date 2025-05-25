#include "read_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

lines_t *read_lines(char *filename) {
    lines_t *lines = malloc(sizeof(lines_t));
    if (lines == NULL) {
	return NULL;
    }
    lines->cap = 0;
    lines->len = 0;
    lines->lines = NULL;

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
	free(lines);
	return NULL;
    }

    int c = 0;
    char buff[BUF_LEN];
    int buff_idx = 0;
    while(fread(&c, 1, 1, f)) {
	if (buff_idx == BUF_LEN) {
	    free(lines);
	    fclose(f);
	    return NULL;
	}
	if (c == '\n') {
	    buff[buff_idx] = '\0';
	    buff_idx = 0;
	    if (add_line(lines, buff) == NULL) {
		free(lines);
		return NULL;
	    }
	} else {
	    buff[buff_idx++] = c;
	}
    }
    if (buff_idx != 0) {
	if (buff_idx == BUF_LEN) {
	    free(lines);
	    fclose(f);
	    return NULL;
	}
	buff[buff_idx] = '\0';
	if (add_line(lines, buff) == NULL) {
		free(lines);
		fclose(f);
		return NULL;
	}
    }

    fclose(f);
    return lines;
}

char *add_line(lines_t *lines, char *line) {
    size_t line_len = strlen(line);
    char *new_line = malloc(line_len + 1);
    if (new_line == NULL) {
	return NULL;
    }
    strcpy(new_line, line);

    if (lines->lines == NULL) {
	lines->cap = LINES_INITIAL_LEN;
	lines->lines = malloc(sizeof(char *) * lines->cap);
	if (lines->lines == NULL) {
	    free(new_line);
	    return NULL;
	}
    }

    if (lines->len == lines->cap) {
	lines->cap = lines->len + LINES_INITIAL_LEN;
	lines->lines = reallocarray(lines->lines, lines->cap, sizeof(char *));
	if (lines->lines == NULL) {
	    free(new_line);
	    free(lines->lines);
	    return NULL;
	}
    }

    lines->lines[lines->len] = new_line;
    lines->len++;

    return new_line;
}

void free_lines(lines_t *lines) {
    for (int i = 0; i < lines->len; i++) {
	free(lines->lines[i]);
    }
    free(lines->lines);
    free(lines);
}
