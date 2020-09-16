/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) {	
	char fuck[50];
	char shit[50];
	uint32_t cols = 0, rows = 0;
	FILE *fp = fopen(filename, "r");
	//printf("File pointer: %d \n", *fp);
	Image *image = malloc(sizeof(Image));					// Allocate memory for image struct
	if (!image) { return NULL; } 							// Check for allocation failures
	fscanf(fp, "%s %i %i %s", &fuck, &cols, &rows, &shit); // Read and assign img size
	image->cols = cols;
	image->rows = rows; 	
	//printf("\n fuck: %s shit %s", fuck, shit);
	//printf("\ncolumns: %d  rows: %d \n", cols, rows);
	//printf(filename);

	//*(image->image) = malloc(sizeof(Color*) * cols * rows);  // Allocate a 2d array of pixels
	image->image = malloc(sizeof(Color**));
	*(image->image) = calloc(cols*rows, sizeof(Color));	

	if (!*(image->image)) { return NULL; }
	//(image->image = (Color**) calloc(cols*rows, sizeof(Color));
	//if (!image->image) { return NULL; }
	
	for (int i=0; i < cols*rows; i++) {
		uint8_t R, G, B;
		fscanf(fp, "%hhd %hhd %hhd", &R, &G, &B);
		Color color = {R, G, B};
		(*image->image)[i] = color;
	}


	// for (int r=0; r < rows; r++) {
	// 	for (int c=0; c < cols; c++) {
	// 		uint8_t R, G, B;
	// 		fscanf(fp, "%hhd %hhd %hhd", &R, &G, &B);
	// 		Color color = {R, G, B};
	// 		image->image[r][c] = color;
	// 	}
	// }
	fclose(fp);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image) {
	printf("P3\n%d %d \n255\n", image->cols, image->rows);
	//Color *color = *image->image;
	for (int row=0; row < image->rows; row++) {
		for (int col=0; col < image->cols - 1; col++) {
			Color color = (*image->image)[row+col];
			printf("%*d %*d %*d   ", 3, color.R, 3, color.G, 3, color.B);
			if (col == image->cols - 1) {
				printf("%*d %*d %*d\n", 3, color.R, 3, color.G, 3, color.B);
			}
		}
	}
}

//Frees an image
void freeImage(Image *image) {
	free(*image->image);
	free(image);
}