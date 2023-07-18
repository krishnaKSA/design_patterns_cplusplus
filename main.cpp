#include <iostream>
#include "FSM_Pattern/CoinMachine.hpp"
#include "FactoryMethod/VehicleFactory_AbstractClass.hpp"
#include "FactoryMethod/VehicleFactory_ConcreteClass.hpp"
#include "FactoryMethod/VehicleFactory_ObjectPool.hpp"


int main()
{
    coinMachine::testFSMPattern();
    facoryMethodAbstractClass::testFactoryMethod();
    facoryMethodConcreteClass::testFactoryMethod();
    factoryMethodObjectPool::testFactoryMethod();
    return 0;
}