#include "field.h"

/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author <b>Logan Reed</b> goes here
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {    
	int new = value >> position;
	return new & 1;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
	int mask = (1 << position);
	return value | mask;
	
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
    	int mask = ~(1 << position);
		return value & mask;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
	int range = (hi - lo) + 1;
	int shortened = value >> lo;
	int mask = (1 << range) - 1;
	
	int result = shortened & mask; 
	
	if(isSigned == true)
	{
		if(getBit(result, hi - lo) == 0)
		{
				return result;
		}
		else
		{
				int mask2 = (0-1) << (hi-lo+1);
				return result | mask2;
		}
	}
	return result;
	
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setField (int oldValue, int hi, int lo, int newValue) {
	int mask = ((hi - lo) + 1);
	int result = 0x0;
	int mask2 = 0x0;
	mask2 = (1 << mask) - 1;
	mask2 = mask2 << lo;
	oldValue = oldValue & ~(mask2);
	newValue = newValue << lo;
	newValue = newValue & mask2;
	result = oldValue | newValue;
	return result;
}

