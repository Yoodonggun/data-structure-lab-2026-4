#include <stdio.h>

#define HEIGHT 8
#define WIDTH 8

int image[HEIGHT][WIDTH] = {
	{ 10, 30, 55, 80, 120, 160, 200, 230},
	{ 20, 45, 70, 100, 140, 180, 220, 210},
	{ 35, 60, 90, 130, 170, 210, 240, 210},
	{ 50, 80, 115, 150, 190, 230, 255, 170},
	{ 40, 65, 100, 140, 175, 215, 235, 150},
	{ 25, 50, 80, 115, 155, 195, 210, 130},
	{ 15, 35, 60, 90, 130, 165, 185, 110},
	{ 5, 20, 40, 70, 105, 140, 160, 90},
};

int FindMaxPixel(int a[][WIDTH], int h, int w) {
	int MaxPixel = a[0][0];
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if(a[i][j] > MaxPixel) {
				MaxPixel = a[i][j];
			}
		}
	}
	return MaxPixel;
}
int main() {
	int result = FindMaxPixel(image, HEIGHT, WIDTH);
	printf("MaxPixel : %d\n", result);
	return 0;
}