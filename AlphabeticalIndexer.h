#ifndef ALPHABETICALINDEXER_H
#define ALPHABETICALINDEXER_H

#include <map>
#include <string>
#include <sstream>
#include "ISetAlphabet.h"

class AlphabeticalIndexer {
public:
    AlphabeticalIndexer(int pageSize, bool isAuto) : pageSize(pageSize), isAuto(isAuto) {}

    std::map<std::string, ISet*> createIndex(const std::string& text) {
        std::map<std::string, ISet*> index;

        std::istringstream iss(text);
        std::string word;
        int page = 1;
        int pageWordCount = 0;
        while (iss >> word) {
            if (index.find(word) == index.end()) {
                index[word] = new MySet();
            }

            if (pageWordCount + 1 > this->pageSize) {
                page++;
                pageWordCount = 0;
            }

            index[word]->insert(std::to_string(page));

            pageWordCount++;
        }

        return index;
    }

private:
    int pageSize;
    bool isAuto;
};

#endif //ALPHABETICALINDEXER_H