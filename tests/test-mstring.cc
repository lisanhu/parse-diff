//
// Created by Sanhu Li on 2019-05-01.
//

#include <cstring>
#include "catch.hpp"
#include "../mstring.h"

TEST_CASE("no delimiter", "[mstring] [ms_split]") {
	const char *s = "ref|NC_001133|-38543"
	                "<\t10\tref|NC_001133|:23423"
	                ">\t10\tref|NC_001133|:23422"
	                "ref|NC_001133|-75046"
	                "<\t0\tref|NC_001133|:24177"
	                ">\t0\tref|NC_001133|:11745";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}

TEST_CASE("delimiter in the begin", "[mstring] [ms_split]") {
	const char *s = "\nref|NC_001133|-38543"
	                "<\t10\tref|NC_001133|:23423"
	                ">\t10\tref|NC_001133|:23422"
	                "ref|NC_001133|-75046"
	                "<\t0\tref|NC_001133|:24177"
	                ">\t0\tref|NC_001133|:11745";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	CHECK(l == 2);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}

TEST_CASE("delimiter in the middle", "[mstring] [ms_split]") {
	const char *s = "ref|NC_001133|-38543\n"
	                "<\t10\tref|NC_001133|:23423\n"
	                ">\t10\tref|NC_001133|:23422\n"
	                "ref|NC_001133|-75046\n\n"
	                "<\t0\tref|NC_001133|:24177\n"
	                ">\t0\tref|NC_001133|:11745";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}

TEST_CASE("delimiter in the end", "[mstring] [ms_split]") {
	const char *s = "ref|NC_001133|-38543"
	                "<\t10\tref|NC_001133|:23423"
	                ">\t10\tref|NC_001133|:23422"
	                "ref|NC_001133|-75046"
	                "<\t0\tref|NC_001133|:24177"
	                ">\t0\tref|NC_001133|:11745\n";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	CHECK(l == 2);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}

TEST_CASE("delimiter in the begin & middle", "[mstring] [ms_split]") {
	const char *s = "\nref|NC_001133|-38543\n"
	                "<\t10\tref|NC_001133|:23423\n"
	                ">\t10\tref|NC_001133|:23422\n"
	                "ref|NC_001133|-75046\n\n"
	                "<\t0\tref|NC_001133|:24177\n"
	                ">\t0\tref|NC_001133|:11745";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}

TEST_CASE("delimiter in the middle & end", "[mstring] [ms_split]") {
	const char *s = "ref|NC_001133|-38543\n"
	                "<\t10\tref|NC_001133|:23423\n"
	                ">\t10\tref|NC_001133|:23422\n"
	                "ref|NC_001133|-75046\n\n"
	                "<\t0\tref|NC_001133|:24177\n"
	                ">\t0\tref|NC_001133|:11745\n";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}

TEST_CASE("delimiter in the begin & end", "[mstring] [ms_split]") {
	const char *s = "\nref|NC_001133|-38543"
	                "<\t10\tref|NC_001133|:23423"
	                ">\t10\tref|NC_001133|:23422"
	                "ref|NC_001133|-75046"
	                "<\t0\tref|NC_001133|:24177"
	                ">\t0\tref|NC_001133|:11745\n";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}

TEST_CASE("delimiter in both sides and middle", "[mstring] [ms_split]") {
	const char *s = "\nref|NC_001133|-38543\n"
				 "<\t10\tref|NC_001133|:23423\n"
	            ">\t10\tref|NC_001133|:23422\n"
			    "ref|NC_001133|-75046\n\n"
                "<\t0\tref|NC_001133|:24177\n"
                ">\t0\tref|NC_001133|:11745\n";

	mstring ms = ms_from((char *)s, false);
	mstring *strs;
	size_t l = ms_split(ms, '\n', &strs);
	char buf[4096] = "";
	char tmp[4096] = "";
	for (int i = 0; i < l; ++i) {
		CHECK(ms_to_cstr(tmp, strs[i]) >= 0);
		printf("%s\n", tmp);
		sprintf(buf, "%s%s\n", buf, tmp);
	}

	sprintf(tmp, "%s\n", s);
	CHECK(!strcmp(tmp, buf));
}