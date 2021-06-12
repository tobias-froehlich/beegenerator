#include "../src/Parameters.h"

TEST ( Parameters, create_and_delete ) {
  Parameters* parameters;
  parameters = new Parameters();
  delete parameters;
}

TEST ( Parameters, read_line_and_name_occurs ) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_FALSE(parameters->name_occurs("hallo"));
  parameters->read_line(" \% comment");
  ASSERT_FALSE(parameters->name_occurs("hallo"));
  parameters->read_line("hallo du da \% comment");
  ASSERT_TRUE(parameters->name_occurs("hallo"));
  ASSERT_THROW(
    parameters->read_line("hallo dibi dub dub"),
    std::invalid_argument
  );

  delete parameters;
}

TEST ( Parameters, get_strings) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_THROW(
    parameters->get_strings("Eins"),
    std::invalid_argument
  );
  parameters->read_line("Zwei dup di");
  ASSERT_THROW(
    parameters->get_strings("Eins"),
    std::invalid_argument
  );
  std::vector < std::string > values{"dup", "di"};
  ASSERT_EQ(
    parameters->get_strings("Zwei"),
    values
  );
  delete parameters;
}

TEST ( Parameters, get_ints) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_THROW(
    parameters->get_ints("Eins"),
    std::invalid_argument
  );
  parameters->read_line("Eins dup di");
  ASSERT_THROW(
    parameters->get_ints("Eins"),
    std::invalid_argument
  );
  parameters->read_line("Zwei 4 5");
  std::vector < int > values{4, 5};
  ASSERT_EQ(
    parameters->get_ints("Zwei"),
    values
  );
  delete parameters;
}

TEST ( Parameters, get_floats) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_THROW(
    parameters->get_floats("Eins"),
    std::invalid_argument
  );
  parameters->read_line("Eins dup di");
  ASSERT_THROW(
    parameters->get_floats("Eins"),
    std::invalid_argument
  );
  parameters->read_line("Zwei 4.5 5.3");
  ASSERT_EQ(
    parameters->get_floats("Zwei").size(),
    2
  );
  ASSERT_FLOAT_EQ(
    parameters->get_floats("Zwei")[0],
    4.5
  );
  ASSERT_FLOAT_EQ(
    parameters->get_floats("Zwei")[1],
    5.3
  );
  delete parameters;
}


TEST ( Parameters, get_string ) {
    Parameters* parameters;
    parameters = new Parameters();
    parameters->read_line("Zwei dup di");
    ASSERT_THROW(
        parameters->get_string("Zwei"),
        std::invalid_argument
    );
    parameters->read_line("Drei dup");
    ASSERT_EQ(
        parameters->get_string("Drei"),
        "dup"
    );
}

TEST ( Parameters, get_int ) {
    Parameters* parameters;
    parameters = new Parameters();
    parameters->read_line("Zwei dup di");
    ASSERT_THROW(
        parameters->get_int("Zwei"),
        std::invalid_argument
    );
    parameters->read_line("Drei dup");
    ASSERT_THROW(
        parameters->get_int("Drei"),
        std::invalid_argument
    );
    parameters->read_line("Eins 2 3");
    ASSERT_THROW(
        parameters->get_int("Eins"),
        std::invalid_argument
    );  
    parameters->read_line("Vier 3");
    ASSERT_EQ(
        parameters->get_int("Vier"),
        3
    );
}

TEST ( Parameters, get_float ) {
    Parameters* parameters;
    parameters = new Parameters();
    parameters->read_line("Zwei dup di");
    ASSERT_THROW(
        parameters->get_float("Zwei"),
        std::invalid_argument
    );
    parameters->read_line("Drei dup");
    ASSERT_THROW(
        parameters->get_float("Drei"),
        std::invalid_argument
    );
    parameters->read_line("Eins 2.5 3.2");
    ASSERT_THROW(
        parameters->get_float("Eins"),
        std::invalid_argument
    );  
    parameters->read_line("Vier 3.5");
    ASSERT_FLOAT_EQ(
        parameters->get_float("Vier"),
        3.5
    );
}

TEST (Parameters, read_file) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_THROW(
    parameters->read_file("notexisting_file.txt"),
    std::invalid_argument
  );
  ASSERT_THROW(
    parameters->read_file(
      "../test/testfiles/parameters1.txt"
    ),
    std::invalid_argument
  );
  parameters->read_file(
    "../test/testfiles/parameters2.txt"
  );
  std::vector< std::string > output {"du", "da"};
  ASSERT_EQ(
    parameters->get_strings("hallo"),
    output
  );
  delete parameters;
}
