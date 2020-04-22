
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

using namespace boost::filesystem;
namespace bp = boost::process;

class Calculator {

    bp::opstream in;
    bp::ipstream out;
    bp::child c;

public:

    Calculator(std::string const &path) {
        c = bp::child(path, bp::std_out > out, bp::std_in < in);
    }

    ~Calculator() { c.terminate(); }

    std::string getResult(std::string const &expr) {

        std::string line;

        in << expr << std::endl;
        
        (out && std::getline(out, line, '\n'));

        return line;
    }
};