#include "../src/Image.h"
#include "../src/Bee.h"


TEST (Bee, create_and_delete) {
    Parameters* parameters_ptr = new Parameters("../test/testfiles/generator_parameters.txt");
    Bee bee(parameters_ptr);
    bee.setRadius(4);
    bee.setX(5);
    bee.setY(6);
    bee.setXSpeed(10);
    bee.setYSpeed(11);
    ASSERT_FLOAT_EQ(bee.getX(), 5);
    ASSERT_FLOAT_EQ(bee.getY(), 6);
    ASSERT_FLOAT_EQ(bee.getXSpeed(), 10);
    ASSERT_FLOAT_EQ(bee.getYSpeed(), 11);
    ASSERT_FLOAT_EQ(bee.getRadius(), 4);
}

TEST (Bee, draw) {
    Parameters* parameters_ptr = new Parameters("../test/testfiles/generator_parameters.txt");
    Bee bee(parameters_ptr);
    bee.setRed(250);
    bee.setGreen(200);
    bee.setBlue(30);
    bee.setRadius(4);
    bee.setX(5);
    bee.setY(6);
    bee.setXSpeed(10);
    bee.setYSpeed(11);
    Image image(40, 30);
    image.fill(50, 50, 50);
    bee.draw(&image);
    image.write("/tmp/test_bee.png");
}

TEST (Bee, overlapsWith) {
    Parameters* parameters_ptr = new Parameters("../test/testfiles/generator_parameters.txt");
    Bee bee1(parameters_ptr);
    Bee bee2(parameters_ptr);
    Bee bee3(parameters_ptr);
    bee1.setRadius(5);
    bee2.setRadius(5);
    bee3.setRadius(5);
    bee1.setX(10);
    bee1.setY(20);
    bee2.setX(15);
    bee2.setY(15);
    bee3.setX(30);
    bee3.setX(30);
    ASSERT_EQ(bee1.overlapsWith(&bee2), 1);
    ASSERT_EQ(bee1.overlapsWith(&bee3), 0);
}
