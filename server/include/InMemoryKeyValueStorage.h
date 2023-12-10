#include <iostream>
#include <unordered_map>
#include <string>
#include <mutex>

class InMemoryKeyValueStorage
{
public:

    void put(const std::string& key, const std::string& value);

    bool get(const std::string& key, std::string& value);

 private:
    std::unordered_map<std::string, std::string> m_data;  

    std::mutex m_dataAccessMutex;
};