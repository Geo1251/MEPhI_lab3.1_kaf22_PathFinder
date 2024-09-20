#ifndef STREAM_TREE_H
#define STREAM_TREE_H

#include <vector>

template <typename T>
class Stream {
private:
    std::vector<T> data;

public:
    Stream() {}

    void add(const T& value) {
        data.push_back(value);
    }

    typename std::vector<T>::iterator begin() {
        return data.begin();
    }

    typename std::vector<T>::iterator end() {
        return data.end();
    }
};

#endif // STREAM_TREE_H