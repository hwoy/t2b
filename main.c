#include <stdio.h>
#include <string.h>
#include "function.h"

#define BSIZE 64
#define COL 5
#define BASE 10


static char suffix[BSIZE];
static char buff[BSIZE];

int
main (int argc, char *argv[])
{
  FILE *in, *out;
  unsigned int ch, i, j, base;
  static char instr[1024], outstr[1024];
/*****************************************/

  if (argc < 2)
    {
      fprintf (stderr, "Parameter\n");
      return 1;
    }

  base = BASE;
  j = 1;
  if (!strncmp (argv[1], "-b", 2))
    {
      if (!isUint (argv[1] + 2))
	{
	  fprintf (stderr, "-b parameter\n");
	  return 1;
	}
      base = s2ui (argv[1] + 2);
      j = 2;
    }

  suffix[0] = '.';
  ui2s (base, suffix + 1, BSIZE - 1, 10);

/*****************************************/
  for (; j < argc; j++)
    {
      strcpy (instr, argv[j]);
      strcpy (outstr, argv[j]);
      strcat (outstr, suffix);

      if (!(in = fopen (instr, "rb")))
	{
	  fprintf (stderr, "inprt %s\n", instr);
	  continue;
	}

      if (!(out = fopen (outstr, "wb")))
	{
	  fprintf (stderr, "outptr %s\n", outstr);
	  fclose (in);
	  continue;
	}
      i = 0;
      while ((ch = fgetc (in)) != EOF)
	{
	  ui2s (ch, buff, BSIZE, base);
	  fprintf (out, "%s,", buff);
	  if (++i > COL - 1)
	    {
	      fprintf (out, "\n");
	      i = 0;
	    }

	}
      fclose (in);
      fclose (out);
    }
  return 0;
}
