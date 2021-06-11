#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parameters.h"
#include "Generator.h"

Generator::Generator() {
    
}

Generator::~Generator() {

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

void Generator::readParameterFile(
        std::string parameterFileName) {
    Parameters parameters;

    parameters.read_file(parameterFileName);

    imageWidth = std::stoi(
      parameters.get_value("image_width")
    );
    imageHeight = std::stoi(
      parameters.get_value("image_height")
    );
    borderWidth = std::stoi(
      parameters.get_value("border_width")
    );   
}

