#include <stdio.h>
#include <stdlib.h>

/* Mandelbrot function */
int mandelbrot(double c_real, double c_imag, int max_iter) {
	int iter = 0;
	double z_real = 0.0, z_imag = 0.0;
	double temp;
	
	while(iter < max_iter && z_real*z_real + z_imag*z_imag < 4.0) {
		temp = z_real*z_real - z_imag*z_imag + c_real;
		z_imag = 2.0*z_real*z_imag + c_imag;
		z_real = temp;
		iter++;
	}

	return iter;
}

int main(int argc, char **argv) {
	
	if (argc < 4) {
		printf("Not enough arguments supplied!\n");
		return 1;
	}

	if (argc > 4) {
		printf("Too many arguments supplied!\n");
		return 1;
	}

	const int width = atoi(argv[1]);
	const int height = atoi(argv[2]);
	const int max_iter = atoi(argv[3]);
	/* We don't have a complex number type yet, so we are going
	 * to use double type for real and imaginary parts separately */
	double c_real, c_imag;
	double rscale_from = -1.5, rscale_to = 0.7, iscale_from = -1.0, iscale_to = 1.0;
	FILE *output;
	output = fopen("output.ppm", "w");

	/* Filling in the .ppm file header */
	/* We will have a width x height image with maximum color palette of 255 colors */
	fprintf(output, "P3\n%d %d\n255\n", width, height);

	/* Iterate through image pixels */
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			/* We need to map c's real and imaginary part according to our scale */
			c_real = j * ((rscale_to - rscale_from) / width) + rscale_from;
			c_imag = i * ((iscale_to - iscale_from) / height) + iscale_from;
			int n = mandelbrot(c_real, c_imag, max_iter);
			int r = (n % 256);
			int g = (n % 256);
			int b = (n % 256);
			fprintf(output, "%d %d %d ", r, g, b);
		}

		fprintf(output, "\n");
	}

	fclose(output);
	return 0;
}
