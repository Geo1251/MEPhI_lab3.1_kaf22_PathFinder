#include <iostream>
#include "UnitTests.h"

int main() {
    while (true) {
        std::cout << "Choose test type:\n";
        std::cout << "1. Automatic\n";
        std::cout << "2. Manual\n";
        std::cout << "3. Comparison Test\n";
        std::cout << "4. Exit\n";

        int testType;
        std::cin >> testType;

        if (testType == 3) {
            std::cout << "Running comparison test...\n";
            CompareAlgorithms();
            std::cout << "Comparison test finished.\n";
            continue;
        } else

        if (testType == 4) {
            std::cout << "Exiting...\n";
            break;
        }

        if(testType != 1 && testType != 2 && testType != 3 && testType != 4) {
            std::cout << "Invalid test type.\n";
            continue;
        }

        std::cout << "Choose test:\n";
        std::cout << "1. Cache Test\n";
        std::cout << "2. Alphabetical Index Test\n";
        std::cout << "3. Most Frequent Subsequence Test\n";

        int test;
        std::cin >> test;

        switch (testType) {
            case 1:
                switch (test) {
                    case 1:
                        TestLRUCacheAuto();
                        break;
                    case 2:
                        TestAlphabeticalIndexerAuto();
                        break;
                    case 3:
                        TestSequenceFinderAuto();
                        break;
                    default:
                        std::cout << "Invalid test number.\n";
                        break;
                }
                break;
            case 2:
                switch (test) {
                    case 1:
                        TestLRUCacheManual();
                        break;
                    case 2:
                        TestAlphabeticalIndexerManual();
                        break;
                    case 3:
                        TestSequenceFinderManual();
                        break;
                    default:
                        std::cout << "Invalid test number.\n";
                        break;
                }
                break;

            default:
                std::cout << "Invalid test type.\n";
                break;
        }
    }

    return 0;
}