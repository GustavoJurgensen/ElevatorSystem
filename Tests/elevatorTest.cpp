#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../elevador.h"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrictMock;

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

TEST(ElevatorTests, PortaTest)
{
    Elevador elevador;

    elevador.abre_porta();
    EXPECT_TRUE(elevador.get_status_porta());

    elevador.fecha_porta();
    EXPECT_FALSE(elevador.get_status_porta());
}

TEST(ElevatorTests, entrada_reqTest)
{
    Elevador elevador;

    //testes de falha - andares inexistentes
    EXPECT_FALSE(elevador.entrada_req(5));
    EXPECT_FALSE(elevador.entrada_req(-1));

    //testes de falha - andar ja existente na fila
    EXPECT_TRUE(elevador.entrada_req(1));
    EXPECT_FALSE(elevador.entrada_req(1));

    //testes andares existentes
    EXPECT_TRUE(elevador.entrada_req(3));
    EXPECT_TRUE(elevador.entrada_req(2));

    std::vector<int> andar_requisitado = elevador.get_andar_requisitado();
    //valida ordenação
    EXPECT_EQ(andar_requisitado.size(),3);
    EXPECT_EQ(andar_requisitado[0],2);
    EXPECT_EQ(andar_requisitado[1],3);
    EXPECT_EQ(andar_requisitado[2],1);
}
TEST(ElevatorTests, destino_reqTest)
{
    Elevador elevador;

    EXPECT_EQ(elevador.get_andar_atual(),1);

    //testes de falha - andares inexistentes
    EXPECT_FALSE(elevador.destino_req(5));
    EXPECT_FALSE(elevador.destino_req(-1));

    //configura buffer andares
    elevador.entrada_req(3);
    elevador.entrada_req(2);

    //testes andares existentes
    EXPECT_TRUE(elevador.destino_req(1));

    std::vector<int> andar_requisitado = elevador.get_andar_requisitado();
    //valida ordenação - prioridade default
    EXPECT_EQ(andar_requisitado.size(),3);
    EXPECT_EQ(andar_requisitado[0],2);
    EXPECT_EQ(andar_requisitado[1],3);
    EXPECT_EQ(andar_requisitado[2],1);

    //valida ordenação - mudança de prioridade de andar já existente
    elevador.destino_req(3);
    andar_requisitado = elevador.get_andar_requisitado();
    EXPECT_EQ(andar_requisitado.size(),3);
    EXPECT_EQ(andar_requisitado[0],2);
    EXPECT_EQ(andar_requisitado[1],1);
    EXPECT_EQ(andar_requisitado[2],3);

    // test destino atual
    EXPECT_EQ(elevador.get_destino_atual(),3);
}