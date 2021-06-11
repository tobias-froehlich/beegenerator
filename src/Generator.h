#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator {
    private:
       std::string beginOfFilenames = "";
       int numberOfDigits = 0;
       int numberOfImages = 0;
       int imageWidth = 0;
       int imageHeight = 0;
       int borderWidth = 0;
       int numberOfBees = 0;
       double radiusOfBees = 0;
       double minStartSpeed = 0;
       double maxStartSpeed = 0;
       uint8_t backgroundRed = 0;
       uint8_t backgroundGreen = 0;
       uint8_t backgroundBlue = 0;
       uint8_t beeRed = 0;
       uint8_t beeGreen = 0;
       uint8_t beeBlue = 0;
       Image* image_ptr;
       std::vector<Bee*> bee_ptrs;
    public:
        Generator(std::string parameterFileName);
        ~Generator();
        void createNewBee();
        int getImageWidth();
        int getImageHeight();
        int getBorderWidth();
        void writeImage(std::string imageFileName);
        void makeStep();
        void makeVideo();
};

#endif
