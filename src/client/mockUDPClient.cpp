/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include "gmock/gmock.h"
//#include "include/Entities.hpp"

class mockUDPClient {
public:
    MOCK_METHOD(int, add, (int a, int b));
    MOCK_METHOD(int, mult, (int a, int b));
};

// client class
class MyClient {
public:
    MyClient(mockUDPClient * server) : srv(server) {;}
    void doMath() {
        std::cout << "add " << srv->add(2, 2) << std::endl;
        std::cout << "mult " << srv->mult(1, 2) << std::endl;
    }
private:
    mockUDPClient* srv;
};


TEST(ClientNetwork, test1) {
    // create instance of "InSequence" class to force gmock expect function calls in stict order
    //::testing::InSequence dummy;

    // here we create server instance, define calls order, parameters and return values
    mockUDPClient udpClient;
    // we expect add() is called with parameters (2,2) and returns 4
    EXPECT_CALL(udpClient, add(2,2)).WillOnce(testing::Return(4));
    // we expect mult() is called with parameters (2,2) and returns 4
    EXPECT_CALL(udpClient, mult(2,2)).WillOnce(testing::Return(4));

    // do calculations
    MyClient cl(&udpClient);
    cl.doMath();
}
