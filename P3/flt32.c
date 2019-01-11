#include "flt32.h"
#include "stdio.h"

/** @file flt32.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in flt32.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Logan Reed</b> goes here
 */

void printBinary (int value);

static int getBit (int value, int position) {    
	int new = value >> position;
	return new & 1;
}
static int setField (int oldValue, int hi, int lo, int newValue) {
	int mask = (hi - lo) + 1;
	int result = 0x0;
   	int mask2 = (1 << mask) - 1;
   	mask2 = mask2 << lo;
	oldValue = oldValue & ~(mask2);
	newValue = newValue << lo;
	newValue = newValue & mask2;
	result = oldValue | newValue;
	return result;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_sign (flt32 x) {
  int y = x >> 31; /* implement this */
  return y & 1;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_exp (flt32 x) {
  int mask = 0xFF;
  return x >> 23 & mask; /* implement this */
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_val (flt32 x) {
   int mask = 0x007FFFFF; 
   mask = mask & x; 
   int mask2 = 1 << 23;
   return mask2 | mask;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
void flt32_get_all(flt32 x, int* sign, int*exp, int* val) {

	*sign = flt32_get_sign(x);
	*exp = flt32_get_exp(x);
	*val = flt32_get_val(x);
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_abs (flt32 x) {
	return x & ~(1 <<31);
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_negate (flt32 x) {
	if(x < 0)
	{
		return flt32_abs(x);
	}
	if(x > 0)
	{
		return x | (1 << 31);
	}
	return x;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_add (flt32 x, flt32 y) {
	if(x == 0 && y != 0)
	{
		return y;
	}
	if(x != 0 && y == 0)
	{
		return x;
	}
	int firstmantissa = flt32_get_val(x);// mantissa of x
	int firstexponent = flt32_get_exp(x);// exponent of x
	int secondmantissa = flt32_get_val(y);// mantissa of y
	int secondexponent = flt32_get_exp(y);// exponent of y
	if(firstexponent < secondexponent)// Step 2 if first exponent is smaller than second
	{
	  firstmantissa = firstmantissa >> (secondexponent - firstexponent);
	  firstexponent = firstexponent + flt32_abs((secondexponent - firstexponent)); // Add difference in exponents
	}
	else if(secondexponent < firstexponent)// Step 2 if second exponent is smaller then first
	{
		secondmantissa = secondmantissa >> (firstexponent - secondexponent);
		secondexponent = secondexponent + flt32_abs((firstexponent - secondexponent)); // Add difference in exponents
	}
	if(x < 0)// Step 3, if x is negative do 2s comp
	{
		firstmantissa = 1 + ~(firstmantissa);
	}
	if(y < 0)// Step 3, if y is negative do 2s comp
	{
		secondmantissa = 1 + ~(secondmantissa);
	}
	int result = firstmantissa + secondmantissa;// Step 4 add mantissas
	int resultsign = flt32_get_sign(result);// Sign of the mantissa
	if(resultsign == 1)// Step 5, if result is negative, convert back to signed magnitude
	{
		result = 1 + ~(result);
	}
	int counter = 0;
	int counter2 = 0;
	int sumexp = firstexponent;
	//Step 6, if the first 1 bit is in wrong position
	for(int i = 31; i >= 0; i--)
	{
		if(i > 22)
		{
			if(getBit(result, i) == 1)
			{
				counter = i - 23;
				result = result >> counter;
				sumexp = sumexp + counter;
				break;
			}
		}
		if(i <= 22)
		{
			if(getBit(result, i) == 1)
			{
				counter2 = 23 - i;
				result = result << counter2;
				sumexp = sumexp - counter2;
				break;
			}
		}
	}
	result = result & 0xFF7FFFFF; //Step 7, remove implicit 1, this is the final mantissa
	int finalnum = 0x00000000;
	finalnum = setField(finalnum, 31, 31, resultsign);// putting it all together 
	finalnum = setField(finalnum, 30, 23, sumexp);//putting it all together
	finalnum = setField(finalnum, 22, 0, result);// putting it all together
	return finalnum;

}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_sub (flt32 x, flt32 y) {
	if(x == y)
	{
		return 0;
	}
  else return flt32_add(x, flt32_negate(y));
}

