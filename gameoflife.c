/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Frank Warren
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// This function takes in a an image, pixel location, rule, and channel (a number representing one of the 24 bits, where 0
// represents the rightmost bit of the combined RGB values, 23 represents the most significant 'Red' bit.)
// and returns what the channel's bit should be for that pixel, given the rule provided.
uint8_t evaluateChannel(Image *image, int row, int col, uint32_t rule, uint8_t channel)
{
	Color cell = (image->image)[row][col]; // Get the original cell
	Color neighbor;
	unsigned long cellFields = (cell.R << 16) + (cell.G << 8) + (cell.B); // Combine all its color fields in one number
	unsigned long neighborFields;
	uint8_t cellField = (cellFields >> channel) & 1; // Determine if cell is dead or alive
	uint8_t neighborField;
	int8_t neighbors = 0; // Account for counting cell as a neighbor
	for (int r = 1; r >= -1; r--)
	{ // Iterate through neighbors
		for (int c = 1; c >= -1; c--)
		{
			neighbor = (image->image)[(row + image->rows - r) % (image->rows)][(col + image->cols - c) % (image->cols)];
			neighborFields = (neighbor.R << 16) + (neighbor.G << 8) + (neighbor.B);
			neighborField = (neighborFields >> channel) & 1;
			if (neighborField) { neighbors++; } // Neighbor is "alive" at channel
		}
	}
	if (cellField) {neighbors--;}
	rule = rule >> (cellField * 9); // Shift to correct set of rules depending on if cell is alive
	return (rule >> neighbors) & 1;
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule) {
	uint32_t color = 0;
	for (int i=0; i<24; i++) {
		color = color | (evaluateChannel(image, row, col, rule, i)<<i);
	}
	Color *ptr = (Color*) calloc(1, sizeof(Color));
	ptr->R = color>>16;
	ptr->G = color>>8;
	ptr->B = color;
	return ptr;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	Image *newImage = (Image*) malloc(sizeof(Image));
	*newImage = *image;
	newImage->image = calloc(image->rows, sizeof(Color*));
	for (int r = 0; r <= image->rows - 1; r++) {
		(newImage->image)[r] = calloc(image->cols, sizeof(Color));
		for (int c = 0; c <= image->cols - 1; c++) {
			Color *pixel = evaluateOneCell(image, r, c, rule);
			(newImage->image)[r][c] = *pixel;
			free(pixel);
		}
	}
	return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	if (argc != 3) {
		printf(	"usage: ./gameOfLife filename rule\n"
			   	"filename is an ASCII PPM file (type P3 with maximum value 255.\n"
				"rule is a hex number beginning with 0x; Life is 0x1808.\n");
	}
	//uint32_t rule = atoi(argv[3]);
	uint32_t rule = 6152; 				//TODO: NOT HARDCODE THIS!!
	Image *image = readData(argv[1]);
	Image *iteration = life(image, rule);
	writeData(iteration);
	freeImage(iteration);
	freeImage(image);
}
