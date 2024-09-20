#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "Sequence.h"
#include "SmartPointer.h"
#include <stdexcept>

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    SmartPointer<T[]> data;
    int length;
public:
    ArraySequence() : data(new T[0]), length(0) {}

    T GetFirst() const override {
        if (length == 0) throw std::out_of_range("Sequence is empty");
        return data.get()[0];
    }

    T GetLast() const override {
        if (length == 0) throw std::out_of_range("Sequence is empty");
        return data.get()[length - 1];
    }

    T Get(int index) const override {
        if (index < 0 || index >= length) throw std::out_of_range("Index is out of range");
        return data.get()[index];
    }

    int GetLength() const override {
        return length;
    }

    void Append(T item) override {
        T* newData = new T[length + 1];
        for (int i = 0; i < length; i++) {
            newData[i] = data.get()[i];
        }
        newData[length] = item;
        data.reset(newData);
        length++;
    }

    void Prepend(T item) override {
        T* newData = new T[length + 1];
        newData[0] = item;
        for (int i = 0; i < length; i++) {
            newData[i + 1] = data.get()[i];
        }
        data.reset(newData);
        length++;
    }

    void InsertAt(T item, int index) override {
        if (index < 0 || index > length) throw std::out_of_range("Index is out of range");
        T* newData = new T[length + 1];
        for (int i = 0; i < index; i++) {
            newData[i] = data.get()[i];
        }
        newData[index] = item;
        for (int i = index; i < length; i++) {
            newData[i + 1] = data.get()[i];
        }
        data.reset(newData);
        length++;
    }

    Sequence<T>* Concat(Sequence<T>* list) override {
        ArraySequence<T>* result = new ArraySequence<T>();
        for (int i = 0; i < length; i++) {
            result->Append(data.get()[i]);
        }
        for (int i = 0; i < list->GetLength(); i++) {
            result->Append(list->Get(i));
        }
        return result;
    }

    std::vector<T> Stream() {
        std::vector<T> stream;
        for (int i = 0; i < length; i++) {
            stream.push_back(data.get()[i]);
        }
        return stream;
    }

    bool ISet(T item) {
        for (int i = 0; i < length; i++) {
            if (data.get()[i] == item) {
                return true;
            }
        }
        return false;
    }
};

#endif //ARRAYSEQUENCE_H