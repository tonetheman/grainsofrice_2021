#include <cstdlib>
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Pixel {
    int r;
    int g;
    int b;
};

void print_pixel(Pixel* p) {
    printf("%d %d %d\n", p->r, p->g, p->b);
}

void get(unsigned char * data, int x, int y, int n, 
    int X, int Y, Pixel *pixel) {
    int index = (Y*y*3) + (X*x*3);
    pixel->r = data[index];
    pixel->g = data[index+1];
    pixel->b = data[index+2];
}

// will write a filename called crud.ppm
// that is a P3 type of ppm file
// it can be used to verify the data is the
// same
void verify(unsigned char * data, int x, int y, int n) {
    FILE* outf = fopen("crud.ppm","w");
    fprintf(outf, "P3\n# tony is cool\n");
    fprintf(outf, "%d %d\n",x,y);
    fprintf(outf, "255\n");
    int idx = 0;
    for (int i=0;i<y;i++) {
        for (int j=0;j<x;j++) {
            // read n samples
            for (int k=0;k<n;k++) {
                int r = data[idx++];
                int g = data[idx++];
                int b = data[idx++];
                fprintf(outf, "%d %d %d ",r,g,b);
            }
        }
        fprintf(outf,"\n");
    }
    fclose(outf);
}

// will only write the red channel to the ppm
// effectively making it grayscale
void verify_red(unsigned char * data, int x, int y, int n) {
    FILE* outf = fopen("crud.ppm","w");
    fprintf(outf, "P3\n# tony is cool\n");
    fprintf(outf, "%d %d\n",x,y);
    fprintf(outf, "255\n");
    int idx = 0;
    for (int i=0;i<y;i++) {
        for (int j=0;j<x;j++) {
            // read n samples
            for (int k=0;k<n;k++) {
                int r = data[idx++];
                int g = data[idx++];
                int b = data[idx++];
                fprintf(outf, "%d %d %d ",r,r,r);
            }
        }
        fprintf(outf,"\n");
    }
    fclose(outf);
}

void threshold(unsigned char * data, int x, int y, int n) {
    // only threshold RED component
    int TH = 150;
    FILE* outf = fopen("crud.ppm","w");
    fprintf(outf, "P3\n# tony is cool\n");
    fprintf(outf, "%d %d\n",x,y);
    fprintf(outf, "255\n");
    int idx = 0;
    for (int i=0;i<y;i++) {
        for (int j=0;j<x;j++) {
            // read n samples
            for (int k=0;k<n;k++) {
                int r = data[idx++];
                int g = data[idx++];
                int b = data[idx++];
                if (r>TH) {
                    fprintf(outf, "%d %d %d ",r,r,r);
                } else {
                    fprintf(outf, "255 255 255 ");
                }
            }
        }
        fprintf(outf,"\n");
    }
    fclose(outf);
}

int main() {

    int x;
    int y;
    int n;
    unsigned char * data = stbi_load("A.jpg", &x, &y, &n, 0);
    // x is width
    // y is height
    // n is number of color channels
    // all of ^ is from docs on stb

    // write data out to ppm for debugging only
    verify(data,x,y,n);
    //verify_red(data,x,y,n);

    // do something cool here
    // ???
    //threshold(data,x,y,n);

    Pixel p;
    get(data,x,y,n,
        0,1,&p);
    print_pixel(&p);
    
    return 0;
}