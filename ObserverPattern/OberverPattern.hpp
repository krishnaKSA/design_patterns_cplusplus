#ifndef OBSERVERPATTERN_HPP
#define OBSERVERPATTERN_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex> //once_flag

using namespace std;

namespace oberverpattern
{
    //Message class
    class CMessage 
    {
        private:
        string data;
        public:
        CMessage()
        {
            data =" ";
        }
        void setMessage(string message) 
        {
            data = message;
        }
        string getMessage() 
        {
            return data;
        }
    };

    enum eNotifyType
    {
        eEmail = 0,
        eSMS
    };

    //Listener Interface class
    class IListener
    {
        public:
        virtual void update(CMessage* message) = 0;
    };

    //Publisher Interface class
    class IPublisher
    {
        public:
        virtual void addListener(eNotifyType type, IListener* listener) = 0;
        virtual void removeListener(eNotifyType type, IListener* listener) = 0 ;
    };

    //Concrete publisher class
    class CPublisher: public IPublisher
    {
        private:
 
        static std::shared_ptr<CPublisher> publisher;
        std::unordered_map<eNotifyType, std::vector<IListener*>> listenerList;
        static std::once_flag s_once;
        
        CPublisher()
        {
            listenerList = std::unordered_map<eNotifyType, std::vector<IListener*>>();
        }

        public:

        static std::shared_ptr<CPublisher> getPublisher()
        {
            std::call_once(s_once, [&] {publisher = std::shared_ptr<CPublisher>(new CPublisher); });
            return publisher;
        }
        void addListener(eNotifyType type, IListener* listener) override
        {
            //check 
            if((eNotifyType::eEmail == type) || (eNotifyType::eSMS == type))
            {
                auto iter = listenerList.find(type);
                if( iter != listenerList.end())
                {
                    auto list = iter->second;
                    list.push_back(listener);
                }
                else
                {
                    std::vector<IListener*> tempList;
                    tempList.push_back(listener);
                    listenerList[type] = tempList;
                }
            }
            else{
                std::cerr<<__FUNCTION__<<" wrong type "<<type<<endl;
            }
        }

        void removeListener(eNotifyType type, IListener* listener) override
        {
            if(nullptr != listener)
            {
                auto iter = listenerList.find(type);
                if( iter != listenerList.end())
                {
                    auto list = iter->second;
                    size_t index = 0;
                    for(auto listenerId:list)
                    {
                        if(listenerId == listener)
                        {
                            list.erase(list.begin()+index);
                            break;
                        }
                        index++;
                    }
                    listenerList[type] = list;
                }
            }
        }

        void notifyListeners(eNotifyType type, CMessage* message)
        {
            auto iter = listenerList.find(type);
            if( iter != listenerList.end())
            {
                for(auto listener:iter->second)
                {
                    listener->update(message);
                }
            }
            else
            {
                cout<<"no listners for type = "<<type<<endl;
            }
        }

        void printListener()
        {
            for(auto iter:listenerList)
            {
                auto index = iter.first;
                for(auto list:iter.second)
                {
                    cout<<"listener "<<index<<" "<<list<<endl;
                }                
            }                
        }
    };

    std::shared_ptr<CPublisher> CPublisher::publisher = nullptr;
    once_flag CPublisher::s_once;

    class CTravelAgency 
    {
        private:
        std::shared_ptr<CPublisher> publisher;

        public:
        CTravelAgency()
        {
            publisher = CPublisher::getPublisher();
        }

        void busDelayed()
        {           
            string text = "bus delayed for 2 hours";
            CMessage* msg = new CMessage;
            msg->setMessage(text);
            publisher->notifyListeners(eNotifyType::eEmail, msg);
            publisher->notifyListeners(eNotifyType::eSMS, msg);
        }
    };

    class CEmailListener : public IListener
    {
        public:
        CEmailListener()
        {
            CPublisher::getPublisher()->addListener(eNotifyType::eEmail, this);
        }
        void update(CMessage* message) override
        {
            cout<<"In EMAIL "<<message->getMessage()<<endl;
        }
    };

    class CSMSListener : public IListener
    {
        public:
        CSMSListener()
        {
            CPublisher::getPublisher()->addListener(eNotifyType::eSMS, this);
        }
        void update(CMessage* message) override
        {
            cout<<"In SMS "<<message->getMessage()<<endl;
        }
    };

    void testClientCode()
    {
        CSMSListener* smsListener = new CSMSListener;
        CEmailListener* emailListener = new CEmailListener;

        CPublisher::getPublisher()->printListener();
        CTravelAgency* agency = new CTravelAgency;
        agency->busDelayed();

        CPublisher::getPublisher()->removeListener(eSMS, smsListener);
        agency->busDelayed();
    }

    void testObserverPattern()
    {
        testClientCode();
    }
}


#endif