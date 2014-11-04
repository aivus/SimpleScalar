/* mtrace.h - memory tracing definitions and interfaces */

#ifndef MTRACE_H
#define MTRACE_H

#include "host.h"
#include "misc.h"
#include "machine.h"
#include "range.h"

//
///* pipeline stages */
//#define PST_IFETCH		"IF"
//#define PST_DISPATCH		"DA"
//#define PST_EXECUTE		"EX"
//#define PST_WRITEBACK		"WB"
//#define PST_COMMIT		"CT"
//
///* pipeline events */
//#define PEV_CACHEMISS		0x00000001	/* I/D-cache miss */
//#define PEV_TLBMISS		0x00000002	/* I/D-tlb miss */
//#define PEV_MPOCCURED		0x00000004	/* mis-pred branch occurred */
//#define PEV_MPDETECT		0x00000008	/* mis-pred branch detected */
//#define PEV_AGEN		0x00000010	/* address generation */

/* pipetrace file */
extern FILE *mtrace_outfd;

/* pipetracing is active */
extern int mtrace_active;

/* pipetracing range */
extern struct range_range_t mtrace_range;

/* one-shot switch for pipetracing */
extern int mtrace_oneshot;

/* open pipeline trace */
void
mtrace_open(char *fname,		/* output filename */
			char *range);		/* trace range */

/* close pipeline trace */
void
mtrace_close(void);

/* NOTE: pipetracing is a one-shot switch, since turning on a trace more than
   once will mess up the pipetrace viewer */
#define mtrace_check_active(PC, ICNT, CYCLE)				\
  ((mtrace_outfd != NULL						\
    && !range_cmp_range1(&mtrace_range, (PC), (ICNT), (CYCLE)))		\
   ? (!mtrace_oneshot ? (mtrace_active = mtrace_oneshot = TRUE) : FALSE)\
   : (mtrace_active = FALSE))

/* main interfaces, with fast checks */
#define mtrace_newstore(A,B)						\
  if (mtrace_active) __mtrace_newstore((A),(B))
#define mtrace_newload(A,B)						\
  if (mtrace_active) __mtrace_newload((A),(B))

#define mtrace_active(A,I,C)						\
  (mtrace_outfd != NULL	&& !range_cmp_range(&mtrace_range, (A), (I), (C)))

/* declare a new cycle */
void
__mtrace_newstore(unsigned int size, md_addr_t addr);

/* indicate instruction transition to a new pipeline stage */
void
__mtrace_newload(unsigned int size, md_addr_t addr);

#endif /* MTRACE_H */
