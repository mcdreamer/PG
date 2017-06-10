#include "CoreDataTests.h"
#include "gtest/gtest.h"

#include "PG/data/DataGrid.h"
#include "PG/data/Attributes.h"
#include "PG/data/EntityLoader.h"
#include "PG/data/EntityHandle.h"

using namespace PG;

//--------------------------------------------------------
TEST(CoreDataTests,testDataGrid)
{
    DataGrid<int> g(100, 100);
    
    auto v = g.at(4, 5);
    EXPECT_EQ(0, v);
    
    g.set(4, 5, 10);
    v = g.at(4, 5);
    EXPECT_EQ(10, v);
}

//--------------------------------------------------------
TEST(CoreDataTests,testAttributes)
{
    Attributes atts;
    
    atts.setAttributeInt("i", 123);
    atts.setAttributeBool("t", true);
    atts.setAttributeBool("f", false);
    atts.setAttributeString("s", "Hello");
    
    auto a1 = atts.getAttributeInt("i");
    auto a2 = atts.getAttributeBool("t");
    auto a3 = atts.getAttributeBool("f");
    auto a4 = atts.getAttributeString("s");
    
    ASSERT_TRUE(a1.is_initialized());
    ASSERT_TRUE(a2.is_initialized());
    ASSERT_TRUE(a3.is_initialized());
    ASSERT_TRUE(a4.is_initialized());
    
    EXPECT_EQ(123, *a1);
    EXPECT_TRUE(*a2);
    EXPECT_FALSE(*a3);
    EXPECT_EQ("Hello", *a4);
}

//--------------------------------------------------------
TEST(CoreDataTests,testEntityLoader)
{
    EntityLoader loader;
    
    auto entities = loader.loadEntityFile("testdata.json");
    ASSERT_EQ((size_t)4, entities.size());
    
    auto it = entities.begin();
    {
        ASSERT_TRUE(it->getAttributeString("stat").is_initialized());
        EXPECT_EQ("add1", *it->getAttributeString("stat"));
    }
    ++it;
    {
        ASSERT_TRUE(it->getAttributeString("stat").is_initialized());
        EXPECT_EQ("Hello", *it->getAttributeString("stat"));
    }
    ++it;
    {
        ASSERT_TRUE(it->getAttributeString("name").is_initialized());
        ASSERT_TRUE(it->getAttributeString("stat1").is_initialized());
        ASSERT_TRUE(it->getAttributeString("stat2").is_initialized());
        EXPECT_EQ("base", *it->getAttributeString("name"));
        EXPECT_EQ("123", *it->getAttributeString("stat1"));
        EXPECT_EQ("234", *it->getAttributeString("stat2"));
    }
    ++it;
    {
        ASSERT_TRUE(it->getAttributeString("name").is_initialized());
        ASSERT_TRUE(it->getAttributeString("stat1").is_initialized());
        ASSERT_TRUE(it->getAttributeString("stat2").is_initialized());
        EXPECT_EQ("inherited", *it->getAttributeString("name"));
        EXPECT_EQ("123", *it->getAttributeString("stat1"));
        EXPECT_EQ("345", *it->getAttributeString("stat2"));
        EXPECT_FALSE(it->hasAttribute("parent"));
    }
}

//--------------------------------------------------------
TEST(CoreDataTests,testEntityHandle)
{
    EntityHandle<int> handle;
    
    ASSERT_FALSE(handle.getEntity());
    handle.setEntity(123);
    ASSERT_TRUE(handle.getEntity());
    handle.clearEntity();
    ASSERT_FALSE(handle.getEntity());
}

//--------------------------------------------------------
TEST(CoreDataTests,testEntityHandleSwap)
{
    EntityHandle<int> handleOne;
    EntityHandle<int> handleTwo;
    
    handleOne.setEntity(123);
    ASSERT_TRUE(handleOne.getEntity());
    ASSERT_FALSE(handleTwo.getEntity());
    
    handleOne.swap(handleTwo);
    ASSERT_FALSE(handleOne.getEntity());
    ASSERT_TRUE(handleTwo.getEntity());
}
