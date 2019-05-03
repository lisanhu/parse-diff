//
// Created by Sanhu Li on 2019-05-03.
//

#ifndef PARSE_DIFF_LOGIC_H
#define PARSE_DIFF_LOGIC_H

#include "mstring.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct line_parse_item {
	mstring str;
	/// when the str is definitely a full line, valid is true
	/// ow, valid is false
	char valid;
} line_parse_item;


size_t parse_block(const char *content, size_t block_size, line_parse_item **items);


#ifdef __cplusplus
};
#endif

#endif //PARSE_DIFF_LOGIC_H
