#ifndef VEHICLEFACTORYABSTRACTCLASS_HPP
#define VEHICLEFACTORYABSTRACTCLASS_HPP

//include directories
#include <iostream>

using namespace std;

namespace facoryMethodAbstractClass
{
    /********** PRODUCT CLASS *******/
    enum eVehicleType
    {
        eSedan = 0,
        eXUV,
        eElectricCar
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

    /********** FACTORY CLASS ********/


    //Factory interface class - Abstract class
    class IVehicleFactory
    {
    public:
        //Factory method to create instance
        virtual IVehicle* createProduct(eVehicleType type) = 0;
    };

	//Sub creator class
	class CVehicleFactory : public IVehicleFactory
	{
	public:

		//Factory method to create instance
		IVehicle* createProduct(eVehicleType type) override
		{
			IVehicle* vehicle = nullptr;
			if (type == eSedan)
			{
				vehicle = new CSedan();
			}
			else if (type == eXUV)
			{
				vehicle = new CXUV();
			}
			else if (type == eElectricCar)
			{
				vehicle = new CElectricCar();
			}
			else {
				//return nullptr
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
        client->getVehicle(eElectricCar);
        client->printVehicleDetails();
    }
}

#endif