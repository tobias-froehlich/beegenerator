#include "../src/Generator.h"

TEST (Generator, create_and_delete ) {

    Generator* generator_ptr;
    Parameters* parameters_ptr = new Parameters();

    parameters_ptr->read_file(
        "../test/testfiles/generator_parameters_wrong1.txt");

    ASSERT_THROW(
        generator_ptr = new Generator(parameters_ptr, 0),
        std::invalid_argument
    );

    delete parameters_ptr;

    parameters_ptr = new Parameters();

    parameters_ptr->read_file(
        "../test/testfiles/generator_parameters.txt");

    generator_ptr = new Generator(parameters_ptr, 0);

    ASSERT_EQ(generator_ptr->getImageWidth(), 200);
    ASSERT_EQ(generator_ptr->getImageHeight(), 200);
    ASSERT_EQ(generator_ptr->getBorderWidth(), 300);

    delete generator_ptr;
}

TEST (Generator, write_image) {
    Parameters* parameters_ptr = new Parameters();
    parameters_ptr->read_file("../test/testfiles/generator_parameters.txt");
    Generator generator(parameters_ptr, 0);

    generator.writeImage("/tmp/test_bees.png");
    delete parameters_ptr;
}

TEST (Generator, makeVideo) {
    std::srand(std::time(nullptr));

    Parameters* parameters_ptr = new Parameters();
    parameters_ptr->read_file("../test/testfiles/generator_parameters.txt");
    Generator generator(parameters_ptr, 0);
    generator.makeVideo();
    delete parameters_ptr;
}
