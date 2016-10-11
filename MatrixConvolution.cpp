#include "MatrixConvolution.h"

// Helper function to deal with cases along the border of the bitmap
int getReflectedPixel(int maxpix, int i) {
	if (i < 0) { return -i - 1; }
	if (i >= maxpix) { return maxpix*2 - i- 1; }
	return  i;
}

// Applies a 3x3 convolution matrix to a bitmap (of size width x height) stored as an array of unsigned chars
unsigned char* applyMatrixConvolution(unsigned char *bmp, double mtrx[9], int width, int height) {
	double m_sum = 0;
	for (int i = 0; i < 9; i++) { m_sum += mtrx[i]; }
	unsigned char *new_bmp = new unsigned char[width * height * 4];
	for (int i = 0; i < width*height; i++) {
		int r_sum = 0; int g_sum = 0; int b_sum = 0;
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				int p = i * 4;
				int row = getReflectedPixel(height, (i / width) + k);
				int col = getReflectedPixel(width,  (i % width) + j);
				float kernel_val = mtrx[(k+1)*3 + j + 1];
				r_sum += bmp[row*width * 4 + col * 4] * kernel_val;
				g_sum += bmp[row*width * 4 + col * 4 + 1] * kernel_val;
				b_sum += bmp[row*width * 4 + col * 4 + 2] * kernel_val;
			}
		}
		new_bmp[i * 4] = r_sum / m_sum;
		new_bmp[i * 4 + 1] = g_sum / m_sum;
		new_bmp[i * 4 + 2] = b_sum / m_sum;
		new_bmp[i * 4 + 3] = 255;
	}
	return new_bmp;
}