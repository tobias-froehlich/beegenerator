#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "const.h"
#include "Parameters.h"
#include "Image.h"
#include "Bee.h"

Bee::Bee(Parameters* parameters_ptr) {
    this->parameters_ptr = parameters_ptr;
    std::vector< int > color =
            parameters_ptr->get_ints(
            "color_of_bees");
    red = color[0];
    green = color[1];
    blue = color[2];
    radius = parameters_ptr->get_float(
            "radius_of_bees");
    xCountLine = parameters_ptr->get_float(
            "x_count_line");
    imageWidth = parameters_ptr->get_int(
            "image_width");
    imageHeight = parameters_ptr->get_int(
            "image_height");
    borderWidth = parameters_ptr->get_int(
            "border_width");
    minStartSpeed = parameters_ptr->get_float(
            "min_start_speed");
    maxStartSpeed = parameters_ptr->get_float(
            "max_start_speed");
    brownianProbability = parameters_ptr->get_float(
            "brownian_probability");
    brownianStrength = parameters_ptr->get_float(
            "brownian_strength");
    oneMinusFriction = 1
            - parameters_ptr->get_float(
            "friction");
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

void Bee::setXCountLine(double xCountLine) {
    this->xCountLine = xCountLine;
}

void Bee::setX(double x) {
    this->x = x;
    this->xLastCount = x;
}

void Bee::setY(double y) {
    this->y = y;
    this->yLastCount = y;
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

void Bee::randomLocation() {
        x =  (
            std::rand()
            % (int)(
                (
                    imageWidth-2*radius
                  + 2*borderWidth
                ) * 1000
            )
        ) * 0.001 + radius - borderWidth;
        y = (
            std::rand()
            % (int)(
                (imageHeight-2*radius) * 1000
            )
        ) * 0.001 + radius;
         
}

void Bee::randomSpeed() {
    double speed = (std::rand() % (int)(maxStartSpeed * 1000.0)) * 0.001 + minStartSpeed;
    double angle = (std::rand() % (int)(360000)) * 0.001 * cPiOver180;
    xSpeed = std::cos(angle) * speed;
    ySpeed = std::sin(angle) * speed;
}

void Bee::draw(Image* image_ptr) {
    if(( x >= -radius)
      && (x <= imageWidth + radius)) {
        int startX = (int)(x - radius);
        int startY = (int)(y - radius);
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
}

void Bee::applyFriction() {
    xSpeed *= oneMinusFriction;
    ySpeed *= oneMinusFriction;
}

void Bee::applyBrownianMotion() {
    if ((std::rand() % 10000) * 0.0001 
            < brownianProbability) {
        double speed = (std::rand() % (int)(brownianStrength * 1000.0)) * 0.001;
        double angle = (std::rand() % (int)(360000)) * 0.001 * cPiOver180;
        xSpeed = std::cos(angle) * speed;
        ySpeed = std::sin(angle) * speed;
    }
}

void Bee::makeStep(double factor) {
    x += xSpeed * factor;
    y += ySpeed * factor;
}

void Bee::collideWithWalls() {
    if ((x < -borderWidth + radius)
        || (x >= imageWidth + borderWidth)) {
        xSpeed = -xSpeed;
        if (x < -borderWidth + radius) {
            x = -borderWidth + radius + 1;
        } else {
            x = imageWidth + borderWidth - radius - 1;
        }
    }
    if ((y < radius) || (y >= imageHeight - radius)) {
        ySpeed = -ySpeed;
        if (y < radius) {
            y = radius + 1;
        } else {
            y = imageHeight - radius - 1;
        }
    }
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

void Bee::reflectAt(Bee* bee_ptr) {
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
    this->setX(x1 + dX);
    this->setY(y1 + dY);

    bee_ptr->setXSpeed(xSpeed2);
    bee_ptr->setYSpeed(ySpeed2);
    bee_ptr->setX(x2 - dX);
    bee_ptr->setY(y2 - dY);
}

void Bee::collideWith(Bee* bee_ptr) {
    if (this->overlapsWith(bee_ptr)) {
        this->reflectAt(bee_ptr);
    }
}

int Bee::count() {
   int result = 0;
   if ((xLastCount <= xCountLine)
     && (x > xCountLine)) {
         result = 1;
         std::cout << "counted 1 because moved from " << xLastCount << " to " << x << "\n";
   }
   if ((xLastCount > xCountLine)
     && (x <= xCountLine)) {
         result = -1;
         std::cout << "counted -1 because moved from " << xLastCount << " to " << x << "\n";
   }
   xLastCount = x;
   yLastCount = y;
   return result;
}
