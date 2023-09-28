#ifndef STRATEGYPATTERN_HPP
#define STRATEGYPATTERN_HPP

#include <iostream>
#include <string>
using namespace std;

namespace strategyPattern
{
    //Strategy abstract class
    class IRouteStrategy
    {
        public:
        virtual void buildRoute() = 0;
    };

    //concrete strategy class
    class FourWheelerStrategy: public IRouteStrategy
    {
        public:
        void buildRoute()
        {
            cout<<"FourWheelerStrategy route projected to the user"<<endl;
        }
    };

    //concrete strategy class
    class PublicTransportStrategy: public IRouteStrategy
    {
        public:
        void buildRoute()
        {
            cout<<"PublicTransportStrategy route projected to the user"<<endl;
        }
    };

    //concrete strategy class
    class WalkStrategy: public IRouteStrategy
    {
        public:
        void buildRoute()
        {
            cout<<"WalkStrategy route projected to the user"<<endl;
        }
    };

    //context class
    class Context
    {
        private:
        IRouteStrategy* strategy;

        public:
        Context():strategy(nullptr)
        {

        }

        //Set strategy 
        void setStrategy(IRouteStrategy* strategy)
        {
            this->strategy = strategy;
        }

        //Build route based on the strategy selected
        void buildRoute()
        {
            if(nullptr != strategy)
            {
                this->strategy->buildRoute();
            }
            else{
                cerr<<"No strategy selected "<<endl;
            }
        }
    };

    //Class Application
    class Application
    {
        std::string userChoice;
        Context* context;

        public:
        Application(Context* context)
        {
            this->context = context;
        }
        //user selection
        void findRoute(string selectedOption)
        {
            if("car" == selectedOption)
            {
                this->context->setStrategy(new FourWheelerStrategy);
            }
            else if("walk" == selectedOption)
            {
                this->context->setStrategy(new WalkStrategy);
            }
            else if("bus" == selectedOption)
            {
                this->context->setStrategy(new PublicTransportStrategy);
            }
            else{
                //do nothing
            }
            this->context->buildRoute();
        }
    };

    void testClientCode()
    {
        Context* obj = new Context();
        Application* appl = new Application(obj);
        appl->findRoute("bus");
        appl->findRoute("walk");
        appl->findRoute("car");

    }

}
#endif