
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <iostream>

using namespace boost::filesystem;
namespace bp = boost::process;

class SortTester {
  bp::opstream _in;
  bp::ipstream _out;
  bp::child _child;

 public:
  SortTester(std::string const &path) {
    _child = bp::child(path, bp::std_out > _out, bp::std_in < _in);
  }

  ~SortTester() { _child.terminate(); }

  void fillArray(std::string const &array) {
    _in << array << std::endl;
  }

  std::string getNextLine() {
    std::string line;

    if (_out) {
      std::getline(_out, line, '\n');
    }
    return line;
  }

  
};