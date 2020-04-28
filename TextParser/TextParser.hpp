#ifndef TEXT_PARSER
#define TEXT_PARSER

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class TextParser {
    std::vector<std::string> _words;

    void changeBadSymToWhite(std::string &str) {
        for (char &c : str) {
            if (isalpha(c) || c == '\'')
                c = tolower(c);
            else
                c = ' ';
        }
    }

    void parseFormattedLine(std::string const &str) {
        std::string token;
        std::istringstream token_stream(str); 

        while (std::getline(token_stream, token, ' ')) {
            if (!token.empty()) {
                _words.push_back(token);
            }
        }
    }

public:
    bool parseText(std::string const &fileName) {
        std::ifstream file(fileName);
        std::string   line;

        _words.clear();

        if (file.is_open()) {
            while (getline(file, line, '\n')) {
                changeBadSymToWhite(line);
                parseFormattedLine(line);
            }
            file.close();
            return true;
        }
        return false;
    }

    std::vector<std::string> &vectorOfWords() {
        return _words;
    }
};

#endif