#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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
    this->xOld = x;
}

void Bee::setY(double y) {
    this->y = y;
    this->yOld = y;
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

void Bee::makeStep(double factor) {
    xOld = x;
    yOld = y;
    x += xSpeed * factor;
    y += ySpeed * factor;
    undone = 0;
}

void Bee::undo() {
    x = xOld;
    y = yOld;
    undone = 1;
}

int Bee::getUndone() {
    return undone;
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

void Bee::collideWith(Bee* bee_ptr) {
    double x1 = this->getX();
    double y1 = this->getY();
    double xSpeed1 = this->getXSpeed();
    double ySpeed1 = this->getYSpeed();
    double x2 = bee_ptr->getX();
    double y2 = bee_ptr->getY();
    double xSpeed2 = bee_ptr->getXSpeed();
    double ySpeed2 = bee_ptr->getYSpeed();

    double dX = x1 - x2;
    double dY = y1 - y2;
    double distance = std::sqrt(dX*dX + dY*dY);
   
    dX /= distance;
    dY /= distance;

    double prod1 = xSpeed1 * dX + ySpeed1 * dY;
    double xSpeed1par = prod1 * dX;
    double ySpeed1par = prod1 * dY;
    double xSpeed1vert = xSpeed1 - xSpeed1par;
    double yspeed1vert = ySpeed1 - ySpeed1par;

    double prod2 = xSpeed2 * dX + ySpeed2 * dY;
    double xSpeed2par = prod2 * dX;
    double ySpeed2par = prod2 * dY;
    double xSpeed2vert = xSpeed2 - xSpeed2par;
    double yspeed2vert = ySpeed2 - ySpeed2par;

    xSpeed1 += -xSpeed1par + xSpeed2par;
    ySpeed1 += -ySpeed1par + ySpeed2par;

    xSpeed2 += -xSpeed2par + xSpeed1par;
    ySpeed2 += -ySpeed2par + ySpeed1par;


    this->setXSpeed(xSpeed1);
    this->setYSpeed(ySpeed1);

    bee_ptr->setXSpeed(xSpeed2);
    bee_ptr->setYSpeed(ySpeed2);
}
