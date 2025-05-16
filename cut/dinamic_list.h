#ifndef DINAMIC_LIST_H
#define DINAMIC_LIST_H

struct list_t {
    int len;
    int capacity;
    void **items;
};

typedef struct list_t list_t;

list_t *list_init(void);
void list_destroy(list_t *l);
void list_append(list_t *l, void *item);

#define INCREMENT 10

#endif
