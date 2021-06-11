#include "../src/Image.h"

TEST (Image, create_and_delete ) {
    Image* image = new Image(5, 6);
    ASSERT_EQ(image->getWidth(), 5);
    ASSERT_EQ(image->getHeight(), 6);
    delete image;
}


TEST (Image, everything) {
    Image image(40, 30);
    image.fill(50, 100, 70);
    image.setPixel(10, 5, 2, 255);
    image.setPixel(11, 5, 180, 190, 200);
    ASSERT_EQ(image.getPixel(10, 5, 2), 255);
    ASSERT_EQ(image.getPixel(11, 5, 0), 180);
    ASSERT_EQ(image.getPixel(11, 5, 1), 190);
    ASSERT_EQ(image.getPixel(11, 5, 2), 200);
    image.write("/tmp/test.png");
}

