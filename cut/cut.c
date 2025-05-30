#include "read_file.h"
#include "fields.h"
#include "args.h"

#include <stdio.h>

#define DEBUG

int main(int argc, char *argv[]) {
    args_t *args = parse_args(argc, argv);
    if (args == NULL) {
	fprintf(stderr, "could not parse args\n");
	return 69;
    }

    if (args->indexes.len == 0) {
	fprintf(stderr, "cut: you must specify a list of fields\n");
	return 69;
    }

    if (args->files.len == 0) {
	files_append(&args->files, "-");
    }

#ifdef DEBUG
    printf("files: ");
    for (int i = 0; i < args->files.len; i++) {
	printf("%s ", args->files.items[i]);
    }
    printf("\nindexes: ");
    for (int i = 0; i < args->indexes.len; i++) {
	printf("%d ", args->indexes.items[i]);
    }
    printf("\n");
    if (args->delimiter == '\t') {
	printf("delimiter: \\t\n");
    } else {
	printf("delimiter: %c\n", args->delimiter);
    }
#endif

    for (int i = 0; i < args->files.len; i++) {
	lines_t *lines = read_lines(args->files.items[i]);
	if (lines == NULL) {
	    fprintf(stderr, "could not read file -- %s\n", args->files.items[i]);
	    return 69;
	}
	for (int j = 0; j < lines->len; j++) {
	    fields_t *fields = parse_fields(args->indexes.items, args->indexes.len,
		    lines->lines[j], args->delimiter);
	    if (fields == NULL) {
		fprintf(stderr, "error extracting fields\n");
		return 69;
	    }
	    for (int x = 0; x < fields->len; x++) {
		printf("%s", fields->fields[x]);
		if (x != fields->len - 1) {
		    printf("%c", args->delimiter);
		}
	    }
	    printf("\n");
	    free_fields(fields);
	}
	free_lines(lines);
    }

    free_arguments(args);
}
