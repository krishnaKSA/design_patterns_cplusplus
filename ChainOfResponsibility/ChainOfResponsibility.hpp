#ifndef CHAINOFRESPONSIBILITY_HPP
#define CHAINOFRESPONSIBILITY_HPP

#include <iostream>
using namespace std;

namespace chainofresponsibility
{
    //Interfacehandler
    class IHandler
    {
        public:
        virtual IHandler* setNextHandler(IHandler* nextHandler) = 0;
        virtual std::string handle(string request) = 0;
    };

    //Base handler
    class BaseHandler: public IHandler
    {
        private:
        IHandler* nextHandler;

        public:
        BaseHandler():nextHandler(nullptr)
        {

        }
        IHandler* setNextHandler(IHandler* nextHandler) override
        {
            this->nextHandler = nextHandler;
            return nextHandler;
        }

        std::string handle(string request) override
        {
            if(nullptr != this->nextHandler)
            {
                return this->nextHandler->handle(request);
            }

            return {};
        }
    };

    class IntHandler: public BaseHandler
    {

        public:
        std::string handle(string request) override
        {
            if("int" == request)
            {
                return "IntHandler::request processed";
            }
            return BaseHandler::handle(request);
        }
    };
    class FloatHandler: public BaseHandler
    {
        public:
        std::string handle(string request) override
        {
            if("float" == request)
            {
                return "FloatHandler::request processed";
            }
            return BaseHandler::handle(request);
        }
    };

    class StringHandler: public BaseHandler
    {
        public:
        std::string handle(string request) override
        {
            if("string" == request)
            {
                return "StringHandler::request processed";
            }
            return BaseHandler::handle(request);
        }
    };

    void testClientCode()
    {
        BaseHandler* baseHandler = new BaseHandler;
        IntHandler* intHandler = new IntHandler;
        FloatHandler* floatHandler = new FloatHandler;
        StringHandler* stringHandler = new StringHandler;

        baseHandler->setNextHandler(intHandler)->setNextHandler(floatHandler)->setNextHandler(stringHandler);

        cout << baseHandler->handle("string") << endl;
        cout << baseHandler->handle("float") << endl;
        cout << baseHandler->handle("int") << endl;
    }
}

#endif