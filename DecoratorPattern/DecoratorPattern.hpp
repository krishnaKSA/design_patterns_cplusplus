

//include directory
#include <iostream>
#include <stdint.h>

using namespace std;

namespace decoratorpattern
{

    /************ COMPONENT CLASS/INTERFACE CLASS **************/
    //Interface class
    class  ICar
    {
        public:
        virtual void printCarModel() = 0;
        virtual uint32_t getCost() = 0;
    };

    /************* CONCRETE COMPONENT CLASS ********************/
    //Sedan
    class CSedan : public ICar
    {
        private:
        uint32_t cost;
        public:
        //constructor
        CSedan()
        {
            //cost of this car model
            cost = 1000000;
        }
        //Implementation of the pure virtual methods declared in the Interface class
        void printCarModel() override
        {
            cout<<" : car model is Sedan "<<endl;
        }
        uint32_t getCost() override
        {
            cout << "car cost "<<cost << " "<<endl;
            return cost;
        }
    };

    //mini
    class CMini : public ICar
    {
        private:
        uint32_t cost;
        public:
        //constructor
        CMini()
        {
            //cost of this car model
            cost = 650000;
        }
        //Implementation of the pure virtual methods declared in the Interface class
        void printCarModel() override
        {
            cout<<" : car model is Mini "<<endl;
        }
        uint32_t getCost() override
        {
            cout << "car cost "<<cost << " "<<endl;
            return cost;
        }
    };

    //XUV
    class CXUV : public ICar
    {
        private:
        uint32_t cost;
        public:
        //constructor
        CXUV()
        {
            //cost of this car model
            cost = 1500000;
        }
        //Implementation of the pure virtual methods declared in the Interface class
        void printCarModel() override
        {
            cout<<" : car model is XUV "<<endl;
        }
        uint32_t getCost() override
        {
            cout << "car cost "<<cost << " "<<endl;
            return cost;
        }
    };

    /********************* BASE DECORATOR ABSTRACT CLASS ***************/
    //Decorator class
    class CCarDecorator:public ICar
    {
        private:
        //interface class object
        ICar* car;

        public:
        //constructor
        CCarDecorator(ICar* carObject)
        {
            car = carObject;
        }
        //Implementation of the pure virtual methods declared in the Interface class
        void printCarModel() override
        {
            car->printCarModel();
        }
        uint32_t getCost() override
        {
            return car->getCost();
        }
        //additional features
        virtual void additionalFeatures() = 0;
    };

    /*************** CONCRETE DECORATOR CLASS *******************/
    //AirBag feature
    class CAirBags:public CCarDecorator
    {
        public:
        //Enum for air bag types
        enum eAirBagType
        {
            eFront = 0,
            eBack
        };

        //constructor
        CAirBags(ICar* carObject,eAirBagType type):CCarDecorator(carObject)
        {      
            //car object and type of the air bag selected by the customer passed as argument 
            //of the constrcutor call  
            airBagSupport = type;

            //cost calculations
            if(eFront == airBagSupport)
            {
                costOfAirBags = 20000;
            }
            else if(eBack == airBagSupport)
            {
                costOfAirBags = 40000;
            }
            else{
                airBagSupport = eFront;
                costOfAirBags = 20000;
            }

        }
        //additional features 
        uint32_t getCost() override
        {
            cout <<"Airbag cost = "<< costOfAirBags <<" + ";
            return CCarDecorator::getCost() + costOfAirBags;
        }    

        void printCarModel() override
        {
            additionalFeatures();
            CCarDecorator::printCarModel();
        }

        void additionalFeatures() override
        {
            cout<<"airbags added for "<<((eFront == airBagSupport) ? " front passengers " : "front and back passengers ");
        }
        
        private:
        //air bag cost
        uint32_t costOfAirBags;
        //type of the air bag selected by the user
        eAirBagType airBagSupport;
    };

    //Rear Camera
    class CRearCamera:public CCarDecorator
    {
        private:
        uint32_t costOfRearCamera;

        public:
        //car object and type of the air bag selected by the customer passed as argument 
        //of the constrcutor call  
        CRearCamera(ICar* carObject):CCarDecorator(carObject)
        {
            costOfRearCamera = 250000;
        }
        //Additional features
        uint32_t getCost() override
        {
            cout <<"cost of rearcamera = "<< costOfRearCamera <<" + ";
            return CCarDecorator::getCost() + costOfRearCamera;
        }

        void additionalFeatures() override
        {
            cout<<"rear camera added ";
        }

        void printCarModel() override
        {
            additionalFeatures();
            CCarDecorator::printCarModel();
        }
    };

    class CEntertainmentUnit:public CCarDecorator
    {
        public:
        //enum for HU models
        enum eHUModel
        {
            eBasic = 0,
            eMedium = 1,
            eAdvanced
        };

        //car object and type of the air bag selected by the customer passed as argument 
        //of the constrcutor call  
        CEntertainmentUnit(ICar* carObject,eHUModel type):CCarDecorator(carObject)
        {        
            HUModel = type;
            if(eBasic == HUModel)
            {
                costOfHU = 20000;
            }
            else if(eMedium == HUModel)
            {
                costOfHU = 32000;
            }
            else if(eAdvanced == HUModel)
            {
                costOfHU = 45000;
            }

        }

        //Additional features
        uint32_t getCost() override
        {
            cout << "HU cost " << costOfHU <<" + ";
            return CCarDecorator::getCost();
        }

        void additionalFeatures() override
        {
            cout<<"Entertainment unit added with Model "<<((HUModel == eBasic )?" Basic ":((HUModel == eMedium ) ? "Medium " : "Advanced "))<<" , ";
        }

        void printCarModel() override
        {
            additionalFeatures();
            CCarDecorator::printCarModel();
        }

        private:
        uint32_t costOfHU; //cost of the HU
        eHUModel HUModel; //HU model types
    };

    void testDecoratorpattern()
    {
        //Chosing sedan with front and back airbags and Medium type HU model
        ICar* carModel = new CSedan;
        carModel = new CAirBags(carModel, CAirBags::eBack);
        carModel = new CEntertainmentUnit(carModel, CEntertainmentUnit::eMedium);
        cout<<endl;
        carModel->printCarModel();
        cout <<endl << "Total cost = "<<carModel->getCost();

        //Chosing Mini with front airbags and basic type HU model
        carModel = new CMini;
        carModel = new CAirBags(carModel, CAirBags::eFront);
        carModel = new CEntertainmentUnit(carModel, CEntertainmentUnit::eBasic);
        cout<<endl;
        carModel->printCarModel();
        cout <<endl << "Total cost = "<<carModel->getCost();

        //Chosing XUV with rear camera, front and back airbags and advanced type HU model
        carModel = new CXUV;
        carModel = new CRearCamera(carModel);
        carModel = new CEntertainmentUnit(carModel, CEntertainmentUnit::eAdvanced);
        carModel = new CAirBags(carModel, CAirBags::eBack);
        cout<<endl;
        carModel->printCarModel();
        cout <<endl <<"Total cost = "<<carModel->getCost();
    }
}
