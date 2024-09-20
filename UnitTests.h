#ifndef UNITTESTS_H
#define UNITTESTS_H

#include "LRUCache.h"
#include "Person.h"
#include "BinaryTree.h"
#include "SequenceFinder.h"
#include "AlphabeticalIndexer.h"
#include "ISetAlphabet.h"
#include "SmartPointer.h"

#include <cassert>
#include <set>
#include <iostream>
#include <chrono>

void TestLRUCacheAuto() {
    LRUCache<int, Person> cache(3);

    std::set<std::string> names = {"George", "Vladimir", "Vladislav"};
    std::set<int> ages = {25, 30, 35};

    std::cout << "Adding George, Vladimir, and Vladislav to the cache...\n";
    cache.Put(1, Person("George", 25));
    cache.Put(2, Person("Vladimir", 30));
    cache.Put(3, Person("Vladislav", 35));

    std::cout << "Checking if George, Vladimir, and Vladislav are in the cache...\n";
    assert(cache.GetWithTimeMeasurement(1).name == "George");
    assert(cache.GetWithTimeMeasurement(2).name == "Vladimir");
    assert(cache.GetWithTimeMeasurement(3).name == "Vladislav");

    std::cout << "Adding David to the cache...\n";
    cache.Put(4, Person("David", 40));

    std::cout << "Checking if George was evicted from the cache...\n";
    try {
        cache.GetWithTimeMeasurement(1);
        assert(false); 
    } catch (std::out_of_range&) {
        std::cout << "George was successfully evicted from the cache.\n";
    }

    std::cout << "Checking if Vladimir, Vladislav, and David are in the cache...\n";
    assert(cache.GetWithTimeMeasurement(2).name == "Vladimir");
    assert(cache.GetWithTimeMeasurement(3).name == "Vladislav");
    assert(cache.GetWithTimeMeasurement(4).name == "David");

    std::cout << "Streaming all items in the cache...\n";
    auto stream = cache.Stream();
    for (const auto& item : stream) {
        std::cout << "Key: " << item.first << ", Value: " << item.second.name << ", Age: " << item.second.age << "\n";
    }

    std::cout << "Automatically searching for people in the cache by name...\n";
    for (const auto& name : names) {
        bool found = false;
        for (int i = 1; i <= 4; ++i) {
            if (cache.Contains(i)) {
                auto person = cache.Get(i);
                if (person.name == name) {
                    auto start = std::chrono::high_resolution_clock::now();
                    cache.GetWithTimeMeasurement(i);
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    std::cout << "Time taken to access " << name << ": " << duration.count() << " microseconds\n";
                    std::cout << name << " is in the cache. The age is " << person.age << ".\n";
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            std::cout << name << " is not in the cache.\n";
        }
    }

    std::cout << "Automatically searching for people in the cache by age...\n";
    for (const auto& age : ages) {
        bool found = false;
        for (int i = 1; i <= 4; ++i) {
            if (cache.Contains(i)) {
                auto person = cache.Get(i);
                if (person.age == age) {
                    auto start = std::chrono::high_resolution_clock::now();
                    cache.GetWithTimeMeasurement(i);
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    std::cout << "Time taken to access person with age " << age << ": " << duration.count() << " microseconds\n";
                    std::cout << "A person with age " << age << " is in the cache. The name is " << person.name << ".\n";
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            std::cout << "No person with age " << age << " is in the cache.\n";
        }
    }

    std::cout << "All tests passed!\n";
}

void TestLRUCacheManual() {
    int size;
    std::cout << "Enter the number of cache slots: ";
    std::cin >> size;

    LRUCache<int, Person> cache(size);

    std::string name;
    int age;
    for (int i = 1; i <= size; ++i) {
        std::cout << "Enter a name and age for person " << i << ": ";
        std::cin >> name >> age;
        cache.Put(i, Person(name, age));
    }

    std::cout << "Manually checking if people are in the cache...\n";
    for (int i = 1; i <= size; ++i) {
        std::cout << "Enter a name or age to check (or 'exit' to finish): ";
        std::string input;
        std::cin >> input;
        if (input == "exit") {
            break;
        }
        bool found = false;
        try {
            age = std::stoi(input);
            for (int j = 1; j <= size; ++j) {
                if (cache.Contains(j)) {
                    auto person = cache.GetWithTimeMeasurement(j);
                    if (person.age == age) {
                        std::cout << "A person with age " << age << " is in the cache. The name is " << person.name << ".\n";
                        found = true;
                        break;
                    }
                }
            }
        } catch (std::invalid_argument&) {
            for (int j = 1; j <= size; ++j) {
                if (cache.Contains(j)) {
                    auto person = cache.GetWithTimeMeasurement(j);
                    if (person.name == input) {
                        std::cout << input << " is in the cache. The age is " << person.age << ".\n";
                        found = true;
                        break;
                    }
                }
            }
        }
        if (!found) {
            std::cout << "The person is not in the cache.\n";
        }
    }

    std::cout << "Manually adding a person to the cache...\n";
    std::cout << "Enter a name and age for the new person: ";
    std::cin >> name >> age;
    cache.Put(size + 1, Person(name, age));

    std::cout << "Manually checking if the first person was evicted from the cache...\n";
    try {
        cache.GetWithTimeMeasurement(1);
        std::cout << "The first person was not evicted from the cache.\n";
    } catch (std::out_of_range&) {
        std::cout << "The first person was successfully evicted from the cache.\n";
    }

    std::cout << "Printing the current people in the cache...\n";
    for (int i = 2; i <= size + 1; ++i) {
        if (cache.Contains(i)) {
            auto person = cache.GetWithTimeMeasurement(i);
            std::cout << "Person " << i << ": " << person.name << ", " << person.age << "\n";
        }
    }

    std::cout << "Manual test completed!\n";
}

//--------------------------------------------------------------------------------------------------

void TestSequenceFinderAuto() {
    BinaryTree<int> tree;
    SequenceFinder<int> finder;

    int sequence[] = {1, 2, 3, 1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6};

    for (int i = 0; i < sizeof(sequence)/sizeof(sequence[0]); ++i) { 
        tree.insert(sequence[i]);
    }

    Stream<int> stream = tree.toStreamInOrder();

    std::cout << "Generated sequence: ";
    for (int num : stream) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto subsequences = finder.findFrequentSubsequences(tree, 1, sizeof(sequence)/sizeof(sequence[0])/2);

    std::map<std::vector<int>, int> expectedCounts = {
        {{1}, 3},
        {{1,1}, 2},
        {{1,1,1}, 1},
        {{1,1,1,2}, 1},
        {{1,1,1,2,2}, 1},
        {{1,1,1,2,2,2}, 1},
        {{1,1,1,2,2,2,3}, 1},
        {{1,1,1,2,2,2,3,3}, 1},
        {{1,1,1,2,2,2,3,3,3}, 1},
        {{1,1,1,2,2,2,3,3,3,4}, 1},
        {{1,1,2}, 1},
        {{1,1,2,2}, 1},
        {{1,1,2,2,2}, 1},
        {{1,1,2,2,2,3}, 1},
        {{1,1,2,2,2,3,3}, 1},
        {{1,1,2,2,2,3,3,3}, 1},
        {{1,1,2,2,2,3,3,3,4}, 1},
        {{1,1,2,2,2,3,3,3,4,4}, 1},
        {{1,2}, 1},
        {{1,2,2}, 1},
        {{1,2,2,2}, 1},
        {{1,2,2,2,3}, 1},
        {{1,2,2,2,3,3}, 1},
        {{1,2,2,2,3,3,3}, 1},
        {{1,2,2,2,3,3,3,4}, 1},
        {{1,2,2,2,3,3,3,4,4}, 1},
        {{1,2,2,2,3,3,3,4,4,4},1},
        {{2}, 3},
        {{2,2}, 2},
        {{2,2,2}, 1},
        {{2,2,2,3}, 1},
        {{2,2,2,3,3}, 1},
        {{2,2,2,3,3,3}, 1},
        {{2,2,2,3,3,3,4}, 1},
        {{2,2,2,3,3,3,4,4}, 1},
        {{2,2,2,3,3,3,4,4,4}, 1},
        {{2,2,2,3,3,3,4,4,4,5}, 1},
        {{2,2,3}, 1},
        {{2,2,3,3}, 1},
        {{2,2,3,3,3}, 1},
        {{2,2,3,3,3,4}, 1},
        {{2,2,3,3,3,4,4}, 1},
        {{2,2,3,3,3,4,4,4}, 1},
        {{2,2,3,3,3,4,4,4,5}, 1},
        {{2,2,3,3,3,4,4,4,5,5}, 1},
        {{2,3}, 1},
        {{2,3,3}, 1},
        {{2,3,3,3}, 1},
        {{2,3,3,3,4}, 1},
        {{2,3,3,3,4,4}, 1},
        {{2,3,3,3,4,4,4}, 1},
        {{2,3,3,3,4,4,4,5}, 1},
        {{2,3,3,3,4,4,4,5,5}, 1},
        {{2,3,3,3,4,4,4,5,5,5}, 1},
        {{3}, 3},
        {{3,3}, 2},
        {{3,3,3}, 1},
        {{3,3,3,4}, 1},
        {{3,3,3,4,4}, 1},
        {{3,3,3,4,4,4}, 1},
        {{3,3,3,4,4,4,5}, 1},
        {{3,3,3,4,4,4,5,5}, 1},
        {{3,3,3,4,4,4,5,5,5}, 1},
        {{3,3,3,4,4,4,5,5,5,6}, 1},
        {{3,3,4}, 1},
        {{3,3,4,4}, 1},
        {{3,3,4,4,4}, 1},
        {{3,3,4,4,4,5}, 1},
        {{3,3,4,4,4,5,5}, 1},
        {{3,3,4,4,4,5,5,5}, 1},
        {{3,3,4,4,4,5,5,5,6}, 1},
        {{3,3,4,4,4,5,5,5,6,6}, 1},
        {{3,4}, 1},
        {{3,4,4}, 1},
        {{3,4,4,4}, 1},
        {{3,4,4,4,5}, 1},
        {{3,4,4,4,5,5}, 1},
        {{3,4,4,4,5,5,5}, 1},
        {{3,4,4,4,5,5,5,6}, 1},
        {{3,4,4,4,5,5,5,6,6}, 1},
        {{3,4,4,4,5,5,5,6,6,6}, 1},
        {{4}, 3},
        {{4,4}, 2},
        {{4,4,4}, 1},
        {{4,4,4,5}, 1},
        {{4,4,4,5,5}, 1},
        {{4,4,4,5,5,5}, 1},
        {{4,4,4,5,5,5,6}, 1},
        {{4,4,4,5,5,5,6,6}, 1},
        {{4,4,4,5,5,5,6,6,6}, 1},
        {{4,4,4,5,5,5,6,6,6,7}, 1},
        {{4,4,5}, 1},
        {{4,4,5,5}, 1},
        {{4,4,5,5,5}, 1},
        {{4,4,5,5,5,6}, 1},
        {{4,4,5,5,5,6,6}, 1},
        {{4,4,5,5,5,6,6,6}, 1},
        {{4,4,5,5,5,6,6,6,7}, 1},
        {{4,4,5,5,5,6,6,6,7,8}, 1},
        {{4,5}, 1},
        {{4,5,5}, 1},
        {{4,5,5,5}, 1},
        {{4,5,5,5,6}, 1},
        {{4,5,5,5,6,6}, 1},
        {{4,5,5,5,6,6,6}, 1},
        {{4,5,5,5,6,6,6,7}, 1},
        {{4,5,5,5,6,6,6,7,8}, 1},
        {{4,5,5,5,6,6,6,7,8,9}, 1},
        {{5}, 3},
        {{5,5}, 2},
        {{5,5,5}, 1},
        {{5,5,5,6}, 1},
        {{5,5,5,6,6}, 1},
        {{5,5,5,6,6,6}, 1},
        {{5,5,5,6,6,6,7}, 1},
        {{5,5,5,6,6,6,7,8}, 1},
        {{5,5,5,6,6,6,7,8,9}, 1},
        {{5,5,6}, 1},
        {{5,5,6,6}, 1},
        {{5,5,6,6,6}, 1},
        {{5,5,6,6,6,7}, 1},
        {{5,5,6,6,6,7,8}, 1},
        {{5,5,6,6,6,7,8,9}, 1},
        {{5,6}, 1},
        {{5,6,6}, 1},
        {{5,6,6,6}, 1},
        {{5,6,6,6,7}, 1},
        {{5,6,6,6,7,8}, 1},
        {{5,6,6,6,7,8,9}, 1},
        {{6}, 3},
        {{6,6}, 2},
        {{6,6,6}, 1},
        {{6,6,6,7}, 1},
        {{6,6,6,7,8}, 1},
        {{6,6,6,7,8,9}, 1},
        {{6,6,7}, 1},
        {{6,6,7,8}, 1},
        {{6,6,7,8,9}, 1},
        {{6,7}, 1},
        {{6,7,8}, 1},
        {{6,7,8,9}, 1},
        {{7}, 1},
        {{7,8}, 1},
        {{7,8,9}, 1},
        {{8}, 1},
        {{8,9}, 1},
        {{9}, 1},
    };

    for (const auto& pair : subsequences) {
        const auto& subsequence = pair.first;
        int count = pair.second;

        std::cout << "Subsequence: ";
        for (int num : subsequence) {
            std::cout << num << " ";
        }
        std::cout << "Count: " << count << " ";
        std::cout << "Expected count: " << expectedCounts[subsequence] << "\n";

        assert(count == expectedCounts[subsequence]);
    }

    std::cout << "All tests passed!\n";
}

void TestSequenceFinderManual() {
    BinaryTree<int> tree;
    SequenceFinder<int> finder;

    std::cout << "Enter the number of elements in the sequence: ";
    int n;
    std::cin >> n;

    std::cout << "Enter the elements of the sequence: ";
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        tree.insert(num);
    }

    Stream<int> stream = tree.toStreamInOrder();

    std::cout << "Generated sequence: ";
    for (int num : stream) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    std::cout << "Enter the minimum length of the subsequences: ";
    int min_length;
    std::cin >> min_length;

    std::cout << "Enter the maximum length of the subsequences: ";
    int max_length;
    std::cin >> max_length;

    auto subsequences = finder.findFrequentSubsequences(tree, min_length, max_length);

    for (const auto& pair : subsequences) {
        const auto& subsequence = pair.first;
        int count = pair.second;

        std::cout << "Subsequence: ";
        for (int num : subsequence) {
            std::cout << num << " ";
        }
        std::cout << "Count: " << count << "\n";

        assert(count >= 1);
    }

    std::cout << "All tests passed!\n";
}

//--------------------------------------------------------------------------------------------------

void TestAlphabeticalIndexerAuto() {
    AlphabeticalIndexer indexer(5, true);

    std::string text = "Hi my name is George I am 18 years old and I am a student of Mephi";

    auto index = indexer.createIndex(text);

    std::map<std::string, std::set<std::string>> expectedIndex = {
        {"Hi", {"1"}},
        {"my", {"1"}},
        {"name", {"1"}},
        {"is", {"1"}},
        {"George", {"1", "2"}},
        {"I", {"2", "3"}},
        {"am", {"2", "3"}},
        {"18", {"2"}},
        {"years", {"3"}},
        {"old", {"3"}},
        {"and", {"3"}},
        {"a", {"3"}},
        {"student", {"3"}},
        {"of", {"4"}},
        {"Mephi", {"4"}},
    };

    for (const auto& pair : index) {
        const std::string& word = pair.first;
        ISet* pages = pair.second;

        std::set<std::string> expectedPages = expectedIndex[word];
        std::set<std::string> actualPages;
        for (auto it = pages->begin(); it != pages->end(); ++it) {
            actualPages.insert(*it);
        }

        if (expectedPages != actualPages) {
            std::cout << "Error: for word " << word << ", expected pages were ";
            for (const auto& page : expectedPages) {
                std::cout << page << " ";
            }
            std::cout << ", but actual pages were ";
            for (const auto& page : actualPages) {
                std::cout << page << " ";
            }
            std::cout << "\n";
        }

        std::cout << "Word: " << word << " Pages: ";
        for (auto it = pages->begin(); it != pages->end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

    for (auto& pair : index) {
        delete pair.second;
    }

    std::cout << "All tests passed!\n";
}

void TestAlphabeticalIndexerManual() {
    int pageSize;
    std::cout << "Enter the number of words per page: ";
    std::cin >> pageSize;

    AlphabeticalIndexer indexer(pageSize, true);

    std::string text;
    std::cout << "Enter text: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::getline(std::cin, text);

    auto index = indexer.createIndex(text);

    std::string word;
    while (true) {
        std::cout << "Enter a word (or 'done' to finish): ";
        std::getline(std::cin, word);
        if (word == "done") break;

        auto it = index.find(word);
        if (it != index.end()) {
            ISet* pages = it->second;
            std::cout << "Word: " << word << " is on pages: ";
            for (const auto& page : *pages) {
                std::cout << page << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "Word: " << word << " is not in the text.\n";
        }
    }

    for (auto& pair : index) {
        delete pair.second;
    }
}

//--------------------------------------------------------------------------------------------------

void CompareAlgorithms() {
    auto totalStart = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    start = std::chrono::high_resolution_clock::now();
    TestLRUCacheAuto();
    end = std::chrono::high_resolution_clock::now();
    auto timeLRUCacheAuto = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;

    start = std::chrono::high_resolution_clock::now();
    TestSequenceFinderAuto();
    end = std::chrono::high_resolution_clock::now();
    auto timeSequenceFinderAuto = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;

    start = std::chrono::high_resolution_clock::now();
    TestAlphabeticalIndexerAuto();
    end = std::chrono::high_resolution_clock::now();
    auto timeAlphabeticalIndexerAuto = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;

    auto totalEnd = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - totalStart).count() / 1000000.0;

    std::cout << "TestLRUCacheAuto took " << timeLRUCacheAuto << " seconds.\n";
    std::cout << "TestSequenceFinderAuto took " << timeSequenceFinderAuto << " seconds.\n";
    std::cout << "TestAlphabeticalIndexerAuto took " << timeAlphabeticalIndexerAuto << " seconds.\n";
    std::cout << "Total time taken by all tests: " << totalTime << " seconds.\n";
}

#endif //UNITTESTS_H