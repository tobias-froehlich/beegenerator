#include "../src/Generator.h"

TEST (Generator, create_and_delete ) {
    Generator* generator;
    ASSERT_THROW(
        generator = new Generator("notexist.txt"),
        std::invalid_argument
    );

    ASSERT_THROW(
        generator = new Generator(
          "../test/testfiles/generator_parameters_wrong1.txt"),
        std::invalid_argument
    );

    generator = new Generator(
    "../test/testfiles/generator_parameters.txt");


    ASSERT_EQ(generator->getImageWidth(), 50);
    ASSERT_EQ(generator->getImageHeight(), 75);
    ASSERT_EQ(generator->getBorderWidth(), 100);

    delete generator;
}

TEST (Generator, write_image) {
    Generator generator(
    "../test/testfiles/generator_parameters.txt");

    generator.writeImage("/tmp/test_bees.png");
}

TEST (Generator, makeVideo) {
    Generator generator(
    "../test/testfiles/generator_parameters.txt");
    generator.makeVideo();
}
