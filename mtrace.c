/* mtrace.c - memory tracing routines */

#include <stdio.h>
#include <stdlib.h>

#include "host.h"
#include "misc.h"
#include "machine.h"
#include "range.h"
#include "mtrace.h"

/* pipetrace file */
FILE *mtrace_outfd = NULL;

/* pipetracing is active */
int mtrace_active = FALSE;

/* pipetracing range */
struct range_range_t mtrace_range;

/* one-shot switch for pipetracing */
int mtrace_oneshot = FALSE;

/* open pipeline trace */
void
mtrace_open(char *fname,		/* output filename */
	    char *range)		/* trace range */
{
  char *errstr;

  // Enable trace
  mtrace_active = TRUE;

//  /* parse the output range */
//  if (!range)
//    {
//      /* no range */
//      errstr = range_parse_range(":", &mtrace_range);
//      if (errstr)
//	panic("cannot parse pipetrace range, use: {<start>}:{<end>}");
//      mtrace_active = TRUE;
//    }
//  else
//    {
//      errstr = range_parse_range(range, &mtrace_range);
//      if (errstr)
//	fatal("cannot parse pipetrace range, use: {<start>}:{<end>}");
//      mtrace_active = FALSE;
//    }
//
//  if (mtrace_range.start.ptype != mtrace_range.end.ptype)
//    fatal("range endpoints are not of the same type");

  /* open output trace file */
  if (!fname || !strcmp(fname, "-") || !strcmp(fname, "stderr"))
    mtrace_outfd = stderr;
  else if (!strcmp(fname, "stdout"))
    mtrace_outfd = stdout;
  else
    {
      mtrace_outfd = fopen(fname, "w");
      if (!mtrace_outfd)
	fatal("cannot open memory trace output file `%s'", fname);
    }
}

/* close pipeline trace */
void
mtrace_close(void)
{
  if (mtrace_outfd != NULL && mtrace_outfd != stderr && mtrace_outfd != stdout)
    fclose(mtrace_outfd);
}

/* declare a new store */
void
__mtrace_newstore(unsigned int size, md_addr_t addr)
{
	fprintf(mtrace_outfd, "s %u %u\n", size, addr);

	if (mtrace_outfd == stderr || mtrace_outfd == stdout)
		fflush(mtrace_outfd);
}

/* declare a new load */
void
__mtrace_newload(unsigned int size, md_addr_t addr)
{
	fprintf(mtrace_outfd, "l %u %u\n", size, addr);

	if (mtrace_outfd == stderr || mtrace_outfd == stdout)
		fflush(mtrace_outfd);
}
