#include "read_file.h"
#include <stdio.h>

int main(void) {
    lines_t *lines = read_lines("fourchords.csv");
    for (int i = 0; i < lines->len; i++) {
	printf("%d: %s\n", i + 1, lines->lines[i]);
    }
    free_lines(lines);
}
