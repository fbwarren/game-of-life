/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
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
	uint8_t blue = (*image->image)[(row * image->cols) + col].B;  // Get the blue value from the image
	blue &= 1; 
	blue = ~blue + 1;
	Color *color = calloc(1, sizeof(Color));
	Color temp = {blue, blue, blue};
	*color = temp;
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image *newImage = malloc(sizeof(Image));
	*newImage = *image;
	*(newImage->image) = calloc(image->cols*image->rows, sizeof(Color));
	for (int r=0; r < image->rows; r++) {
		for (int c=0; c < image->rows; c++) {
			(newImage->image)[c+r] = evaluateOnePixel(image, r, c);
		}
	}
	free(image);
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
	freeImage(newImage);
	//freeImage(newImage);
	return 0;
}
