#ifndef BRIDGEPATTERN_HPP
#define BRIDGEPATTERN_HPP

#include <iostream>
#include "stdint.h"
using namespace std;

namespace bridgePattern
{
    //Implementation interface class.
    //This class provides the interfaces 
    class IDevice
    {
        public:
        virtual bool powerButton() = 0;
        virtual void setVolume(uint8_t value) = 0;
        virtual uint8_t getVolume() = 0;
        virtual uint8_t getChannelNumber() = 0;
        virtual void setChannelNumber(uint8_t value) = 0;
    };

    //Implementation class
    class TV : public IDevice
    {
        private:
        uint8_t channelNumber; //current channel number
        uint8_t volume; //current volume levels
        bool powerStatus; //current power status
        uint8_t MAX_VOLUME; //Max volume level
        uint8_t MAX_CHANNELS; //Maximum number of channels

        public:
        //constructor
        TV()
        {
            //set the default values
            channelNumber = 1; //default
            volume = 8; //default
            powerStatus = false; //powerOff
            MAX_VOLUME = 255;
            MAX_CHANNELS = 200;
        }
        //Set power ON/OFF
        bool powerButton()
        {
            powerStatus = !powerStatus;
            printf("Power status =%s \n",(powerStatus == true ? "ON" : "OFF"));
            return powerStatus;
        }
        //Set volume
        void setVolume(uint8_t value)
        {
            if(MAX_VOLUME != value)
            {
               volume = value;
            }
            if(0 == volume)
            {
                printf("Volume Muted \n");
            }
            else
            {
                printf("Volume level =%d\n",volume);
            }
        }
        //Get current volume
        uint8_t getVolume()
        {
            return volume;
        }
        //Set channel number
        void setChannelNumber(uint8_t value)
        {
            if(MAX_CHANNELS != value)
            {
                channelNumber = value;
            }
            printf("Channel number =%d\n", channelNumber);
        }
        //Get current channel number
        uint8_t getChannelNumber()
        {
            return channelNumber;
        }
    };

    //Abstraction class
    class remote
    {
        public:
        //implementation class object
        IDevice* deviceObj;
        
        //constructor
        remote(IDevice* device)
        {
            deviceObj = device;
        }
        //Set power status
        void power()
        {
            deviceObj->powerButton();
        }
        //Volume Up
        void volumeUp(uint8_t value)
        {
            uint8_t volume = deviceObj->getVolume();
            deviceObj->setVolume(volume + value);
        }
        //Volume Down
        void volumeDown(uint8_t value)
        {
            uint8_t volume = deviceObj->getVolume();
            deviceObj->setVolume(volume - value);
        }
        //Channel Up
        void channelUp(uint8_t value)
        {
            uint8_t channelNum = deviceObj->getChannelNumber();
            cout<<"channel num "<<channelNum<<endl;
            deviceObj->setChannelNumber(value + channelNum);
        }
        //Channel Down
        void channelDown(uint8_t value)
        {
            uint8_t channelNum = deviceObj->getChannelNumber();
            deviceObj->setChannelNumber(channelNum - value);
        }
    };

    //Derived class from abstraction class
    class advancedRemote : public remote
    {
        public:
        advancedRemote(IDevice* device):remote(device)
        {

        }
        void mute()
        {
            deviceObj->setVolume(0);
        }
    };

    void testBridgePattern()
    {
        TV* tv = new TV();
        remote* abstractionObj = new remote(tv);

        //power On
        abstractionObj->power();
        abstractionObj->channelUp(1);
        abstractionObj->volumeDown(2);

        advancedRemote* advanced = new advancedRemote(tv);
        advanced->mute();
    }
}
#endif