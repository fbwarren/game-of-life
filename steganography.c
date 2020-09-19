/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				Frank Warren
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	Color color = (image->image)[row][col];
	Color *ptr;
	uint8_t blue = color.B;
	blue &= 1;				// Grab LSB
	blue = ~blue + 1;		// Set to 0 if LSB==0, else blue=255
	ptr = calloc(1, sizeof(Color));  // color now points to new Color space.
	ptr->R = ptr->G = ptr->B = blue; 
	return ptr;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image *newImage = malloc(sizeof(Image));
	*newImage = *image;
	for (int r=0; r <= image->rows-1; r++) {
		for (int c=0; c <= image->cols-1; c++) {
	 		Color *pixel = evaluateOnePixel(image, r, c);
			(newImage->image)[r][c] = *pixel; 
			free(pixel);
	 	}
	}
	return newImage;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	Image *image = readData(argv[1]);
	if (image == NULL) return -1;
	Image *newImage = steganography(image);
	if (newImage == NULL) return -1;
	writeData(newImage);
	//freeImage(image);
	freeImage(newImage);
	return 0;
}
