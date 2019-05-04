//
// Created by Sanhu Li on 2019-05-03.
//

#ifndef PARSE_DIFF_LOGIC_H
#define PARSE_DIFF_LOGIC_H

#include "mstring.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct parse_result {
	size_t missed, redundant, wrong;
} p_result;

p_result parse_full_text(const char *text, int length, int truth_pos);


#ifdef __cplusplus
};
#endif

#endif //PARSE_DIFF_LOGIC_H
