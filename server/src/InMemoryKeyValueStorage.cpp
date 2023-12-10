#include "InMemoryKeyValueStorage.h"

void InMemoryKeyValueStorage::put(const std::string& key, const std::string& value)
{
    std::lock_guard<std::mutex> lock(m_dataAccessMutex);

    m_data[key] = value;
}

bool InMemoryKeyValueStorage::get(const std::string& key, std::string& value)
{
    std::lock_guard<std::mutex> lock(m_dataAccessMutex);

    auto it = m_data.find(key);

    if (it != m_data.end())
    {
        value = it->second;

        return true;  // Key found
    }

    return false;  // Key not found
}