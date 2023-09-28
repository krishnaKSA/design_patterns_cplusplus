#ifndef COMMANDPATTERN_HPP
#define COMMANDPATTERN_HPP

#include <iostream>
using namespace std;

namespace commandPattern
{
    //Receiver interface
    class IDevice
    {
        public:
        virtual void On() = 0;
        virtual void Off() = 0;
        virtual void Up() = 0;
        virtual void Down() = 0;
    };

    //Receiver concrete class
    class Light:public IDevice
    {
        public:
        void On() override
        {
            cout<<"Light turned ON"<<endl;
        }
        void Off() override
        {
            cout<<"Light turned OFF"<<endl;
        }
        void Up() override
        {
            cout<<"Light brightness increased"<<endl;
        }
        void Down() override
        {
            cout<<"Light brightness decreased"<<endl;
        }
    };

    class Speaker:public IDevice
    {
        public:
        void On() override
        {
            cout<<"Speaker turned ON"<<endl;
        }
        void Off() override
        {
            cout<<"Speaker turned OFF"<<endl;
        }
        void Up() override
        {
            cout<<"volume increased"<<endl;
        }
        void Down() override
        {
            cout<<"volume decreased"<<endl;
        }
    };

    //Command interface class
    class ICommand
    {
        public:
        virtual void execute() = 0;
    };

    //Concrete command class
    //On command
    class OnCommand: public ICommand
    {
        private:
        IDevice *device;
        public:
        OnCommand(IDevice* obj):device(obj)
        {

        }
        void execute() override
        {
            device->On();
        }
    };
    //OFF command
    class OffCommand: public ICommand
    {
        private:
        IDevice *device;
        public:
        OffCommand(IDevice* obj):device(obj)
        {

        }
        void execute() override
        {
            device->Off();
        }
    };
    //Up command
    class UpCommand: public ICommand
    {
        private:
        IDevice *device;
        public:
        UpCommand(IDevice* obj):device(obj)
        {

        }
        void execute() override
        {
            device->Up();
        }
    };
    //Down command
    class DownCommand: public ICommand
    {
        private:
        IDevice *device;
        public:
        DownCommand(IDevice* obj):device(obj)
        {

        }
        void execute() override
        {
            device->Down();
        }
    };

    //Application class
    class Invoker
    {
        private:
        ICommand* onCommand;
        ICommand* offCommand;
        ICommand* upCommand;
        ICommand* downCommand;
        public:
        Invoker(ICommand* onCommand,ICommand* offCommand,ICommand* upCommand,ICommand* downCommand)
        {
            this->downCommand = downCommand;
            this->onCommand = onCommand;
            this->offCommand = offCommand;
            this->upCommand = upCommand;
        }
        void onClick()
        {
            onCommand->execute();
        }
        void offClick()
        {
            offCommand->execute();
        }
        void upclick()
        {
            upCommand->execute();
        }
        void downClick()
        {
            downCommand->execute();
        }
    };

    void remoteApplication()
    {
        //device class
        Light* lightObj = new Light();
        Speaker* SpeakerObj =  new Speaker();

        //create light remote object
        Invoker *lightApplObj = new Invoker(new OnCommand(lightObj), new OffCommand(lightObj), new UpCommand(lightObj), new DownCommand(lightObj));
        lightApplObj->onClick();
        lightApplObj->upclick();
        lightApplObj->downClick();
        lightApplObj->offClick();

        //create speaker remote object
        Invoker *speakerApplObj = new Invoker(new OnCommand(SpeakerObj), new OffCommand(SpeakerObj), new UpCommand(SpeakerObj), new DownCommand(SpeakerObj));
        speakerApplObj->onClick();
        speakerApplObj->upclick();
        speakerApplObj->downClick();
        speakerApplObj->offClick();
    }
}
#endif