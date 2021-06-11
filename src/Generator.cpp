#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "const.h"
#include "utils.h"
#include "Parameters.h"
#include "Image.h"
#include "Bee.h"
#include "Generator.h"

Generator::Generator(
        std::string parameterFileName) {
     Parameters parameters;

    parameters.read_file(parameterFileName);

    beginOfFilenames = parameters.get_value(
            "begin_of_filenames");
    numberOfDigits = std::stoi(
      parameters.get_value("number_of_digits")
    );
    numberOfImages = std::stoi(
      parameters.get_value("number_of_images")
    );
    if (std::pow(10, numberOfDigits) + 0.01 <= numberOfImages) {
        throw std::invalid_argument(
            "Number of digits too small"
        );
    }
    imageWidth = std::stoi(
      parameters.get_value("image_width")
    );
    imageHeight = std::stoi(
      parameters.get_value("image_height")
    );
    borderWidth = std::stoi(
      parameters.get_value("border_width")
    );
    numberOfBees = std::stoi(
      parameters.get_value("number_of_bees")
    );

    image_ptr = new Image(imageWidth, imageHeight);

    std::vector<std::string> color = 
            parameters.get_values("color_of_bees");

    beeRed = std::stoi(color[0]);
    beeGreen = std::stoi(color[1]);
    beeBlue = std::stoi(color[2]);

    color = parameters.get_values(
            "background_color");

    backgroundRed = std::stoi(color[0]);
    backgroundGreen = std::stoi(color[1]);
    backgroundBlue = std::stoi(color[2]);

    radiusOfBees = std::stof(
        parameters.get_value("radius_of_bees"));
    minStartSpeed = std::stof(
        parameters.get_value("min_start_speed"));
    maxStartSpeed = std::stof(
        parameters.get_value("max_start_speed"));

    std::srand(std::time(nullptr));
    for(int i=0; i<numberOfBees; i++) {
        createNewBee();
    }


    for(Bee* bee_ptr : bee_ptrs) {
        std::cout << "x = " << bee_ptr->getX() << ", y = " << bee_ptr->getY() << "\n";
    }

}

Generator::~Generator() {
    delete image_ptr;
}

void Generator::createNewBee() {
    Bee* newbee_ptr = new Bee();
    newbee_ptr->setRed(beeRed);
    newbee_ptr->setGreen(beeGreen);
    newbee_ptr->setBlue(beeBlue);
    newbee_ptr->setRadius(radiusOfBees);
    int occupied = 1;
    while (occupied) {
        double x =  (std::rand() % (int)((imageWidth-2*radiusOfBees) * 1000)) * 0.001 + radiusOfBees;
        double y = (std::rand() % (int)((imageHeight-2*radiusOfBees) * 1000)) * 0.001 + radiusOfBees;
        newbee_ptr->setX(x);
        newbee_ptr->setY(y);
        occupied = 0;
        for(Bee* bee_ptr : bee_ptrs) {
            if (newbee_ptr->overlapsWith(bee_ptr)) {
                occupied = 1;
            }
        }
    }
    double speed = ((std::rand() % (int)(maxStartSpeed) * 1000)) * 0.001 + minStartSpeed;
    double angle = (std::rand() % (int)(360000)) * 0.001 * cPiOver180;
    std::cout << "speed = " << speed << "\n";
    std::cout << "angle = " << angle << "\n";
    double xSpeed = std::cos(angle) * speed;
    double ySpeed = std::sin(angle) * speed;
    newbee_ptr->setXSpeed(xSpeed);
    newbee_ptr->setYSpeed(ySpeed);
    bee_ptrs.push_back(newbee_ptr);
}


int Generator::getImageWidth() {
    return imageWidth;
}

int Generator::getImageHeight() {
    return imageHeight;
}

int Generator::getBorderWidth() {
    return borderWidth;
}

void Generator::writeImage(
        std::string imageFileName) {
    image_ptr->fill(backgroundRed,
            backgroundGreen, backgroundBlue);
    for(Bee* bee_ptr : bee_ptrs) {
        std::cout << "This bee is at " << bee_ptr->getX() << ", " << bee_ptr->getY() << "\n";
        bee_ptr->draw(image_ptr);
    }
    image_ptr->write(imageFileName);
}


void Generator::makeStep() {
    for(Bee* bee_ptr : bee_ptrs) {
        bee_ptr->makeStep();
        double x = bee_ptr->getX();
        double y = bee_ptr->getY();
        if ((x < radiusOfBees)
            || (x >= imageWidth - radiusOfBees)) {
            bee_ptr->setXSpeed(
                -bee_ptr->getXSpeed()
            );
        }
        if ((y < radiusOfBees) || (y >= imageHeight - radiusOfBees)) {
            bee_ptr->setYSpeed(
                -bee_ptr->getYSpeed()
            );
        }
    }

}

void Generator::makeVideo() {
    for(int i=0; i<numberOfImages; i++) {
        std::string filename(beginOfFilenames);
        filename.append(
            utils::intToStringLeadingZeros(
                i, numberOfDigits
            )
        );
        filename.append(".png");
        makeStep();
        writeImage(filename);
    }
}
