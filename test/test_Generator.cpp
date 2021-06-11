#include "../src/Generator.h"

TEST (Generator, create_and_delete ) {
    Generator* generator;
    generator = new Generator();
    delete generator;
}

TEST (Generator, read_parameters) {
    Generator* generator = new Generator();
    ASSERT_THROW(
        generator->readParameterFile("notexisting_file.txt"),
        std::invalid_argument
    );

    generator->readParameterFile(
        "../test/testfiles/generator_parameters.txt"
    );
    ASSERT_EQ(generator->getImageWidth(), 30);
    ASSERT_EQ(generator->getImageHeight(), 50);
    ASSERT_EQ(generator->getBorderWidth(), 20);


    delete generator;
}


