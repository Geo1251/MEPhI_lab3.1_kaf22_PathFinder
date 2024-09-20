#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <cassert>
#include "SmartPointerException.h"

template <typename T>
class SmartPointer {
private:
    T* ptr;
    unsigned* count;

public:

    SmartPointer(T* p = 0) : ptr(p), count(p ? new unsigned(1) : 0) {
        if (ptr == nullptr) {
            throw SmartPointerException("Error: ptr is nullptr");
        }
        if (count == nullptr) {
            throw SmartPointerException("Error: count is nullptr");
        }
        if (*count != 1) {
            throw SmartPointerException("Error: count is not 1");
        }
    }

    SmartPointer(const SmartPointer<T>& sp) : ptr(sp.ptr), count(sp.count) {
        ++(*count);
    }

    SmartPointer<T>& operator=(const SmartPointer<T>& sp) {
        if (this != &sp) {
            if (--(*count) == 0) {
                delete ptr;
                delete count;
            }
            ptr = sp.ptr;
            count = sp.count;
            ++(*count);
        }
        return *this;
    }

    bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }

    bool operator==(std::nullptr_t) const {
        return ptr == nullptr;
    }

    ~SmartPointer() {
        if (count && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

    void reset(T* p = 0) {
        if (count && --(*count) == 0) {
            delete ptr;
            delete count;
        }
        ptr = p;
        count = p ? new unsigned(1) : 0;
    }

    T* get() { return ptr; }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }
};

#endif // SMARTPOINTER_H
