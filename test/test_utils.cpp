#include "../src/const.h"
#include "../src/utils.h"

TEST(utils, split) {
  std::string str;
  std::vector< std::string > words;


  str = "eins zwei drei";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ' '), words);

  str = " eins  zwei   drei ";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ' '), words);

  str = "eins,zwei,drei";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ','), words);
}

TEST(utils, split_equal) {
  std::string str;
  std::vector< std::string > words;

  str = "abcdef";
  words = {"abc", "def"};
  ASSERT_EQ(utils::split_equal(str, 3), words);

  str = "abcdef";
  words = {"ab", "cd", "ef"};
  ASSERT_EQ(utils::split_equal(str, 2), words);

  str = "abcdef";
  words = {"abcd", "ef"};
  ASSERT_EQ(utils::split_equal(str, 4), words);

  str = "";
  words = {};
  ASSERT_EQ(utils::split_equal(str, 4), words);
}

TEST(utils, remove_comment) {
  std::string line = "hallo du \% da \% huhu";
  ASSERT_EQ(utils::remove_comment(line), "hallo du ");
  line = "hallo du ";
  ASSERT_EQ(utils::remove_comment(line), "hallo du ");
}

TEST(utils, square) {
  ASSERT_FLOAT_EQ(utils::square(3.0), 9.0);
  ASSERT_FLOAT_EQ(utils::square(-4.0), 16.0);
}

TEST(utils, float_equal) {
  ASSERT_TRUE(utils::float_equal(1.2345, 1.2345));
  ASSERT_FALSE(utils::float_equal(1.2345, 1.2346));
  ASSERT_TRUE(utils::float_equal(1.0, 1.0));
}

TEST( utils, inc_ending_number ) {
  ASSERT_EQ(
    utils::inc_ending_number("bla_1"),
    "bla_2"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla_9"),
    "bla_10"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla_100"),
    "bla_101"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla1"),
    "bla2"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla_blub99"),
    "bla_blub100"
  );
  
}

TEST ( utils, vector_str_to_int ) {
  std::vector < std::string > v {"1", "2", "345"};
  std::vector < int > result {1, 2, 345};
  ASSERT_EQ(utils::vector_str_to_int(v), result);
}
