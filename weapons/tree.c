/*
 * This is a tool intended to mimic a lot of the behavior of find(1) when
 * invoked from the command line and supplied with one or more paths.
 *
 * It will traverse the entirety of one or more caller-supplied directory trees,
 * and for each object discovered of type file, it will print the logical size
 * (in bytes), the time of last data modification (epoch time) and the physical
 * size in kilobytes.
 *
 * This utility uses nftw(3C).  The creation of this program was born out of
 * necessity.  Apparently GNU find (version 4.2.33) builds out an internal
 * representation of a directory tree in memory which is obviously problematic
 * in systems where the number of objects in the tree is sufficiently high.  In
 * a situation where GNU find taps out, our file listing is truncated, giving an
 * incomplete picture of the tree's contents.  As a mitigation to this problem,
 * this tool was created.  It was written with nftw(3C) at the foundation which
 * does not make over-gratuitous use of memory during directory tree traversal.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <ftw.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * Since nftw(3C) uses one file descriptor for each level in the tree, this
 * should be more than enough to traverse the depths of a simple directory.
 */
#define	MAX_DESCRIPTORS	10
#define	MAX_LEVEL	256

static void nftw_warn(const char *, ...);
static int nftw_cb(const char *, const struct stat *, int, struct FTW *);

/* Globals */
static int error;
static int counts[MAX_LEVEL] = {0};

void
print_entry(int depth, const char *name)
{
	int i;

	for (i = 1; i < depth; i++)
		printf("%c   ", counts[i] > 0 ? '|' : ' ');

	printf("|--%s\n", name);
}

int
main(int argc, char *argv[])
{
	int i, ret, flags;

	if (argc < 2)
		errx(1, "usage: %s dir1 dir2 ... dirN", argv[0]);

	flags = (FTW_PHYS | FTW_MOUNT);

	/*
	 * Roll through the list of caller-supplied directories and call
	 * `nftw()' on each.  Record any errors along the way.
	 */
	for (i = 1; i < argc; i++) {
		ret = nftw(argv[i], nftw_cb, MAX_DESCRIPTORS, flags);

		if (ret == -1) {
			warn("An error occured traversing %s", argv[i]);
			error = 1;
		}

		/*
		 * The only way that this can happen is if we reach the default
		 * case in `nftw_cb()'.  This should never happen.
		 */
		if (ret == 1)
			break;
	}

	return (error);
}

static void
nftw_warn(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vwarnx(fmt, args);
	va_end(args);

	error = 1;
}

static int
nftw_cb(const char *path, const struct stat *st, int objtype, struct FTW *ftw)
{
	int ret = 0;
	blkcnt_t logical;
	const char *obj_name = strrchr(path, '/');

	/* This is as deep as we're willing to go. */
	if (ftw->level >= MAX_LEVEL)
		return (1);

	switch (objtype) {
	case FTW_D:
		counts[ftw->level + 1] += st->st_nlink - 2;
		
	case FTW_F:
		if (obj_name == NULL) {
			printf("%c\n", '.');
			break;
		}

		if (counts[ftw->level] > 0)
			counts[ftw->level]--;

		print_entry(ftw->level, obj_name + 1);
		break;

	/* We are not interested in symlinks. */
	case FTW_SL:
		break;

	case FTW_DNR:
		nftw_warn("Unable to read directory: %s", path);
		break;

	case FTW_NS:
		nftw_warn("stat failed at %s", path);
		break;

	default:
		/*
		 * In the pratically impossible case that objtype is of a value
		 * that's not known at all, it could be a sign of something
		 * more systemmic.
		 */
		nftw_warn("%s: unknown type (%d)", path, objtype);
		ret = 1;
		break;
	}

	return (ret);
}
