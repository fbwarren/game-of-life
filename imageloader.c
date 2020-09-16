/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Frank Warren
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
	uint32_t cols = 0, rows = 0;
	FILE *fp = fopen(filename, "r");
	Image *image = malloc(sizeof(Image));				
	if (!image) { return NULL; } 						
	fscanf(fp, "%*s %i %i %*s", &cols, &rows);
	image->cols = cols;
	image->rows = rows; 	
	image->image = malloc(sizeof(Color**));
	*(image->image) = calloc(cols*rows, sizeof(Color));	
	if (!*(image->image)) { return NULL; }
	for (int i=0; i < cols*rows; i++) {
		uint8_t R, G, B;
		fscanf(fp, "%hhu %hhu %hhu", &R, &G, &B);
		Color color = {R, G, B};
		(*image->image)[i] = color;
	}
	fclose(fp);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image) {
	printf("P3\n%d %d\n255\n", image->cols, image->rows);
	Color *ptr = (*image->image);
	for (int row=0; row < image->rows; row++) {
		for (int col=0; col < image->cols-1; col++) {
			Color color = ptr[row * image->cols + col];
			printf("%*hhu %*hhu %*hhu   ", 3, color.R, 3, color.G, 3, color.B);
			if (col == image->cols - 2) {
				col++;
				color = (*image->image)[row * image->cols + col];
				printf("%*hhu %*hhu %*hhu\n", 3, color.R, 3, color.G, 3, color.B);
			}
		}
	}
}

//Frees an image
void freeImage(Image *image) {
	free(*image->image);
	free(image->image);
	free(image);
}