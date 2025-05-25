#include "read_file.h"
#include "fields.h"
#include <stdio.h>

#define INDEXES_LEN 2

int main(void) {
    lines_t *lines = read_lines("sample.tsv");
    int indexes[INDEXES_LEN] = { 1, 3 };
    for (int i = 0; i < lines->len; i++) {
	fields_t *flds = fields(indexes, INDEXES_LEN, lines->lines[i], '\t');
	for (int j = 0; j < flds->len; j++) {
	    printf("%s\t", flds->fields[j]);
	}
	free_fields(flds);
	printf("\n");
    }
    free_lines(lines);
}
