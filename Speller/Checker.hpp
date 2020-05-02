#ifndef CHECKER
#define CHECKER

#include "TextParser.hpp"
#include "IDictionary.hpp"

#include "VectorDictionary.hpp"
#include "BinTreeDictionary.hpp"
#include "StdHashTableDictionary.hpp"
#include "MyHashTableDictionary.hpp"
#include "TrieDictionary.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>

#include <boost/filesystem.hpp>

#define PATH_TO_TEXTS "./texts"
#define PATH_TO_DICTIONARY "./dictionary.txt"
#define BAD_WORDS_DIR "./BadWords"
#define BAD_WORD_PREFIX "bad_"

typedef std::pair<std::string, std::vector<std::string> > text_t;

typedef struct {
    std::string type;
    size_t timeForFill;
    size_t timeForCheck;
    size_t amountCheckedWords;
    size_t amountBadWords;
} results_t;

class Checker {
    size_t _count_of_words;
    std::vector<text_t> _texts;
    std::set<std::string> _dict_words;
    std::vector<results_t> _results;

    void fillDictionary(IDictionary *dictionary, results_t *res) {
        auto start = std::chrono::steady_clock::now();

        for (std::string const &word : _dict_words) {
            dictionary->add(word);
        }
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        res->timeForFill = duration.count();
    }

    void writeWordsToFile(std::vector<std::string> const &badWords, 
                          std::string const &path_to_file,
                          std::string const &dir_name) {
        size_t found = path_to_file.find_last_of("/");
        std::string bad_words_file = path_to_file.substr(found + 1);

        boost::filesystem::path dir(std::string(BAD_WORDS_DIR) + "/" + dir_name);
        if(!(boost::filesystem::exists(dir))) {
            boost::filesystem::create_directory(dir);
        }

        std::ofstream file(dir.string() + "/" + BAD_WORD_PREFIX + bad_words_file);

        if (file.is_open()) {
            for (std::string const &word : badWords) {
                file << word << std::endl;
            }
            file.close();
        }
    }

    void checkText(IDictionary *dictionary, text_t const &text, results_t *res) {
        std::vector<std::string> badWords;

        auto start = std::chrono::steady_clock::now();

        for (std::string const &word : text.second) {
            if (!dictionary->check(word)) {
                badWords.push_back(word);
            }
        }

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        res->timeForCheck += duration.count();
        res->amountBadWords += badWords.size();

        writeWordsToFile(badWords, text.first, res->type);
    }

public:
    Checker() : _count_of_words(0) {
        TextParser parser;

        // Parse all texts for farther checking
        for (auto & p : boost::filesystem::directory_iterator(PATH_TO_TEXTS)) {
            if (!parser.parseText(p.path().string())) {
                std::cout << "Cannot open file \"" << p.path().string() << "\"";
                std::cout << std::endl;
                continue ;
            }

            std::vector<std::string> words(parser.moveParsedText());
            _count_of_words += words.size();
            _texts.push_back({p.path().string(), words});
        }

        // Parse words for dictionary
        if (!parser.parseText(PATH_TO_DICTIONARY)) {
            std::cout << "Cannot open dictionary \"" << PATH_TO_DICTIONARY << "\"" <<std::endl;
            return ;
        }

        for (std::string const &word : parser.moveParsedText()) {
            _dict_words.insert(word);
        }

        // Create directory for bad words
        boost::filesystem::path dir(BAD_WORDS_DIR);
        if(!(boost::filesystem::exists(dir))) {
            boost::filesystem::create_directory(dir);
        }
    }

    void check(IDictionary *dictionary) {
        results_t res;

        bzero(&res, sizeof(res));

        res.type = dictionary->getNameOfStructure();
        fillDictionary(dictionary, &res);
        
        for (text_t const &text : _texts) {
            checkText(dictionary, text, &res);
        }
        res.amountCheckedWords = _count_of_words;
        _results.push_back(res);
    }

    void printResults() const {
        size_t type_field_len = 0;
        size_t timeForFill_field_len = 0;
        size_t timeForCheck_field_len = 0;
        size_t amountCheckedWords_field_len = 0;
        size_t amountBadWords_field_len = 0;

        size_t line_len = 0;
        for (results_t const &res : _results) {
            type_field_len = std::max(type_field_len, res.type.size());
            timeForFill_field_len = std::max(timeForFill_field_len, std::to_string(res.timeForFill).size());
            timeForCheck_field_len = std::max(timeForCheck_field_len, std::to_string(res.timeForCheck).size());
            amountCheckedWords_field_len = std::max(amountCheckedWords_field_len, std::to_string(res.amountCheckedWords).size());
            amountBadWords_field_len = std::max(amountBadWords_field_len, std::to_string(res.amountBadWords).size());
        }
        line_len += 16 + type_field_len + timeForFill_field_len + timeForCheck_field_len + amountCheckedWords_field_len + amountBadWords_field_len;

        for (size_t i = 0; i < line_len; i++) {
            if (i == 0)
                std::cout << "┏";
            else if (i == line_len - 1)
                std::cout << "┓";
            else
                std::cout << "━";
        }
        std::cout << std::endl;

        for (results_t const &res : _results) {
            std::cout << "┃ " << std::setw (type_field_len) << std::left << res.type << " ┃ ";
            std::cout << std::setw (timeForFill_field_len) << std::right << res.timeForFill << " ┃ ";
            std::cout << std::setw (timeForCheck_field_len) << std::right << res.timeForCheck << " ┃ ";
            std::cout << std::setw (amountCheckedWords_field_len) << std::right << res.amountCheckedWords << " ┃ ";
            std::cout << std::setw (amountBadWords_field_len) << std::right << res.amountBadWords << " ┃" << std::endl;
        }

        for (size_t i = 0; i < line_len; i++) {
            if (i == 0)
                std::cout << "┗";
            else if (i == line_len - 1)
                std::cout << "┛";
            else
                std::cout << "━";
        }
        std::cout << std::endl;
    }
};

#endif