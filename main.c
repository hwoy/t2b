#include <stdio.h>
#include "function.h"

#define BSIZE 64
#define COL 5
#define BASE 16


static const char infile[] = "a.txt";
static const char outfile[] = "b.txt";

static char buff[BSIZE];

int
main (void)
{
  FILE *in, *out;
  unsigned int ch, i;

  in = fopen (infile, "rb");
  out = fopen (outfile, "wb");

  i = 0;
  while ((ch = fgetc (in)) != EOF)
    {
      ui2s (ch, buff, BSIZE, BASE);
      fprintf (out, "%s,", buff);
      if (++i > COL - 1)
	{
	  fprintf (out, "\n");
	  i = 0;
	}

    }

  return 0;
}
