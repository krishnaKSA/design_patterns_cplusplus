#ifndef FACADEPATTERN_HPP
#define FACADEPATTERN_HPP

#include <iostream>
using namespace std;

namespace facadePattern
{
    //Order class
    class Order
    {
        public:
        void placeOrder()
        {
            cout<<"Order::order placed "<<endl;
        }
    };

    //Payment class
    class Payment
    {
        public:
        void payBill()
        {
            cout<<"Payment::Payment done "<<endl;
        }
    };

    //Delivery class
    class Delivery
    {
        public:
        void deliverOrder()
        {
            cout<<"Delivery::Delivery completed "<<endl;
        }
    };

    //Facade class
    class Facade
    {
        private:
        //Facade holds the objects of subsystems
        Order *order_obj;
        Payment *payment_obj;
        Delivery *delivery_obj;

        public:
        Facade(Order* oObj=nullptr, Payment* pObj=nullptr, Delivery* dObj=nullptr)
        {
            order_obj = oObj;
            payment_obj = pObj;
            delivery_obj = dObj;
        }

        //customer service function
        void customerService()
        {
            bool bRetValue = false;
            if(nullptr != order_obj)
            {
                order_obj->placeOrder();

                if(nullptr != payment_obj)
                {
                    payment_obj->payBill();

                    if(nullptr != delivery_obj)
                    {
                        delivery_obj->deliverOrder();
                        bRetValue = true;
                    }
                }
            }
            if(!bRetValue)
            {
                cout<<"Facade::CustomerService :: Couldn't able to place the order !!!"<<endl;
            }
            else
            {
                cout<<"Facade::CustomerService :: Order placed successfully !!!"<<endl;
            }
        }
    };

    void testFacadePattern()
    {
        Facade* obj = new Facade(new Order, new Payment, new Delivery);
        obj->customerService();
    }
}

#endif