#ifndef SEQUENCE_H
#define SEQUENCE_H

template <typename T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    virtual std::vector<T> Stream() = 0;
    virtual bool ISet(T item) = 0;
    virtual ~Sequence() {}
};

#endif //SEQUENCE_H