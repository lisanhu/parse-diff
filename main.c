#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mlog/logger.h"


typedef struct param {
	uint64_t total_reads;
	const char *diff_path;
	int ground_truth_pos;
	int num_threads;
} param;


typedef struct context {
	mlog logger;
} context;


static int usage(int argc, const char **argv);

static context init(int argc, const char **argv);

static param parse_params(int argc, const char **argv);


int main(int argc, const char *argv[]) {
	if (argc < 2 || argc > 5) {
		return usage(argc, argv);
	}

	context ctx = init(argc, argv);


	return 0;
}

context init(int argc, const char **argv) {
	context ctx;
	ctx.logger = new_mlogger(NULL);
	param p = parse_params(argc, argv);
	mlog log = ctx.logger;

	log.mvlog(&log, "Done parsing commandline parameters");
	log.mvlog(&log, "diff-file-path: %s", p.diff_path);
	log.mvlog(&log, "ground-truth-pos: %d", p.ground_truth_pos);
	log.mvlog(&log, "total-reads: %lu", p.total_reads);
	log.mvlog(&log, "num-threads: %d", p.num_threads);



	return ctx;
}

int usage(int argc, const char **argv) {
	if (argc < 1) {
		fprintf(stderr, "argc < 1, impossible!\n");
		return -1;
	}

	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s <diff-file> [ground-truth-pos] [total-reads] [num-threads]\n", argv[0]);
	fprintf(stderr, "\n");
	fprintf(stderr, "%-25sThe diff file generated from bam diff\n", "<diff-file>");
	fprintf(stderr, "%-25sWhich file is the ground truth? 0 or 1? (Default 0)\n", "[ground-truth-pos]");
	fprintf(stderr, "%-25sThe total number of reads, to compute the percentage numbers, will only output number of reads if not specified\n", "[total-reads]");
	fprintf(stderr, "%-25sThe number of threads wishing to use to accelerate the process, currently not supported yet\n", "[num-threads]");
	return -1;
}

param parse_params(int argc, const char **argv) {
	param p;
	p.diff_path = argv[1];
	p.ground_truth_pos = 0;
	p.total_reads = 0;
	p.num_threads = 1;
	if (argc > 2) {
		p.ground_truth_pos = strtol(argv[2], NULL, 0);
	}

	if (argc > 3) {
		p.total_reads = strtol(argv[3], NULL, 0);
	}

	if (argc > 4) {
		p.num_threads = strtol(argv[4], NULL, 0);
	}
	return p;
}
