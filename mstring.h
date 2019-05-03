//
// Created by Sanhu Li on 2019-04-29.
//

#ifndef PARSE_DIFF_MSTRING_H
#define PARSE_DIFF_MSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>

typedef struct mstring {
	int  cap, len;
	char *s, own;
} mstring;

mstring ms_borrow(char *s, int l);

mstring ms_own(const char *s, int l);

mstring ms_from(char *s, int own);

void ms_destroy(mstring s);
bool ms_start_with(mstring s);

/**
 * Split an mstring object using a char delimiter, will store the sub-strings in parameter __ss__.
 *
 * @param s The mstring object to be split
 * @param deli The delimiter
 * @param ss The returned pointer where the sub-strings are stored
 * @return The number of sub-strings are stored
 */
size_t ms_split(mstring s, char deli, mstring **ss);

/**
 * Convert an mstring object to C-style string
 *
 * The returned C-style string must be freed
 * @param ms The mstring object to be converted
 * @return The C-style string
 */
int ms_to_cstr(char *dest, mstring ms);

/**
 * Merging two mstring objects / Append the second mstring object to the first
 *
 * The result object has to own the data
 * @param ms1 The head mstring object
 * @param ms2 The tail mstring object
 * @return mstring object with ms1 as head, and ms2 as tail
 */
mstring ms_merge(mstring ms1, mstring ms2);

#ifdef __cplusplus
};
#endif

#endif //PARSE_DIFF_MSTRING_H
