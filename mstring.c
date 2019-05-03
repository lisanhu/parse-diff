//
// Created by Sanhu Li on 2019-04-29.
//

#include "mstring.h"
#include <string.h>
#include <stdio.h>

mstring ms_borrow(char *s, int l) { // NOLINT(readability-non-const-parameter)
	mstring ms = {.s = s, .len = l, .cap = 0, .own = false};
	return ms;
}

mstring ms_own(const char *s, int l) {
	char *n = strndup(s, l);
	mstring ms = {.s = n, .len = l, .cap = l + 1, .own = true};
	return ms;
}

mstring ms_from(char *s, int own) {
	size_t l = strlen(s);
	if (own) {
		return ms_own(s, l);
	} else {
		return ms_borrow(s, l);
	}
}

size_t ms_split(mstring s, char deli, mstring **ss) {
	size_t counter = 0;
	for (size_t i = 0; i < s.len; ++i) {
		if (s.s[i] == deli) counter++;
	}

	*ss = (mstring *) malloc(++counter * sizeof(mstring));
	size_t pos = 0;
	counter = 0;
	for (size_t i = 0; i < s.len; ++i) {
		if (s.s[i] == deli) {
			mstring ms = {.s = s.s + pos, .len = i - pos, .cap = 0, .own = false};
			(*ss)[counter++] = ms;
			pos = i + 1;
		}
	}

	if (pos <= s.len) {
		mstring ms = {.s = s.s + pos, .len = s.len - pos, .cap = 0, .own = false};
		(*ss)[counter++] = ms;
	}

	return counter;
}

void ms_destroy(mstring s) {
	if (s.own && s.cap > 0) {
		free(s.s);
	}
	s.s = NULL;
	s.cap = s.len = 0;
	s.own = false;
}

int ms_to_cstr(char *dest, mstring ms) {
	int bytes = sprintf(dest, "%.*s", ms.len, ms.s);
	return bytes;
}

mstring ms_merge(mstring ms1, mstring ms2) {
	char *buf = malloc((ms1.len + ms2.len) * sizeof(char));
	strncpy(buf, ms1.s, ms1.len);
	strncpy(buf + ms1.len, ms2.s, ms2.len);
	int len = ms1.len + ms2.len;
	mstring merged = {.s = buf, .len = len, .own = true, .cap = len};
	ms_destroy(ms1);
	ms_destroy(ms2);
	return merged;
}

mstring ms_borrow_copy(mstring ori) {
	mstring ms = {.s = ori.s, .len = ori.len, .cap = 0, .own = false};
	return ms;
}

mstring ms_own_copy(mstring ori) {
	mstring ms = {.s = strndup(ori.s, ori.len), .len = ori.len, .cap = ori.len + 1, .own = true};
	return ms;
}
