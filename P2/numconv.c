#include <stdio.h>
/**
 *  @author  your name goes here
 * Logan Reed
 */

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int2char (int radix, int digit) {
  if(digit >= radix || radix < 0)
  {
	  return '?';
  }
  else
  {
	  if(digit <= 9)
	  {
	  char c = (char)digit + '0';
	  return c;
	  }
	  else
	  {
		  char d = (char)digit + 55;
		  return d;
	  }
	  
  }
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char2int (int radix, char digit) {
	if(digit >= '0' && digit <= '9')
	{
		int n = digit - '0';
		if(n >= radix)
		{
			return -1;
		}
		return n;
	}
	if(digit >= 'a' && digit <= 'z')
	{
		int o = digit - 87;
		if(o >= radix)
		{
			return -1;
		}
		return o;
	}
	if(digit >= 'A' && digit <= 'Z')
	{
		int p = digit - 55;
		if(p >= radix)
		{
			return -1;
		}
		return p;
	}
	else {
		return -1;
	}
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void divRem (int numerator, int divisor, int* quotient, int* remainder) {
	int result = numerator / divisor;
	int remain = numerator % divisor;
	*quotient = result;
	*remainder = remain;
	
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii2int (int radix, const char *str) {
  int result = 0;
  for (int i = 0; str[i] != 0; i++)
  {
	  result = radix * result + char2int(radix, str[i]);
	  if(char2int(radix, str[i]) == -1)
	  {
		  return -1;
	  }
  }
  return result;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int2ascii (int radix, int value) {
	if(value / radix != 0)
	  {
	    int divvalue = value / radix;
	    int remvalue = value % radix;
	    int2ascii(radix, divvalue);
	    putchar(int2char(radix, remvalue));

	  }
	else
	  {
	    int remvalue2 = value % radix;
	    putchar(int2char(radix, remvalue2));
	  }
	
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double ascii2double (int radix, const char *str) {
  return -1.0;
}

