#ifndef BUILDERPATTERN_HPP
#define BUILDERPATTERN_HPP

#include <iostream>
using namespace std;

namespace builderpattern
{

    //Product class
    //Car 
    class Car
    {
        private:
        uint8_t seats;
        uint8_t airbag;
        bool gps;
        bool rearCamera;
        bool sportsEngine;
        uint8_t doors;

        public:
        Car()
        {

        }
        void setSeats(uint8_t seats)
        {
            this->seats = seats;
        }
        void setAirbags(uint8_t airbags)
        {
            this->airbag = airbags;
        }
        void setGps(bool gps)
        {
            this->gps = gps;
        }
        void setRearCamera(bool rearCamera)
        {
            this->rearCamera = rearCamera;
        }
        void setSportsEngine(bool sportsEngine)
        {
            this->sportsEngine = sportsEngine;
        }
        void setDoors(uint8_t doors)
        {
            this->doors = doors;
        }
    };

    //Car Manual
    class CarManual
    {
        private:
        uint8_t seats;
        uint8_t airbag;
        bool gps;
        bool rearCamera;
        bool sportsEngine;
        uint8_t doors;

        public:
        CarManual(){}
        void setSeats(uint8_t seats)
        {
            this->seats = seats;
        }
        void setAirbags(uint8_t airbags)
        {
            this->airbag = airbags;
        }
        void setGps(bool gps)
        {
            this->gps = gps;
        }
        void setRearCamera(bool rearCamera)
        {
            this->rearCamera = rearCamera;
        }
        void setSportsEngine(bool sportsEngine)
        {
            this->sportsEngine = sportsEngine;
        }
        void setDoors(uint8_t doors)
        {
            this->doors = doors;
        }
        
        uint8_t getSeats()
        {
            return seats;
        }
    };

    //BuilderInterface
    class IBuilder
    {
        public:
        virtual void reset() = 0;
        virtual void buildDoors(uint8_t value) = 0;
        virtual void buildAirbags(uint8_t value) = 0;
        virtual void buildSeats(uint8_t value) = 0;
        virtual void buildEngine(bool value) = 0;
        virtual void buildGps(bool value) = 0;
        virtual void buildRearCamera(bool value) = 0;
    };

    //Manual Car builder class
    class ManualCarBuilder:public IBuilder
    {
        private:
        Car* car;
        public:
        void reset()
        {
            car = new Car();
        }
        Car* getProduct()
        {
            return car;
        }
        void buildDoors(uint8_t value) override
        {
            car->setDoors(value);
        }
        void buildAirbags(uint8_t value) override
        {
            car->setAirbags(value);
        }
        void buildSeats(uint8_t value) override
        {
            car->setSeats(value);
        }
        void buildEngine(bool value) override
        {
            car->setSportsEngine(value);
        }
        void buildGps(bool value) override
        {
            car->setGps(value);
        }
        void buildRearCamera(bool value) override
        {
            car->setRearCamera(value);
        }
    };

    //Car manual builder class
    class ManualBuilder:public IBuilder
    {
        private:
        CarManual* manual;
        public:
        void reset()
        {
            manual = new CarManual();
        }
        CarManual* getProduct()
        {
            return manual;
        }
        void buildDoors(uint8_t value) override
        {
            manual->setDoors(value);
        }
        void buildAirbags(uint8_t value) override
        {
            manual->setAirbags(value);
        }
        void buildSeats(uint8_t value) override
        {
            manual->setSeats(value);
        }
        void buildEngine(bool value) override
        {
            manual->setSportsEngine(value);
        }
        void buildGps(bool value) override
        {
            manual->setGps(value);
        }
        void buildRearCamera(bool value) override
        {
            manual->setRearCamera(value);
        }
    };

    //director class
    class Director
    {
        private:
        IBuilder* builder;
        public:
        Director()
        {
            builder = nullptr;
        }
        //set builder object
        void setBuilder(IBuilder* builder)
        {
            this->builder = builder;
        }
        //Build normal car
        void BuildNormalCar()
        {
            this->builder->reset();
            this->builder->buildAirbags(2);
            this->builder->buildDoors(4);
            this->builder->buildSeats(4);
            this->builder->buildEngine(false);
            this->builder->buildGps(true);
            this->builder->buildRearCamera(true);
        }

        //build sports car
        void BuildSportsCar()
        {
            this->builder->reset();
            this->builder->buildAirbags(2);
            this->builder->buildDoors(2);
            this->builder->buildSeats(2);
            this->builder->buildEngine(true);
            this->builder->buildGps(true);
            this->builder->buildRearCamera(true);
        }

    };

    void testClientCode()
    {
        ManualCarBuilder* carBuilder = new ManualCarBuilder();
        ManualBuilder* manualBuilder = new ManualBuilder();
        Director* director = new Director();
        //set car builder object
        director->setBuilder(carBuilder);
        director->BuildNormalCar();
        //set manual builder object
        director->setBuilder(manualBuilder);
        //get sports car
        director->BuildSportsCar();
        
        //get the car manual for sports car
        CarManual* manual = manualBuilder->getProduct();
    }

}
#endif