#include "../../src/iterator/null_iterator.h"

class NullIteratorTest : public ::testing::Test
{
protected:
    Iterator* it;

    void SetUp() override
    {
        it = new NullIterator();
    }

    void TearDown() override
    {
        delete it;
    }
};

TEST_F(NullIteratorTest, FirstShouldThrowException)
{
    ASSERT_ANY_THROW(it->first());
}

TEST_F(NullIteratorTest, CurrentShouldThrowException)
{
    ASSERT_ANY_THROW(it->currentItem());
}

TEST_F(NullIteratorTest, NextShouldThrowException)
{
    ASSERT_ANY_THROW(it->next());
}

TEST_F(NullIteratorTest, IsDoneShouldBeTrue)
{
    ASSERT_TRUE(it->isDone());
}