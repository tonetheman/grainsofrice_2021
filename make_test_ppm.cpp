#include <cstdlib>
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// make a simple test image
// with known values
void create_test_image() {
    FILE * outf = fopen("testimage.ppm","w'");
    fprintf(outf,"P3\n");
    fprintf(outf,"#tony is cool\n");

    int width = 32;
    int height = 4;
    fprintf(outf,"%d %d\n",width,height);
    fprintf(outf, "255\n");

    for(int j=0;j<4;j++) {
        for (int i=0;i<width;i++) {
            fprintf(outf, "%d %d %d ", i, j, ((i*j)%255));
        }
        fprintf(outf,"\n");
    }

    fclose(outf);
}

// call out to /usr/local/bin/convert
// to convert the image from ppm to png
void convert(const char *in_filename, const char *out_filename) {
    char buffer[512];
    memset(buffer,'\0',512);
    sprintf(buffer,"/usr/local/bin/convert %s %s",in_filename, out_filename);
    int res = system(buffer);
    printf("res: from convert: %d\n", res);
}


struct Pixel {
    int r;
    int g;
    int b;
};

void print_pixel(Pixel& p) {
    printf("%d %d %d\n", p.r, p.g, p.b);
}


struct Image {
    // x is width
    // y is height
    // n is number of color channels
    // all of ^ is from docs on stb
    unsigned char * data;
    int width;
    int height;
    int channels;

    Image(const char * filename) {
        printf("before loading image..\n");
        this->data = stbi_load(filename, 
            &(this->width), &(this->height), &(this->channels), 0);
        printf("done loading image\n");
        printf("x y n: %d %d %d\n",width,height,channels);
    }

    void get(int x, int y, Pixel *pixel) {
        int index = (y*this->height*3) + (x*this->width*3);
        pixel->r = data[index];
        pixel->g = data[index+1];
        pixel->b = data[index+2];
    }

};

void reading() {
    Image img("testimage.png");
    for(int i=0;i<32*4*3;i++) {
        printf("%d\n",img.data[i]);
    }
}

void writing() {
    char buffer[32*4*3];
    int pos = 0;
    for(int j=0;j<4;j++) {
        for (int i=0;i<32;i++) {
            buffer[pos++] = i;
            buffer[pos++] = j;
            buffer[pos++] = (i*j)%255;
        }
    }

    int res = stbi_write_png("out.png",
        32,4, // width and height
        3, // channels
        buffer,
        32*3); // stride, distance between rows
    // res == 0 is FAILURE
    // anything else is SUCCESS
    
    printf("res from write: %d\n",res);
}

int main() {

    // create_test_image();
    // convert("testimage.ppm","testimage.png");

    // reading();

    // writing();

    return 0;
}