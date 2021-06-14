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
        Parameters* parameters_ptr, int type) {

    this->parameters_ptr = parameters_ptr;

    this->type = type;

    dataDirectory = parameters_ptr->get_string(
            "data_directory");
    numberOfDigits =  parameters_ptr->get_int(
            "number_of_digits");

    if (type == 0) {
        numberOfImages = parameters_ptr->get_int(
                "number_of_train_images");
    } else if (type == 1) {
        numberOfImages = parameters_ptr->get_int(
                "number_of_val_images");
    } else if (type == 2) {
        numberOfImages = parameters_ptr->get_int(
                "number_of_test_images");
    }

    numberOfStepsBeforeVideoStarts =
            parameters_ptr->get_int(
            "number_of_steps_before_video_starts");
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

    for(int i=0; i<numberOfBees; i++) {
        createNewBee();
    }

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

    for(int i=0; i<numberOfStepsBeforeVideoStarts;
            i++) {
        makeStep();
    }

    std::string imageFilename(dataDirectory);
    std::string countFilename(dataDirectory);
    countFilename.append("counts_");
    if (type == 0) {
        countFilename.append("train.txt");
        imageFilename.append("train_");
    } else if (type == 1) {
        countFilename.append("val.txt");
        imageFilename.append("val_");
    } else if (type == 2) {
        countFilename.append("test.txt");
        imageFilename.append("test_");
    }

    std::ofstream file(countFilename);

    
    for(int i=0; i<numberOfImages; i++) {
        if (i % 100 == 0) {
            std::cout << "Progress: " << i << " of " << numberOfImages << "\r";
            fflush(stdout);
        }
        std::string filename(imageFilename);
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
        writeImage(filename);
        file
            << utils::intToStringLeadingZeros(
                i, numberOfDigits
            )
            << " "
            << left << " " << right << "\n";
    }
    file.close();
    std::cout << "Data generated successfully.\n";
    fflush(stdout);
}
