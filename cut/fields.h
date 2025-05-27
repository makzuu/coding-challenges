#ifndef FIELDS_H
#define FIELDS_H

#define BUFF_LEN 500

typedef struct {
    char **fields;
    int len;
} fields_t;

fields_t *parse_fields(int *indexes, int indexes_len, char *line, char delimiter);

char *add_field(fields_t *f, int *indexes, int indexes_len, char *buff, int cur_idx);

void free_fields(fields_t *fields);

#endif
