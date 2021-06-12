#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator {
    private:
       Parameters* parameters_ptr;
       std::string beginOfFilenames = "";
       std::string countFilename = "";
       int numberOfDigits = 0;
       int numberOfImages = 0;
       int imageWidth = 0;
       int imageHeight = 0;
       int borderWidth = 0;
       int numberOfBees = 0;
       double xCountLine;
       uint8_t backgroundRed = 0;
       uint8_t backgroundGreen = 0;
       uint8_t backgroundBlue = 0;
       Image* image_ptr;
       std::vector<Bee*> bee_ptrs;
       std::vector< std::vector< int > > counts;
    public:
        Generator(Parameters* parameters_ptr);
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
