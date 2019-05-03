//
// Created by Sanhu Li on 2019-05-01.
//

#include <string.h>
#include <stdarg.h>

#include "mprintf.h"
#include "mstring.h"

char *registered_specifier_types;
int num_registered_specifiers;
int registered_specifier_capacity;
fmt_func *format_funtions;


int register_specifier(char type, fmt_func func) {
	if (num_registered_specifiers + 1 > registered_specifier_capacity) {
		registered_specifier_capacity += 1;
		registered_specifier_capacity *= 2;
		registered_specifier_types = realloc(registered_specifier_types,
		                                     registered_specifier_capacity * sizeof(char));
		format_funtions = realloc(format_funtions,
		                          registered_specifier_capacity * sizeof(fmt_func));
	}

	registered_specifier_types[num_registered_specifiers] = type;
	format_funtions[num_registered_specifiers] = func;

	num_registered_specifiers += 1;
}

int parse_format_specifier(const char *fmt, format_specifier **specifiers) {
	size_t l = strlen(fmt);
	int state = 0, counter = 0;
	for (size_t i = 0; i < l; ++i) {
		if (state == 1) {
			state = 0;
			counter++;
		} else if (state == 0) {
			if (fmt[i] == '%') {
				state = 1;
			}
		}
	}

	*specifiers = malloc(counter * sizeof(format_specifier));
	counter = 0;
	state = 0;
	for (size_t i = 0; i < l; ++i) {
		if (state == 1) {
			state = 0;
			format_specifier fs = {.pos = i - 1, .type = fmt[i], .registered = false};

			for (int j = 0; j < num_registered_specifiers; ++j) {
				if (registered_specifier_types[j] == fmt[i]) {
					fs.registered = true;
					break;
				}
			}

			(*specifiers)[counter++] = fs;
		} else if (state == 0) {
			if (fmt[i] == '%') {
				state = 1;
			}
		}
	}
	return counter;
}

int msprintf(char *buffer, const char *fmt, ...) {
	format_specifier *specifiers;
	int num_specifiers = parse_format_specifier(fmt, &specifiers);
	va_list args, backup;
	va_start(args, fmt);
	va_copy(backup, args);
	for (int i = 0; i < num_specifiers; ++i) {
		if (specifiers[i].registered) {

		} else {
//			va_arg(args, )
			// todo: how do we know the type of the parameter?
			// stuck here
		}
	}
	va_end(args);
	va_end(backup);
	return 0;
}

int mfprintf(FILE *stream, const char *fmt, ...) {
	return 0;
}

int mprintf(const char *fmt, ...) {
	return 0;
}

mstring string_slice_replace(const char *ori, int start, int end, const char *repl) {
	char *buf;
	size_t len = strlen(ori);
	int l = asprintf(&buf, "%.*s%s%.*s", start, ori, repl, (int) (len - end), ori + end);
	mstring ms = {.s = buf, .len = l, .cap = l, .own = true};
	return ms;
}

void mp_release() {
	if (registered_specifier_capacity > 0) {
		free(registered_specifier_types);
		free(format_funtions);
	}
	registered_specifier_capacity = 0;
	num_registered_specifiers = 0;
}
