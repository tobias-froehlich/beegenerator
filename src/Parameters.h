#ifndef PARAMETERS_H_
#define PARAMETERS_H_

class Parameters {
  private:
    std::vector< std::string > zNames {};
    std::vector< std::vector < std::string > >
      zValues {};
  public:
    Parameters();
    ~Parameters();
    void init();
    void read_line(std::string line);
    int name_occurs(std::string name);
    std::vector < std::string > get_strings(
      std::string name
    );
    std::vector < int > get_ints(std::string name);
    std::vector < double > get_floats(
      std::string name);
    std::string get_string(std::string name);
    int get_int(std::string name);
    double get_float(std::string name);
    void read_file(std::string filename);
};

#endif
