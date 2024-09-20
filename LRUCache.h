#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <list>
#include <unordered_map>
#include <chrono>
#include <iostream>

template <typename Key, typename Value>
class LRUCache {
private:
    std::list<std::pair<Key, Value>> itemList;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cache;
    size_t cacheSize;

public:
    LRUCache(size_t size) : cacheSize(size) {}

    void Put(const Key& key, const Value& value) {
        if (cache.find(key) != cache.end()) {
            itemList.erase(cache[key]);
        } else if (itemList.size() >= cacheSize) {
            cache.erase(itemList.back().first);
            itemList.pop_back();
        }
        itemList.push_front({key, value});
        cache[key] = itemList.begin();
    }

    Value Get(const Key& key) {
        if (cache.find(key) == cache.end()) {
            throw std::out_of_range("No such key in cache");
        }
        itemList.splice(itemList.begin(), itemList, cache[key]);
        return cache[key]->second;
    }

    Value GetWithTimeMeasurement(const Key& key) {
        auto start = std::chrono::high_resolution_clock::now();

        Value value = Get(key);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken to access data: " << duration.count() << " microseconds" << std::endl;

        return value;
    }

    std::list<std::pair<Key, Value>> GetAll() {
        return itemList;
    }

    bool Contains(const Key& key) {
        return cache.find(key) != cache.end();
    }

    std::list<std::pair<Key, Value>> Stream() {
        return GetAll();
    }
};

#endif //LRUCACHE_H