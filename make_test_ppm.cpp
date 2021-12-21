#include <cstdlib>
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// make a simple test image
// with known values
void create_test_image() {
    FILE * outf = fopen("testimage.ppm","w'");
    fprintf(outf,"P3\n");
    fprintf(outf,"#tony is cool\n");

    int width = 32;
    int height = 32;
    fprintf(outf,"%d %d\n",width,height);
    fprintf(outf, "255\n");

    for (int i=0;i<width;i++) {
        for (int j=0;j<height;j++) {
            fprintf(outf, "%d %d %d ", i, j, 5);
        }
        fprintf(outf,"\n");
    }

    fclose(outf);
}

struct Pixel {
    int r;
    int g;
    int b;
};

void print_pixel(Pixel& p) {
    printf("%d %d %d\n", p.r, p.g, p.b);
}

void get(unsigned char * data, int x, int y, int n, 
    int X, int Y, Pixel *pixel) {
    int index = (Y*y*3) + (X*x*3);
    pixel->r = data[index];
    pixel->g = data[index+1];
    pixel->b = data[index+2];
}


int main() {

    // x is width
    // y is height
    // n is number of color channels
    // all of ^ is from docs on stb
    int x;
    int y;
    int n;
    unsigned char * data = stbi_load("testimage.png", &x, &y, &n, 0);

    Pixel p;
    for(int i=0;i<32;i++) {
        get(data,x,y,n,i,0,&p);
        print_pixel(p);
    }

    get(data,x,y,n,0,1,&p);
    print_pixel(p);

    return 0;
}