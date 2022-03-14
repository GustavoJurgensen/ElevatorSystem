#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../elevador.h"
#include "../pessoa.h"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrictMock;

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

using namespace std;

class MockElevador : public Elevador
{

public:
    MOCK_METHOD(bool, entrada_req, (int));
    MOCK_METHOD(bool, destino_req, (int));
};

TEST(ElevatorTests, Construtor)
{
    // Arrange
    MockElevador elevador;
    // Assert
    // EXPECT_EQ(elevador.get_andar_atual(),1);
}

TEST(PessoaTest,PessoaParcial)
{
    Pessoa p;

}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}