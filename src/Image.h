#ifndef IMAGE_H_
#define IMAGE_H_

class Image {
    private:
        int width = 0;
        int height = 0;
        uint8_t* pixels;
    public:
        Image(int width, int height);
        ~Image();
        void fill(uint8_t red, uint8_t green,
                uint8_t blue);
        int getWidth();
        int getHeight();
        uint8_t getPixel(int x, int y, int channel);
        void setPixel(int x, int y, int channel,
                uint8_t value);
        void setPixel(int x, int y, uint8_t red,
                uint8_t green, uint8_t blue);
        void write(std::string fileName);
};


#endif
