#ifndef VEHICLEFACTORYOBJECTPOOL_HPP
#define VEHICLEFACTORYOBJECTPOOL_HPP

//include directories
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace factoryMethodObjectPool
{
    /********** PRODUCT CLASS *******/
    enum eVehicleType
    {
        eSedan = 0,
        eXUV,
        eElectricCar,
        eElectricBus
    };

    //Vehicle product class
    class IVehicle
    {
    public:
        //pure virtual
        virtual void printVehicleType() = 0;
    };

    //sub product class
    class CSedan :public IVehicle
    {
    public:
        //virtual method 
        void printVehicleType() override
        {
            cout << "Vehicle type is Sedan" << endl;
        }
    };

    //sub product class
    class CXUV :public IVehicle
    {
    public:
        //virtual method 
        void printVehicleType() override
        {
            cout << "Vehicle type is XUV" << endl;
        }
    };

    //sub product class
    class CElectricCar :public IVehicle
    {
    public:
        //virtual method 
        void printVehicleType() override
        {
            cout << "Vehicle type is Electric Car" << endl;
        }
    };

    //sub product class
    class CElectricBus :public IVehicle
    {
    public:
        //virtual method 
        void printVehicleType() override
        {
            cout << "Vehicle type is Electric Bus" << endl;
        }
    };

    /********** FACTORY CLASS ********/


    //Factory interface class - Abstract class
    class IVehicleFactory
    {
    public:
        //Interface
        virtual IVehicle* createProduct(eVehicleType type) = 0;
    };

    static const vector<eVehicleType> gAllVehicleTypes = {
    eVehicleType::eElectricBus, eVehicleType::eElectricCar, eVehicleType::eSedan, eVehicleType::eXUV
    };

    //Concrete class
    class CVehicleFactory : public IVehicleFactory
    {
    private:
       
            std::map<eVehicleType, IVehicle*> objectPool;
    public:

        CVehicleFactory() 
        {
            for (auto&& type : gAllVehicleTypes)
            {
                if (eVehicleType::eElectricBus == type)
                {
                    objectPool[eVehicleType::eElectricBus] = new CElectricBus;
                }
                else if (eVehicleType::eElectricCar == type)
                {
                    objectPool[eVehicleType::eElectricCar] = new CElectricCar;
                }
                else if (eVehicleType::eXUV == type)
                {
                    objectPool[eVehicleType::eXUV] = new CXUV;
                }
                else if (eVehicleType::eSedan == type)
                {
                    objectPool[eVehicleType::eSedan] = new CSedan;
                }
                else{ //something wrong
                }
            }
        }

        //Factory method to create instance
        IVehicle* createProduct(eVehicleType type) override
        {
            IVehicle* vehicle = nullptr;
            
            auto instance = objectPool.find(type);
            if (instance != objectPool.end())
            {
                vehicle = instance->second;
            }

            return vehicle;
        }
    };

    class CClient
    {
        IVehicle* vehicle;
        IVehicleFactory* factory;

    public:
        CClient() :vehicle(nullptr) {
            factory = new CVehicleFactory;
        }

        //getVehicle
        void getVehicle(eVehicleType type)
        {
            vehicle = factory->createProduct(type);
        }

        void printVehicleDetails()
        {
            if (nullptr != vehicle)
            {
                vehicle->printVehicleType();
            }
        }

    };

    void testFactoryMethod()
    {
        CClient* client = new CClient;
        client->getVehicle(eSedan);
        client->printVehicleDetails();
    }
}

#endif