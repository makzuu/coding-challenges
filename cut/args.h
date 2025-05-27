#ifndef ARGS_H
#define ARGS_H

typedef struct {
    char **items;
    int len;
} file_list_t;

typedef struct {
    int *items;
    int len;
} index_list_t;

typedef struct {
    file_list_t files;
    index_list_t indexes;
    char delimiter;
} args_t;

#define BUFF_LEN 500

int parse_indexes(char *indexes);
args_t *parse_args(int argc, char *argv[]);
char *files_append(file_list_t *files, char *filename);
void free_files(file_list_t *files);
int indexes_append(index_list_t *indexes, int item);
void free_indexes(index_list_t *indexes);

#endif
