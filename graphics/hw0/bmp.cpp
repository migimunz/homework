#include "image.h"

#include <cstdio>

// Based on an answer from Stack Overflow
// https://stackoverflow.com/a/2654860

Image load_bmp(const char* filename) {
  int w;
  int h;

  unsigned char fileheader[14];
  unsigned char infoheader[40];
  unsigned char padding[4];

  FILE* f = fopen(filename, "rb");
  if(!f) {
    fprintf(stderr, "Unable to open file for reading: %s\n", filename);
    exit(1);
  }

  fread(fileheader, 1, 14, f);
  fread(infoheader, 1, 40, f);

  w  = infoheader[ 4] <<  0;
  w += infoheader[ 5] <<  8;
  w += infoheader[ 6] << 16;
  w += infoheader[ 7] << 24;

  h  = infoheader[ 8] <<  0;
  h += infoheader[ 9] <<  8;
  h += infoheader[10] << 16;
  h += infoheader[11] << 24;

  if(w < 1 || w > 1024 || h < 1 || h > 1024) {
    fprintf(stderr, "Invalid image dimensions: %dx%d\n", w, h);
    exit(1);
  }

  Image image(w, h);

  for(int i = 0; i < h; i++) {
    fread(image.data() + 3*w*i, 3, w, f);
    fread(padding, 1, (4-(w*3)%4)%4, f);
  }

  return image;
}

void save_bmp(const char* filename, const Image& image) {
  int w = image.width();
  int h = image.height();
  int s = 54 + 3*w*h; //TODO: This doesn't include the padding!?

  unsigned char fileheader[14] = {'B','M',  0,0,0,0, 0,0,0,0, 54,0,0,0};
  unsigned char infoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char padding[4]     = {0};

  fileheader[ 2] = s >>  0;
  fileheader[ 3] = s >>  8;
  fileheader[ 4] = s >> 16;
  fileheader[ 5] = s >> 24;

  infoheader[ 4] = w >>  0;
  infoheader[ 5] = w >>  8;
  infoheader[ 6] = w >> 16;
  infoheader[ 7] = w >> 24;

  infoheader[ 8] = h >>  0;
  infoheader[ 9] = h >>  8;
  infoheader[10] = h >> 16;
  infoheader[11] = h >> 24;

  FILE* f = fopen(filename, "wb");
  fwrite(fileheader, 1, 14, f);
  fwrite(infoheader, 1, 40, f);

  for(int i = 0; i < h; i++) {
    fwrite(image.data() + 3*w*i, 3, w, f);
    fwrite(padding, 1, (4-(w*3)%4)%4, f);
  }

  fclose(f);
}
