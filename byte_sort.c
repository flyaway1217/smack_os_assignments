/*********************************************************************
 *
 * Operating Systems Assignment 1.1: Byte Sort
 *
 *********************************************************************/

#include <smack.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BYTE_0_MASK	0x00000000000000FF
#define BYTE_1_MASK 0x000000000000FF00
#define BYTE_2_MASK	0x0000000000FF0000
#define BYTE_3_MASK	0x00000000FF000000
#define BYTE_4_MASK	0x000000FF00000000
#define BYTE_5_MASK	0x0000FF0000000000
#define BYTE_6_MASK	0x00FF000000000000
#define BYTE_7_MASK	0xFF00000000000000

typedef int bool;
#define true 1
#define false 0

unsigned long byte_sort (unsigned long arg);
bool is_sorted(unsigned long val);

int main(int argc, char* argv[]) {

	// Test byte_sort
	unsigned long val = __VERIFIER_nondet_ulong();
	assert(is_sorted(byte_sort(val)));

	return 0;
}

/// Here is my unmodified implementation of nibble_sort that I wrote for an
/// operating systems assignment. It was tested with handwritten examples.  
/// It treats its argument as a sequence of 8 bytes, and returns a new unsigned
/// long integer containing the same bytes, sorted numerically, with the 
/// smaller-valued bytes in the lower-order byte positions of the return value
/// EXAMPLE: 0x0403deadbeef0201 returns 0xefdebead04030201.
///
/// @param[in] arg  Value to sort by bytes.
///
/// @return the value sorted by bytes.
unsigned long byte_sort (unsigned long arg)
{
	unsigned long result = 0;
	unsigned char bytes[8];
	int i = 0;
	int j = 0;

	int min = 0;
	int temp = 0;

	// Byte shift input into individual bytes
	bytes[0] = (arg & BYTE_0_MASK) >> (8 * 0);
	bytes[1] = (arg & BYTE_1_MASK) >> (8 * 1);
	bytes[2] = (arg & BYTE_2_MASK) >> (8 * 2);
	bytes[3] = (arg & BYTE_3_MASK) >> (8 * 3);
	bytes[4] = (arg & BYTE_4_MASK) >> (8 * 4);
	bytes[5] = (arg & BYTE_5_MASK) >> (8 * 5);
	bytes[6] = (arg & BYTE_6_MASK) >> (8 * 6);
	bytes[7] = (arg & BYTE_7_MASK) >> (8 * 7);

	// Sort individual bytes (albeit slowly...)
	for(i = 0; i < 8; i++) {

		min = i;

		for(j = i + 1; j < 8; j++) {
			if(bytes[j] < bytes[min]) {
				min = j;
			}
		}

		// Switch the current value with the minimum found
		temp = bytes[i]; // SMACK found the bug tried here: temp = bytes[j];
		bytes[i] = bytes[min];
		bytes[min] = temp;
	}

	// Put the bytes back into a long
	result = (((unsigned long) bytes[7]) << (8 * 7)) |
			 (((unsigned long) bytes[6]) << (8 * 6)) |
			 (((unsigned long) bytes[5]) << (8 * 5)) |
			 (((unsigned long) bytes[4]) << (8 * 4)) | 
			 (((unsigned long) bytes[3]) << (8 * 3)) |
			 (((unsigned long) bytes[2]) << (8 * 2)) |
			 (((unsigned long) bytes[1]) << (8 * 1)) |
			 (((unsigned long) bytes[0]) << (8 * 0));

  	return result;
}

/// I added this function as a helper as part of my project. SMACK uses this
/// function in its assert statements to verify that the value is in sorted
/// order.
///
/// @param[in] val  An already byte sorted value.
///
/// @return true if the value is correctly byte sorted.
bool is_sorted(unsigned long val)
{
	unsigned long mask = 0x00000000000000FF;
	unsigned long temp = 0;
	unsigned long next = 0;

	int i;
	for (i = 0; i < 7; i++)
	{
		next = (val & (mask << (i + 1) * 8)) >> ((i + 1) * 8);
		temp = (val & (mask << i * 8)) >> (i * 8);

		if (next < temp)
		{
			return false;
		}
	}

	return true;
}


