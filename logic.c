//
// Created by Sanhu Li on 2019-05-03.
//

#include "logic.h"

#ifndef try_free
#define try_free(x) if ((x) != NULL) { free((x)); (x) = NULL; }


typedef struct line_parse_item_array {
	line_parse_item *store;
	size_t len, cap;
} lpi_array;

static lpi_array new_lpi_array();

static void lpia_destroy(lpi_array arr);

static void lpia_push(lpi_array arr, line_parse_item item);


size_t parse_block(const char *content, size_t block_size, line_parse_item **items) {
	mstring bcontent = ms_borrow((char *) content, block_size);
	mstring *lines;
	size_t l = ms_split(bcontent, '\n', &lines);

	if (l < 2) {

	}

	for (int i = 0; i < block_size; ++i) {

	}
	ms_destroy(bcontent);
	return 0;
}

lpi_array new_lpi_array() {
	const size_t cap = 100;
	line_parse_item *store = malloc(cap * sizeof(line_parse_item));
	lpi_array arr = {.store = store, .len = 0, .cap = cap};
	return arr;
}

void lpia_destroy(lpi_array arr) {
	try_free(arr.store)
	arr.cap = arr.len = 0;
}

void lpia_push(lpi_array arr, line_parse_item item) {
	if (arr.len + 1 >= arr.cap) {
		arr.cap += 1;
		arr.cap *= 2;
		arr.store = realloc(arr.store, arr.cap * sizeof(line_parse_item));
	}
	arr.store[arr.len++] = item;
}


#undef try_free
#endif
