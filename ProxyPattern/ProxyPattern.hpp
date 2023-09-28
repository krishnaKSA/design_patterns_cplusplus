#ifndef PROXYPATTERN_HPP
#define PROXYPATTERN_HPP

//Include directory
#include <iostream>
#include <vector>

using namespace std;

namespace proxypattern
{
    //Interface
    class IInternet
    {
        public:
        virtual void connectTo(string serverHost) = 0;
    };

    //Real object
    class RealInternet: public IInternet
    {
        public:
        void connectTo(string serverHost) override
        {
            cout<<"RealInternet: Connecting to "<<serverHost<<endl;
        } 
    };

    //proxy object
    class ProxyInternet: public IInternet
    {
        private:
        //Real object instance
        RealInternet* realInternet;

        //list of blocked sites
        vector<string> blockedSites;

        void createBlockedSiteList()
        {            
            blockedSites.push_back("google.com");
            blockedSites.push_back("blog.com");
            blockedSites.push_back("geeks.com");
        }
        public:
        ProxyInternet()
        {
            realInternet = new RealInternet;
            createBlockedSiteList();
        }
        void connectTo(string serverHost) override
        {
            bool isBlocked = false;
            //check the blocked sites
            for(auto siteName:blockedSites)
            {
                if(serverHost == siteName)
                {
                    //site is blocked
                    cout<<"ProxyInternet: blocked site :"<<serverHost<<endl;
                    isBlocked = true;
                    break;
                }
            }

            //Site is not blocked
            if(false == isBlocked)
            {
                cout<<"ProxyInternet: Connecting to "<<serverHost<<endl;
                //calling the real object to do the functionality
                realInternet->connectTo(serverHost);
            }
        } 
    };

    void testProxyPattern()
    {
        //client code
        IInternet* internet = new ProxyInternet;
        internet->connectTo("google.com");
        internet->connectTo("tutorialpoint.com");
    }
}

#endif