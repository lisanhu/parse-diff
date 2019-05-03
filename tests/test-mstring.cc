//
// Created by Sanhu Li on 2019-05-01.
//

#include <cstring>
#include "catch.hpp"
#include "../mstring.h"

TEST_CASE("testing ms_split", "[mstring] [ms_split]") {
	const char *s = "\nref|NC_001133|-38543\n"
				 "<\t10\tref|NC_001133|:23423\n"
	            ">\t10\tref|NC_001133|:23422\n"
			    "ref|NC_001133|-75046\n\n"
                "<\t0\tref|NC_001133|:24177\n"
                ">\t0\tref|NC_001133|:11745\n";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	char buf[4096];
	for (int i = 0; i < l; ++i) {
		char tmp[4096];
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	CHECK(!strcmp(s, buf));
}