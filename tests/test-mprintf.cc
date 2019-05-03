//
// Created by Sanhu Li on 2019-05-01.
//

#include <cstring>
#include "catch.hpp"
#include "../mstring.h"
#include "../mprintf.h"


TEST_CASE("testing string_slice_replace", "[.mprintf][.string_slice_replace]") {
	const char *ori = "abccghijklmn";
	const char *repl = "cdef";
	const char *result = "abcdefghijklmn";
	int start = 2, end = 4;
	mstring ms = string_slice_replace(ori, start, end, repl);
	char *buf;
	int l = asprintf(&buf, "%.*s", ms.len, ms.s);
	CHECK(l == strlen(result));
	CHECK(!strcmp(buf, result));
	ms_destroy(ms);
}

TEST_CASE("testing parse_format_specifier", "[.mprintf][.parse_format_specifier]") {
	const char *s = "abc%c%%gh%ijk%lmn%";
	const char *results = "c%il";
	int positions[] = {3, 5, 9, 13};
	format_specifier *specifiers;
	int l = parse_format_specifier(s, &specifiers);
	CHECK(l == strlen(results));

	for (int i = 0; i < l; ++i) {
		CHECK(specifiers[i].type == results[i]);
		CHECK(specifiers[i].registered == 0);
		CHECK(specifiers[i].pos == positions[i]);
	}
	free(specifiers);
}