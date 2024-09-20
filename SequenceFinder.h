#ifndef SEQUENCE_FINDER_H
#define SEQUENCE_FINDER_H

#include <map>
#include <vector>
#include "BinaryTree.h"
#include "StreamTree.h"

template <typename T>
class SequenceFinder {
public:
    SequenceFinder() {}

    std::map<std::vector<T>, int> findFrequentSubsequences(BinaryTree<T>& tree, int lmin, int lmax) {
        Stream<T> stream = tree.toStreamInOrder();
        std::vector<T> sequence(stream.begin(), stream.end());
        std::map<std::vector<T>, int> subsequences;

        for (int i = 0; i < sequence.size(); ++i) {
            for (int len = lmin; len <= lmax && i + len - 1 < sequence.size(); ++len) {
                std::vector<T> subsequence(sequence.begin() + i, sequence.begin() + i + len);
                subsequences[subsequence]++;
            }
        }

        return subsequences;
    }
};

#endif // SEQUENCE_FINDER_H