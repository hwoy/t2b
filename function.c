#include "function.h"

unsigned int
ui2s (unsigned int num, char *buff, unsigned int bsize, unsigned int base)
{
  unsigned int i, j, k, l;
  char chb, che;
  if (!base)
    {
      buff[0] = 0;
      return 0;
    }

  j = num, i = 0;
  do
    {
      k = j % base;
      j /= base;
      buff[i++] = ((base == 16) && (k > 9)) ? k + 'A' - 10 : k + '0';
    }
  while (j > 0 && i < bsize);
  l = i;

  buff[i] = 0;


  if (i > 0)
    {
      chb = buff[0];
      che = buff[i - 1];
      for (j = 0, i--; j < i; j++, i--)
	{
	  chb = buff[j];
	  che = buff[i];
	  buff[j] = che;
	  buff[i] = chb;
	}
    }

  return l;
}

int
isUint (const char *ch)
{
  unsigned int i;
  if (!sLen (ch))
    return 0;
  for (i = 0; ch[i]; i++)
    {
      if (ch[i] < '0' || ch[i] > '9')
	{
	  return 0;
	}
    }
  return 1;
}

unsigned int
pow2ui (unsigned int base, unsigned int pow)
{
  unsigned int i, j;
  if (!base)
    return 0;
  if (!pow)
    return 1;
  for (i = 1, j = base; i < pow; i++)
    {
      j = j * base;
    }
  return j;
}

unsigned int
s2ui (const char *ch, unsigned int base)
{
  unsigned int i, j, k, l;
  j = 0;
  k = 0;
  i = sLen (ch) - 1;
  do
    {
      if (base == 16)
	{
	  l =
	    (((ch[i] >= 'A'
	       && ch[i] <= 'F') ? (ch[i] - 'A' + 10) : (ch[i] - '0')));

	  j += l * pow2ui (base, k++);
	}

      else
	{
	  j += (ch[i] - '0') * pow2ui (base, k++);
	}
    }
  while (i-- != 0);

  return j;
}



unsigned int
sLen (const char *ch)
{
  unsigned int i;

  for (i = 0; ch[i]; i++)
    {
    }
  return i;
}

int
testbase (unsigned int ch, unsigned int base)
{
  return (base == 16
	  && (ch >= 'A'
	      && ch <= 'F')) ? base - (ch - 'A' + 10) : base - (ch - '0');
}
