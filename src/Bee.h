#ifndef BEE_H_
#define BEE_H_

class Bee {
    private:
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        double radius = 0;
        double x = 0;
        double y = 0;
        double xSpeed = 0;
        double ySpeed = 0;
    public:
        Bee();
        ~Bee();
        void setRed(uint8_t red);
        void setGreen(uint8_t green);
        void setBlue(uint8_t blue);
        void setRadius(double radius);
        double getRadius();
        void setX(double x);
        void setY(double y);
        void setXSpeed(double xSpeed);
        void setYSpeed(double ySpeed);
        double getX();
        double getY();
        double getXSpeed();
        double getYSpeed();
        void draw(Image* image_ptr);
        void makeStep();
        int overlapsWith(Bee* bee_ptr);
};

#endif
