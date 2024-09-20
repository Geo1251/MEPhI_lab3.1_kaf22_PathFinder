#ifndef ISET_H
#define ISET_H

#include <string>
#include <set>
#include <vector>
#include <algorithm>

class ISet {
public:
    virtual ~ISet() {}

    virtual void insert(const std::string& element) = 0;

    virtual bool contains(const std::string& element) const = 0;

    virtual void erase(const std::string& element) = 0;

    virtual int size() const = 0;

    virtual bool empty() const = 0;

    virtual std::vector<std::string>::iterator begin() = 0;

    virtual std::vector<std::string>::iterator end() = 0;
};

class MySet : public ISet {
public:
    void insert(const std::string& element) override {
        if (!contains(element)) {
            data.push_back(element);
        }
    }

    bool contains(const std::string& element) const override {
        return std::find(data.begin(), data.end(), element) != data.end();
    }

    void erase(const std::string& element) override {
        data.erase(std::remove(data.begin(), data.end(), element), data.end());
    }

    int size() const override {
        return data.size();
    }

    bool empty() const override {
        return data.empty();
    }

    std::vector<std::string>::iterator begin() override {
        return data.begin();
    }

    std::vector<std::string>::iterator end() override {
        return data.end();
    }

private:
    std::vector<std::string> data;
};

#endif // ISET_H