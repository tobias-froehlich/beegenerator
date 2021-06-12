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
        Parameters* parameters_ptr) {

    this->parameters_ptr = parameters_ptr;

    beginOfFilenames = parameters_ptr->get_string(
            "begin_of_filenames");
    countFilename = parameters_ptr->get_string(
            "count_filename");
    numberOfDigits =  parameters_ptr->get_int(
            "number_of_digits");
    numberOfImages = parameters_ptr->get_int(
            "number_of_images");
    if (std::pow(10, numberOfDigits) + 0.01
            <= numberOfImages) {
        throw std::invalid_argument(
            "Number of digits too small"
        );
    }
    imageWidth = parameters_ptr->get_int(
            "image_width");
    imageHeight = parameters_ptr->get_int(
            "image_height");
    borderWidth = parameters_ptr->get_int(
            "border_width");
    numberOfBees = parameters_ptr->get_int(
            "number_of_bees");

    image_ptr = new Image(imageWidth, imageHeight);

    backgroundColor = utils::vectorToColor(
        parameters_ptr->get_ints(
            "background_color"
        )
    );

    xCountLine = parameters_ptr->get_float(
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
    Bee* newbee_ptr = new Bee(parameters_ptr);
    int occupied = 1;
    while (occupied) {
        newbee_ptr->randomLocation();
        occupied = 0;
        for(Bee* bee_ptr : bee_ptrs) {
            if (newbee_ptr->overlapsWith(bee_ptr)) {
                occupied = 1;
            }
        }
    }
    newbee_ptr->randomSpeed();
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
    image_ptr->fill(backgroundColor);
    for(Bee* bee_ptr : bee_ptrs) {
            bee_ptr->draw(image_ptr);
    }
    image_ptr->write(imageFileName);
}


void Generator::makeStep() {
    for(Bee* bee_ptr : bee_ptrs) {
        bee_ptr->makeStep(1.0);
        bee_ptr->collideWithWalls();
    }
    for(int i1=1; i1<numberOfBees; i1++) {
        for(int i2=0; i2<i1; i2++) {
            bee_ptrs[i1]->collideWith(bee_ptrs[i2]);
        }
    }
    for(Bee* bee_ptr : bee_ptrs) {
        bee_ptr->applyFriction();
        bee_ptr->applyBrownianMotion();
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
