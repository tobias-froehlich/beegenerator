#include <iostream>
#include <string>
#include <vector>

#include "Image.h"
#include "Bee.h"

Bee::Bee() {

}

Bee::~Bee() {

}

void Bee::setRed(uint8_t red) {
    this->red = red;
}

void Bee::setGreen(uint8_t green) {
    this->green = green;
}

void Bee::setBlue(uint8_t blue) {
    this->blue = blue;
}

void Bee::setRadius(double radius) {
    this->radius = radius;
}

double Bee::getRadius() {
    return radius;
}

void Bee::setX(double x) {
    this->x = x;
}

void Bee::setY(double y) {
    this->y = y;
}

void Bee::setXSpeed(double xSpeed) {
    this->xSpeed = xSpeed;
}

void Bee::setYSpeed(double ySpeed) {
    this->ySpeed = ySpeed;
}

double Bee::getX() {
    return x;
}

double Bee::getY() {
    return y;
}

double Bee::getXSpeed() {
    return xSpeed;
}

double Bee::getYSpeed() {
    return ySpeed;
}

void Bee::draw(Image* image_ptr) {
    int startX = (int)(x - radius);
    int startY = (int)(y - radius);
    std::cout << "Drawing around " << getX() << ", " << getY() << "\n";
    for(int ix=startX; ix<=x+radius+1; ix++) {
        for(int iy=startY; iy<=y+radius+1; iy++) {
            double dx = ix - x;
            double dy = iy - y;
            if (dx*dx + dy*dy <= radius*radius) {
                image_ptr->setPixel(ix, iy,
                        red, green, blue);
            }
        }
    }
}

void Bee::makeStep() {
    x += xSpeed;
    y += ySpeed;
}

int Bee::overlapsWith(Bee* bee_ptr) {
    double radiusSum = this->getRadius()
            + bee_ptr->getRadius();
    double dx = this->getX() - bee_ptr->getX();
    double dy = this->getY() - bee_ptr->getY();
    if (dx*dx + dy*dy < radiusSum*radiusSum) {
        return 1;
    } else {
        return 0;
    }
}
