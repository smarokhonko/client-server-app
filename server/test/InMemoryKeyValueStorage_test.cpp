#include "gtest/gtest.h"

#include "InMemoryKeyValueStorage.h"

TEST(InMemoryKeyValueStorageTest, PutAndGet)
{
    InMemoryKeyValueStorage storage;

    // Test put and get with a single key-value pair
    storage.put("key1", "value1");
    
    std::string retrievedValue;
    bool keyFound = storage.get("key1", retrievedValue);

    ASSERT_TRUE(keyFound);
    EXPECT_EQ(retrievedValue, "value1");

    // Test put and get with another key-value pair
    storage.put("key2", "value2");

    keyFound = storage.get("key2", retrievedValue);

    ASSERT_TRUE(keyFound);
    EXPECT_EQ(retrievedValue, "value2");
}
