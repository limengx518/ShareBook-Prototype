#ifndef CACHE_H
#define CACHE_H

#include <sw/redis++/redis++.h>
#include "jotting.h"
#include "material.h"

class Cache
{
public:
    Cache();
    //数据到底以怎样的方式在redis中存储，hash
    std::unordered_map<std::string,std::string> inCache(std::string  key);
    void storeObject(std::string key,std::unordered_map<std::string,std::string> object);
    ~Cache();
private:
    sw::redis::Redis* m_redis;
};

#endif // CACHE_H
