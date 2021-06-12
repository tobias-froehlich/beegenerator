#include <iostream>
#include <fstream>
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

    beginOfFilenames = parameters.get_string(
            "begin_of_filenames");
    countFilename = parameters.get_string(
            "count_filename");
    numberOfDigits =  parameters.get_int(
            "number_of_digits");
    numberOfImages = parameters.get_int(
            "number_of_images");
    if (std::pow(10, numberOfDigits) + 0.01
            <= numberOfImages) {
        throw std::invalid_argument(
            "Number of digits too small"
        );
    }
    imageWidth = parameters.get_int(
            "image_width");
    imageHeight = parameters.get_int(
            "image_height");
    borderWidth = parameters.get_int(
            "border_width");
    numberOfBees = parameters.get_int(
            "number_of_bees");

    image_ptr = new Image(imageWidth, imageHeight);

    std::vector<std::string> color = 
            parameters.get_strings("color_of_bees");

    beeRed = std::stoi(color[0]);
    beeGreen = std::stoi(color[1]);
    beeBlue = std::stoi(color[2]);

    color = parameters.get_strings(
            "background_color");

    backgroundRed = std::stoi(color[0]);
    backgroundGreen = std::stoi(color[1]);
    backgroundBlue = std::stoi(color[2]);

    radiusOfBees = parameters.get_float(
            "radius_of_bees");
    minStartSpeed = parameters.get_float(
            "min_start_speed");
    maxStartSpeed = parameters.get_float(
            "max_start_speed");
    brownianProbability = parameters.get_float(
            "brownian_probability");
    brownianStrength = parameters.get_float(
            "brownian_strength");
    oneMinusFriction = 1.0 - parameters.get_float(
            "friction");
    xCountLine = parameters.get_float(
            "x_count_line");

    std::srand(std::time(nullptr));
    for(int i=0; i<numberOfBees; i++) {
        createNewBee();
    }

    counts = {};
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
        double x =  (std::rand() % (int)((imageWidth-2*radiusOfBees + 2*borderWidth) * 1000)) * 0.001 + radiusOfBees - borderWidth;
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
    double speed = (std::rand() % (int)(maxStartSpeed * 1000.0)) * 0.001 + minStartSpeed;
    double angle = (std::rand() % (int)(360000)) * 0.001 * cPiOver180;
    double xSpeed = std::cos(angle) * speed;
    double ySpeed = std::sin(angle) * speed;
    newbee_ptr->setXSpeed(xSpeed);
    newbee_ptr->setYSpeed(ySpeed);
    newbee_ptr->setXCountLine(xCountLine);
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
        int x = bee_ptr->getX();
        if ((x >= -radiusOfBees)
            && (x <= imageWidth + radiusOfBees)) {
            bee_ptr->draw(image_ptr);
        }
    }
    image_ptr->write(imageFileName);
}


void Generator::makeStep() {
    for(Bee* bee_ptr : bee_ptrs) {
        bee_ptr->makeStep(1.0);
        double x = bee_ptr->getX();
        double y = bee_ptr->getY();
        if ((x < -borderWidth + radiusOfBees)
            || (x >= imageWidth + borderWidth - radiusOfBees)) {
            bee_ptr->setXSpeed(
                -bee_ptr->getXSpeed()
            );
            if (x < -borderWidth + radiusOfBees) {
                bee_ptr->setX(-borderWidth + radiusOfBees + 1);
            } else {
                bee_ptr->setX(imageWidth + borderWidth - radiusOfBees - 1);
            }
        }
        if ((y < radiusOfBees) || (y >= imageHeight - radiusOfBees)) {
            bee_ptr->setYSpeed(
                -bee_ptr->getYSpeed()
            );
            if (y < radiusOfBees) {
                bee_ptr->setY(radiusOfBees + 1);
            } else {
                bee_ptr->setY(imageHeight - radiusOfBees - 1);
            }
        }
    }
    for(int i1=1; i1<numberOfBees; i1++) {
        for(int i2=0; i2<i1; i2++) {
            if (bee_ptrs[i1]->overlapsWith(
                    bee_ptrs[i2])) {
                bee_ptrs[i1]->collideWith(
                        bee_ptrs[i2]);
                bee_ptrs[i1]->undo();
                bee_ptrs[i2]->undo();
            }
        }
    }

    for(Bee* bee_ptr : bee_ptrs) {
        bee_ptr->setXSpeed(
            bee_ptr->getXSpeed() * oneMinusFriction
        );
        bee_ptr->setYSpeed(
            bee_ptr->getYSpeed() * oneMinusFriction
        );
        if ((std::rand() % 10000) * 0.0001 
                < brownianProbability) {
            double speed = (std::rand() % (int)(brownianStrength * 1000.0)) * 0.001;
            double angle = (std::rand() % (int)(360000)) * 0.001 * cPiOver180;
            double xSpeed = std::cos(angle) * speed;
            double ySpeed = std::sin(angle) * speed;
            bee_ptr->setXSpeed(
                bee_ptr->getXSpeed()
                + xSpeed
            );
            bee_ptr->setYSpeed(
                bee_ptr->getYSpeed()
                + ySpeed
            );
        }

    }

}

void Generator::makeVideo() {
    counts = {};
    for(int i=0; i<numberOfImages; i++) {
        std::cout << i << " of " << numberOfImages << "\n";
        std::string filename(beginOfFilenames);
        filename.append(
            utils::intToStringLeadingZeros(
                i, numberOfDigits
            )
        );
        filename.append(".png");
        makeStep();
        int left = 0;
        int right = 0;
        for(Bee* bee_ptr : bee_ptrs) {
            int c = bee_ptr->count();
            if (c == 1) {
              right += 1;
            } else if (c == -1) {
              left += 1;
            }
        }
        std::vector<int> vec = {left, right};
        counts.push_back(vec);
        writeImage(filename);
    }

    std::ofstream file(countFilename);
    int linenumber = 0;
    for(std::vector<int> vec : counts) {
        file
            << utils::intToStringLeadingZeros(
                linenumber, numberOfDigits
            )
            << " "
            << vec[0] << " " << vec[1] << "\n";
        linenumber++;
    }
    file.close();
}
