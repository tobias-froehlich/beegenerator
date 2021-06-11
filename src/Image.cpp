#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../libs/tinypngout/TinyPngOut.hpp"
#include "Image.h"

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    pixels = new uint8_t[width*height*3];
    for(int i=0; i<width*height*3; i++) {
        pixels[i] = 128;
    }
}


Image::~Image() {
    delete[] pixels;
}

void Image::fill(uint8_t red, uint8_t green,
        uint8_t blue) {
    int n = width * height;
    int i3;
    for(int i=0; i<n; i++) {
        i3 = 3*i;
        pixels[i3] = red;
        pixels[i3 + 1] = green;
        pixels[i3 + 2] = blue;
    }
}

int Image::getWidth() {
    return width;
}

int Image::getHeight() {
    return height;
}


uint8_t Image::getPixel(int x, int y, int channel) {
    if ((x >= 0) && (x < width)
            && (y >= 0) && (y < height)
            && (channel >= 0) && (channel < 3)) {
        return pixels[3*width*y + 3*x + channel];
    } else {
        return 0;
    }
}


void Image::setPixel(int x, int y, int channel,
        uint8_t value) {
    if ((x >= 0) && (x < width)
            && (y >= 0) && (y < height)
            && (channel >= 0) && (channel < 3)) {
        pixels[3*width*y + 3*x + channel] = value;
    }
}

void Image::setPixel(int x, int y, uint8_t red,
        uint8_t green, uint8_t blue) {
    if ((x >= 0) && (x < width)
            && (y >= 0) && (y < height)) {
        int i = 3*width*y + 3*x;
        pixels[i] = red;
        pixels[i+1] = green;
        pixels[i+2] = blue;
    }
}

void Image::write(
        std::string fileName) {
    try {
        std::ofstream out(fileName, std::ios::binary);
        TinyPngOut pngout(static_cast<uint32_t>(width), static_cast<uint32_t>(height), out);
        pngout.write(pixels, static_cast<size_t>(width * height));
    } catch (const char *msg) {
        std::cerr << msg << std::endl;
    }
}
