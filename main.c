/**
 * The accuracy concept used here:
 *
accuracy = (correctly predicted class / total testing class) × 100%
OR,
The accuracy can be defined as the percentage of correctly classified instances (TP + TN)/(TP + TN + FP + FN). where TP, FN, FP and TN represent the number of true positives, false negatives, false positives and true negatives, respectively.
also you can use standard performance measures:
Sensitivity = TP / TP + FN
Specificity = TN / TN + FP
Precision = TP / TP + FP
True-Positive Rate = TP / TP + FN
False-Positive Rate = FP / FP + TN
True-Negative Rate = TN / TN + FP
False-Negative Rate = FN / FN + TP
For good classifiers, TPR and TNR both should be nearer to 100%. Similar is the case with precision and accuracy parameters. On the contrary, FPR and FNR both should be as close to 0% as possible.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mlog/logger.h"
#include "logic.h"


typedef struct param {
	size_t total_reads;
	const char *diff_path;
	int ground_truth_pos;
	int num_threads;
} param;


typedef struct context {
	mlog logger;
	param param;
} context;


static int usage(int argc, const char **argv);

static context init(int argc, const char **argv);

static param parse_params(int argc, const char **argv);

static size_t file_length(const char *path);


int main(int argc, const char *argv[]) {
	if (argc < 2 || argc > 5) {
		return usage(argc, argv);
	}

	context ctx = init(argc, argv);
	mlog log = ctx.logger;

	FILE *fp = fopen(ctx.param.diff_path, "r");
	size_t size = file_length(ctx.param.diff_path);
	char *buf = malloc(size * sizeof(char));
	size_t len = fread(buf, sizeof(char), size, fp);

	if (len != size) {
		//todo: fatal error
		log.melog(&log, "Fatal error!");
		exit(-1);
	}

	p_result result = parse_full_text(buf, len, ctx.param.ground_truth_pos);

	printf("Error: %lu\n", result.wrong);
	printf("Redundant: %lu\n", result.redundant);
	printf("Missed: %lu\n", result.missed);

	printf("\n");

	printf("False Negative (Missed): %lu\n", result.missed);
	printf("False Positive (Error + Redundant): %lu\n", result.wrong + result.redundant);

	if (ctx.param.total_reads != 0) {
		printf("\n");
		size_t total = ctx.param.total_reads;
		size_t tp = total - result.wrong - result.redundant - result.missed;
		printf("True Positive (Total - Error - Redundant - Missed): %lu\n\n", tp);

		printf("Precision (True Positive / Total reads): %lf\n", (double) tp / total);
	}

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

	ctx.param = p;

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

size_t file_length(const char *path) {
	FILE *fp = fopen(path, "r");

	if (!fseek(fp, 0, SEEK_END)) {
		long pos = ftell(fp);
		if (pos >= 0) {
			return pos;
		}
	}

	fclose(fp);
	return 0;
}
