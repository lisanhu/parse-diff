//
// Created by Sanhu Li on 2019-05-03.
//

#include "logic.h"

#ifndef try_free
#define try_free(x) if ((x) != NULL) { free((x)); (x) = NULL; }


typedef struct line_parse_item {
	mstring str;
	/// when the str is definitely a full line, valid is true
	/// ow, valid is false
	char valid;
} line_parse_item;


size_t parse_block(const char *content, size_t length, line_parse_item **items);


typedef struct line_parse_item_array {
	line_parse_item *store;
	size_t len, cap;
} lpi_array;

static lpi_array new_lpi_array();

static void lpia_destroy(lpi_array arr);

static void lpia_push(lpi_array arr, line_parse_item item);


size_t parse_block(const char *content, size_t length, line_parse_item **items) {
//	int state = 0;
//	size_t start = 0, cur = 0;
//
//	for (int i = 0; i < length; ++i) {
//		if (i + 1 < length && content[i] == '\n' && content[i + 1] )
//	}

	//todo to be implemented for parallel processing

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

p_result parse_full_text(const char *text, int length, int truth_pos) {
	p_result result = {.missed = 0, .redundant = 0, .wrong = 0};
	char in_truth = "<>"[truth_pos];
	char in_compared = "><"[truth_pos];

	mstring ms = ms_borrow((char *) text, length);
	mstring *lines;
	size_t num_lines = ms_split(ms, '\n', &lines);

	char begin = false, intruth = false, incompared = false;

	for (size_t i = 0; i < num_lines; ++i) {
		if (!ms_start_with(lines[i], '>') && !ms_start_with(lines[i], '<')) {
			if (intruth && incompared) {
				result.wrong++;
			} else if (intruth && !incompared) {
				result.missed++;
			} else if (!intruth && incompared) {
				result.redundant++;
			}
			begin = true;
			intruth = false;
			incompared = false;
		} else if (ms_start_with(lines[i], in_truth)) {
			intruth = true;
			begin = false;
		} else if (ms_start_with(lines[i], in_compared)) {
			incompared = true;
			begin = false;
		}
	}

	if (!begin) {
		if (intruth && incompared) {
			result.wrong++;
		} else if (intruth && !incompared) {
			result.missed++;
		} else if (!intruth && incompared) {
			result.redundant++;
		}
	}

	ms_destroy(ms);

	return result;
}
