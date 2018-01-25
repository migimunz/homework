#ifndef IMAGE_H
#define IMAGE_H

#include <algorithm>
#include <cstring>

class Image {
protected:
  int mWidth;
  int mHeight;
  unsigned char* mData;
public:
  Image() {
    mWidth  = 0;
    mHeight = 0;
    mData   = NULL;
  }

  Image(Image&& other) {
    mWidth  = other.width();
    mHeight = other.height();
    mData   = other.data();
    other.mData = NULL;
  }

  Image(const Image& other) {
    mWidth  = other.width();
    mHeight = other.height();
    mData   = new unsigned char[3 * area()];
    std::memcpy(mData, other.mData, 3 * area());
  }

  Image(int w, int h) {
    mWidth  = w;
    mHeight = h;
    mData   = new unsigned char[3 * area()];
  }

  ~Image() {
    delete [] mData;
  }

  int area() const {
    return mWidth * mHeight;
  }

  unsigned char* data() {
    return mData;
  }

  const unsigned char* data() const {
    return mData;
  }

  int height() const {
    return mHeight;
  }

  int width() const {
    return mWidth;
  }
};

Image load_bmp(const char* filename);
void save_bmp(const char* filename, const Image& image);

#endif
