#ifndef BEE_H_
#define BEE_H_

class Bee {
    private:
        Parameters* parameters_ptr;
        int imageWidth;
        int imageHeight;
        int borderWidth;
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        double radius = 0;
        double minStartSpeed = 0;
        double maxStartSpeed = 0;
        double brownianProbability = 0;
        double brownianStrength = 0;
        double oneMinusFriction = 0;
        double x = 0;
        double y = 0;
        double xLastCount = 0;
        double yLastCount = 0;
        double xSpeed = 0;
        double ySpeed = 0;
        double xCountLine = 0;
    public:
        Bee(Parameters* parameters_ptr);
        ~Bee();
        void setRed(uint8_t red);
        void setGreen(uint8_t green);
        void setBlue(uint8_t blue);
        void setRadius(double radius);
        double getRadius();
        void setXCountLine(double xCountLine);
        void setX(double x);
        void setY(double y);
        void setXSpeed(double xSpeed);
        void setYSpeed(double ySpeed);
        double getX();
        double getY();
        double getXSpeed();
        double getYSpeed();
        void randomLocation();
        void randomSpeed();
        void draw(Image* image_ptr);
        void applyFriction();
        void applyBrownianMotion();
        void makeStep(double factor);
        int getUndone();
        void collideWithWalls();
        int overlapsWith(Bee* bee_ptr);
        void reflectAt(Bee* bee_ptr);
        void collideWith(Bee* bee_ptr);
        int count();
};

#endif
