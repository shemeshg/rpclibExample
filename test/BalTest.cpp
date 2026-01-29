#include "gtest/gtest.h"
#include <serverBal.h>
#include <clientBal.h>




class BalTest : public ::testing::Test {
protected:
    SvrRpc::ServerBal srv{8080};
    ClntRpc::ClientBal cb{"localhost", 8080};


    void SetUp() override {
        srv.startAsync();
        cb.setClientTimeout(60000);
    }
};

TEST_F(BalTest, AddingTwoNumbers)
{
    //add that **run async**
    //.get waits and return answer
    EXPECT_EQ(cb.add<float>(2, 3).get(), 5);
}

TEST_F(BalTest, CounterExampleAddsCorrectly)
{
    auto c = cb.getCounterExample(11);
    c->add(20);
    EXPECT_EQ(c->get(), 31);
}

TEST_F(BalTest, SessionTimeoutException)
{
    auto c = cb.getCounterExample(11);
    c->add(20);
    // get here is *not about async*, there is a sync remote call that 
    // called `get`
    auto i = c->get();
    c->setExpiredAt(-2); //default is -1=never, 0=now(0 ms from now)
    cb.sessionStateCleanup();
    EXPECT_THROW(c->get(), rpc::rpc_error);
}


