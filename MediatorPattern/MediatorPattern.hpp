#ifndef MEDIATORPATTERN_HPP
#define MEDIATORPATTERN_HPP

#include <iostream>
using namespace std;

namespace mediatorPattern
{    
    //Mediator Interface
    class IMediator
    {
        public:
        virtual void action() = 0;
        virtual void start(bool value) = 0;
    };

    class IBaseComponent
    {
        protected:
        IMediator* mediator;
        public:
        IBaseComponent()
        {
           this->mediator = nullptr;
        }
        void setMediator(IMediator* mediator) {
           this->mediator = mediator;
        } 
    };
    //Button class
    class Button : public IBaseComponent
    {
        private:
        public:
        void press()
        {
            mediator->action();
        }
    };
    //Fan class
    class Fan : public IBaseComponent
    {
        private:
        bool turnOn;
        public:
        Fan()
        {
            turnOn = false;
        }
        void turnOnOROff()
        {
            if(!turnOn)
            {
                cout<<"FAN: turn ON"<<endl;
                turnOn = true;
            }
            else
            {
                cout<<"FAN: turn OFF"<<endl;
                turnOn = false;
            }
            if(mediator)
            {
                mediator->start(turnOn);
            }
        }

    };
    //PowerSupply class
    class PowerSupply: public IBaseComponent
    {
        private:
        bool turnOn;
        public:
        PowerSupply()
        {
            turnOn = false;
        }
        void turnOnOROff(bool value)
        {
            if(value)
            {
                cout<<"PowerSupply: turn ON"<<endl;
                turnOn = true;
            }
            else
            {
                cout<<"PowerSupply: turn OFF"<<endl;
                turnOn = false;
            }
        }
        

    };

    //Mediator class
    class Mediator:public IMediator
    {
        private:
        Button* button;
        Fan* fan;
        PowerSupply* power;

        public:
        Mediator(Button* button,  Fan* fan, PowerSupply* power)
        {
            this->button = button;
            this->fan = fan;
            this->power = power;
            this->button->setMediator(this);
            this->fan->setMediator(this);
            this->power->setMediator(this);
        }
        void action() override
        {
            fan->turnOnOROff();
        }
        void start(bool value) override
        {
            power->turnOnOROff(value);
        }
    };

    //client code
    void testClientCode()
    {
        
        Button* button  = new Button;
        Fan* fan = new Fan;
        PowerSupply* power = new PowerSupply;
        IMediator* mediator = new Mediator(button, fan, power);
        button->setMediator(mediator);
        fan->setMediator(mediator);
        power->setMediator(mediator);
        button->press();
        button->press();
        
    }

}
#endif