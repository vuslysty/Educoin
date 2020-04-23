
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <iostream>

using namespace boost::filesystem;
namespace bp = boost::process;

class Calculator {
  bp::opstream _in;
  bp::ipstream _out;
  bp::child _child;

 public:
  Calculator(std::string const &path) {
    _child = bp::child(path, bp::std_out > _out, bp::std_in < _in);
  }

  ~Calculator() { _child.terminate(); }

  std::string getResult(std::string const &expr) {
    std::string line;

    _in << expr << std::endl;

    if (_out) {
      std::getline(_out, line, '\n');
    }
    return line;
  }
};