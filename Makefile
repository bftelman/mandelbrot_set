CC:= gcc
CFLAGS:= -Wall

all:
	$(CC) $(CFLAGS) -o mandelbrot mandelbrot.c


debug:
	cat output.ppm

view:
	xdg-open output.ppm

clean:
	rm *.ppm ./mandelbrot
