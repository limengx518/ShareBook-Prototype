#include "cache.h"
#include <iostream>
using namespace sw::redis;

//redis只能移动不能复制
Cache::Cache()
{
    m_redis=new sw::redis::Redis("tcp://127.0.0.1:6379");
    std::cout<<"relate the redis server"<<std::endl;

    auto val = m_redis->command<OptionalString>("CONFIG","SET","maxmemory","3GB");
    if(val){
        std::cout<<*val<<std::endl;
    }


    auto policy = m_redis->command<OptionalString>("CONFIG","SET","maxmemory-policy","allkeys-lru");
    if(policy){
        std::cout<<*policy<<std::endl;
    }
}


std::unordered_map<std::string,std::string> Cache::inCache(std::string key)
{
    // std::unordered_map<std::string, std::string> to Redis HASH.
    std::unordered_map<std::string, std::string> m;
    m_redis->hgetall(key, std::inserter(m, m.begin()));
    return m;
}

void Cache::storeObject(std::string key, std::unordered_map<std::string, std::string> object)
{
    m_redis->hmset(key, object.begin(), object.end());
}

void Cache::remove(std::string key, std::string field)
{
    auto val = m_redis->command<OptionalString>("HDEL",key,field);
    if(val){
        std::cout<<*val<<std::endl;
    }
}


Cache::~Cache()
{
    delete m_redis;
}
