//
// Created by Sanhu Li on 2019-05-01.
//

#ifndef PARSE_DIFF_MPRINTF_H
#define PARSE_DIFF_MPRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "mstring.h"

typedef char *(*fmt_func)(void *item);

typedef struct format_specifier {
	int pos;
	char type, registered;
} format_specifier;

int register_specifier(char type, fmt_func func);

int parse_format_specifier(const char *fmt, format_specifier **specifiers);

int msprintf(char *__restrict__ buffer, const char *__restrict__ fmt, ...);

int mfprintf(FILE *__restrict__ stream, const char *__restrict__ fmt, ...);

int mprintf(const char *__restrict__ fmt, ...);

void mp_release();

/**
 * return a heap-allocated string by replacing the characters in __ori__[start, end) with __repl__
 *
 * The returned string must be destroyed after usage
 * This function can only compiles where __asprintf__ is supported
 *
 * @param ori Original string to be processed
 * @param start Start position of the string slice to be replaced
 * @param end Start position of the string slice to be kept
 * 				Could be computed by __start__ + __length__
 * @param repl The replacement string
 * @return The heap allocated string after replacement
 */
mstring string_slice_replace(const char *ori, int start, int end, const char *repl);


#ifdef __cplusplus
}
#endif

#endif //PARSE_DIFF_MPRINTF_H
