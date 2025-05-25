#ifndef READ_FILE_H
#define READ_FILE_H

#define LINES_INITIAL_LEN 10
#define BUF_LEN 500

typedef struct {
    char **lines;
    int len;
    int cap;
} lines_t;

lines_t *read_lines(char *filename);

/* adds line to lines_t struct
 * return value:
 *	the address to the line or NULL on error
 */
char *add_line(lines_t *lines, char *line); // *

void free_lines(lines_t *lines);

#endif
