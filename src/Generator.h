#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator {
    private:
       Parameters* parameters_ptr;
       int type = 0; // 0: train, 1: val, 2: test
       std::string dataDirectory = "";
       int numberOfDigits = 0;
       int numberOfImages = 0;
       int numberOfStepsBeforeVideoStarts = 0;
       int imageWidth = 0;
       int imageHeight = 0;
       int borderWidth = 0;
       int numberOfBees = 0;
       double xCountLine;
       utils::Color backgroundColor;
       Image* image_ptr;
       std::vector<Bee*> bee_ptrs;
    public:
        Generator(Parameters* parameters_ptr,
                int type);
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
