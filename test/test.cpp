#include <iostream>
#include <queue>
#include <chrono>
#include <gtest/gtest.h>
#include "test_utils.cpp"
#include "test_Parameters.cpp"
#include "test_Generator.cpp"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
