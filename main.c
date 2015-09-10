#include <stdio.h>
#include <string.h>
#include "function.h"

#define BSIZE 64
#define COL 16
#define BASE 10
#define DELIM ','

void showErr (const char *errstr[], int errNO);
int showHelp (char *path, const char *param[], const char *pdetail[],
	      int ret);
static unsigned int basename (const char *ch);
static unsigned int extend (const char *ch);

static const char suffix[] = ".bin";
static char buff[BSIZE];

static const char *errstr[] =
  { "Parameters is not match", "Input file is not found",
  "Can not assign an output file", "Base number must not be zero",
  "Syntax Error"
};
static const char *param[] = { "-b" };
static const char *pdetail[] = { "base Number" };

enum __errNO
{
  e_param, e_input, e_output, e_basezero, e_syn
};
enum __param
{
  e_base
};

int
main (int argc, char *argv[])
{
  FILE *in, *out;
  unsigned int ch, i, j, isb, base, syn;
  static char instr[1024], outstr[1024];
/******************* Parameters **********************/

  if (argc < 2)
    {
      showErr (errstr, e_param);
      return showHelp (argv[0], param, pdetail, 0);
      return 1;
    }

  base = BASE;
  j = 1;
  isb = 0;
  if (!strncmp (argv[1], param[e_base], sLen (param[e_base])))
    {
      if (!isUint (argv[1] + 2))
	{
	  showErr (errstr, e_param);
	  return showHelp (argv[0], param, pdetail, 0);
	}
      base = s2ui (argv[1] + 2, 10);
      j = 2;
      isb = 1;
    }

  if (!base)
    {
      showErr (errstr, e_basezero);
      return showHelp (argv[0], param, pdetail, 0);
    }


/******************* Parameters **********************/
  for (syn = 0; j < argc; j++)
    {

      strcpy (instr, argv[j]);
      strcpy (outstr, argv[j]);


      if (!isb && extend (outstr) && isUint (extend (outstr) + outstr))
	{
	  base = s2ui (extend (outstr) + outstr, 10);
	  outstr[extend (outstr) - 1] = 0;
	}
      else
	{
	  strcat (outstr, suffix);
	}


      if (!(in = fopen (instr, "rb")))
	{
	  showErr (errstr, e_input);
	  fprintf (stderr, "FILE: %s\n\n", instr);
	  syn = 1;
	  continue;
	}

      if (!(out = fopen (outstr, "wb")))
	{
	  showErr (errstr, e_output);
	  fprintf (stderr, "FILE: %s\n\n", outstr);
	  fclose (in);
	  syn = 1;
	  continue;
	}
      i = 0;
      syn = 0;
      while ((ch = fgetc (in)) != EOF)
	{

	  if (((ch >= '0' && ch <= '9')
	       || ((base == 16) && (ch >= 'A' && ch <= 'F')))
	      && (testbase (ch, base) > 0))
	    {
	      buff[i++] = ch;
	    }
	  else if (ch == DELIM)
	    {
	      buff[i] = 0;
	      fputc (s2ui (buff, base), out);
	      i = 0;
	    }
	  else if (ch != 10 && ch != 13 && ch != DELIM)
	    {
	      showErr (errstr, e_syn);
	      fprintf (stderr, "FILE: %s\n\n", instr);
	      fclose (in);
	      fclose (out);
	      remove (outstr);
	      syn = 1;
	      break;
	    }

	}
      if (!syn)
	{
	  fclose (in);
	  fclose (out);
	}
    }
  return 0;
}

void
showErr (const char *errstr[], int errNO)
{
  fprintf (stderr, "ERR NO:%u = %s\n", errNO, errstr[errNO]);
}

int
showHelp (char *path, const char *param[], const char *pdetail[], int ret)
{
  fprintf (stderr, "\nUSAGE: %s {%sN} file1 file2 ...\n",
	   path + basename (path), param[e_base]);
  fprintf (stderr, "%s = %s\n", param[e_base], pdetail[e_base]);

  return ret;
}

static unsigned int
basename (const char *ch)
{
  unsigned int i, j;
  for (i = 0, j = 0; ch[i]; i++)
    {
      if (ch[i] == '\\' || ch[i] == '/')
	{
	  j = i;
	}
    }
  return (j == 0) ? 0 : j + 1;
}

static unsigned int
extend (const char *ch)
{
  unsigned int i, j;
  for (i = 0, j = 0; ch[i]; i++)
    {
      if (ch[i] == '.')
	{
	  j = i;
	}
    }
  return (j == 0) ? 0 : j + 1;
}
