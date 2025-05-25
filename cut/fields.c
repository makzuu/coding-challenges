#include "fields.h"
#include <stdlib.h>
#include <string.h>

fields_t *fields(int *indexes, int indexes_len, char *line, char delimiter) {
    fields_t *f = malloc(sizeof(fields_t));
    if (f == NULL) {
	return NULL;
    }
    f->len = 0;
    f->fields = NULL;

    char buff[BUFF_LEN];
    int buff_idx = 0;
    int cur_idx = 1;
    for (int i = 0; line[i]; i++) {
	if (buff_idx == BUFF_LEN) {
	    free(f);
	    return NULL;
	}
	if (line[i] == delimiter) {
	    buff[buff_idx] = '\0';
	    buff_idx = 0;
	    if (add_field(f, indexes, indexes_len, buff, cur_idx) == NULL) {
		free(f);
		return NULL;
	    }
	    cur_idx++;
	} else {
	    buff[buff_idx++] = line[i];
	}
    }
    if (buff_idx != 0) {
	if (buff_idx == BUFF_LEN) {
	    free(f);
	    return NULL;
	}
	buff[buff_idx] = '\0';
	if (add_field(f, indexes, indexes_len, buff, cur_idx) == NULL) {
	    free(f);
	    return NULL;
	}
    }

    return f;
}

char *add_field(fields_t *f, int *indexes, int indexes_len, char *buff, int cur_idx) {
    for (int j = 0; j < indexes_len; j++) {
	if (cur_idx == indexes[j]) {
	    f->fields = realloc(f->fields, sizeof(char *) * (f->len + 1));
	    if (f->fields == NULL) {
		return NULL;
	    }
	    char *new_field = malloc(strlen(buff) + 1);
	    if (new_field == NULL) {
		return NULL;
	    }
	    strcpy(new_field, buff);
	    f->fields[f->len++] = new_field;
	    return new_field;
	}
    }
}

void free_fields(fields_t *fields) {
    for (int i = 0; i < fields->len; i++) {
	free(fields->fields[i]);
    }
    free(fields->fields);
    free(fields);
}
