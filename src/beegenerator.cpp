#include <iostream>
#include <vector>
#include <string>
#include "beegeneratorConfig.h"
#include "const.h"
#include "utils.h"
#include "Parameters.h"
#include "Image.h"
#include "Bee.h"
#include "Generator.h"

using std::uint8_t;
using std::uint32_t;
using std::size_t;

int main(int argc, char** argv) {
    if (argc == 2) {
        std::string parameterFilename(argv[1]);
        std::cout << "parameter filename: "
                << parameterFilename << "\n";

        Parameters* parameters_ptr
                = new Parameters();
        parameters_ptr->read_file(
                parameterFilename);

        Generator* generator_ptr;

        std::cout << "Generating train data:\n";
        generator_ptr = 
                new Generator(parameters_ptr, 0);
        generator_ptr->makeVideo();
        delete generator_ptr;

        std::cout << "Generating val data:\n";
        generator_ptr = 
                new Generator(parameters_ptr, 1);
        generator_ptr->makeVideo();
        delete generator_ptr;

        std::cout << "Generating test data:\n";
        generator_ptr = 
                new Generator(parameters_ptr, 2);
        generator_ptr->makeVideo();
        delete generator_ptr;


        delete parameters_ptr;
    } else {
        std::cout << "One parameter needed that specifies the parameter file.\n";        
    }
}
