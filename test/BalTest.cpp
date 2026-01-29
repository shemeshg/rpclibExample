#include "gtest/gtest.h"
#include <serverBal.h>
#include <clientBal.h>




class BalTest : public ::testing::Test {
protected:
    SvrRpc::ServerBal srv{8080};
    ClntRpc::ClientBal cb{"localhost", 8080};

    void SetUp() override {
        srv.startAsync();
    }
};

TEST_F(BalTest, AddingTwoNumbers)
{
    EXPECT_EQ(cb.add<float>(2, 3).get(), 5);
}

TEST_F(BalTest, CounterExampleAddsCorrectly)
{
    auto c = cb.getCounterExample(11);
    c->add(20);
    EXPECT_EQ(c->get(), 31);
}



