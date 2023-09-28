#include <iostream>
#include "FSM_Pattern/CoinMachine.hpp"
#include "FactoryMethod/VehicleFactory_AbstractClass.hpp"
#include "FactoryMethod/VehicleFactory_ConcreteClass.hpp"
#include "FactoryMethod/VehicleFactory_ObjectPool.hpp"
#include "DecoratorPattern/DecoratorPattern.hpp"
#include "ProxyPattern/ProxyPattern.hpp"
#include "AdapterPattern/AdapterPattern.hpp"
#include "FlyweightPattern/FlyweightPattern.hpp"
#include "ObserverPattern/OberverPattern.hpp"
#include "TemplateMethod/TemplateMethod.hpp"
#include "BridgePattern/BridgePattern.hpp"
#include "FacadePattern/FacadePattern.hpp"
#include "CommandPattern/CommandPattern.hpp"
#include "MediatorPattern/MediatorPattern.hpp"
#include "MomentoPattern/MomentoPattern.hpp"
#include "BuilderPattern/BuilderPattern.hpp"
#include "PrototypePattern/PrototypePattern.hpp"
#include "AbstractFactoryPattern/AbstractFactory.hpp"
#include "VisitorPattern/VisitorPattern.hpp"
#include "ChainOfResponsibility/ChainOfResponsibility.hpp"
#include "CompositePattern/CompositePattern.hpp"
#include "StrategyPattern/StrategyPattern.hpp"

int main()
{
    coinMachine::testFSMPattern();
    facoryMethodAbstractClass::testFactoryMethod();
    facoryMethodConcreteClass::testFactoryMethod();
    factoryMethodObjectPool::testFactoryMethod();
    decoratorpattern::testDecoratorpattern();
    proxypattern::testProxyPattern();
    adapterpattern::testAdapterPattern();
    flyweight::testFlyweightPattern();
    oberverpattern::testObserverPattern();
    templatemethod::testTemplateMethod();
    bridgePattern::testBridgePattern();
    facadePattern::testFacadePattern();
    commandPattern::remoteApplication();
    mediatorPattern::testClientCode();
    momentopattern::testClientCode();
    builderpattern::testClientCode();
    prototypepattern::testPrototypePattern();
    abstractpattern::testClientCode();
    visitorpattern::testClientCode();
    chainofresponsibility::testClientCode();
    compositepattern::testClientCode();
    strategyPattern::testClientCode();
}