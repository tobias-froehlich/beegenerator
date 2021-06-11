#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator {
    private:
       int imageWidth = 0;
       int imageHeight = 0;
       int borderWidth = 0;
    public:
        Generator();
        ~Generator();
        int getImageWidth();
        int getImageHeight();
        int getBorderWidth();
        void readParameterFile(
                std::string parameterFileName);
};

#endif
