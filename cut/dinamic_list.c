#include "dinamic_list.h"
#include <stdlib.h>
#include <stdio.h>

list_t *list_init(void) {
    list_t *l = malloc(sizeof(list_t));
    if (l == NULL) {
	fprintf(stderr, "could not initialize list\n");
	exit(1);
    }
    l->capacity += INCREMENT;
    l->items = malloc(l->capacity * sizeof(void *));
    if (l->items == NULL) {
	fprintf(stderr, "could not initialize list\n");
	exit(1);
    }

    return l;
}

void list_destroy(list_t *l) {
    for (int i = 0; i < l->len; i++) {
	free(l->items[i]);
    }
    free(l->items);
    free(l);
}

void list_append(list_t *l, void *item) {
    if (l->len == l->capacity) {
	l->capacity += INCREMENT;
	l->items = realloc(l->items, (l->capacity - l->len) * sizeof(void *));
	if (l->items == NULL) {
	    fprintf(stderr, "could not allocate more memory\n");
	    exit(1);
	}
    }
    l->items[l->len] = item;
    l->len++;
}
