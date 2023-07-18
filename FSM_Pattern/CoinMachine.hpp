#ifndef COINMACHINESTATE_H
#define COINMACHINESTATE_H

#include <iostream>

using namespace std;

namespace coinMachine
{
    //machine states
    enum eMachineState
    {
        STATE_LOCKED = 0,
        STATE_UNLOCKED,
        STATE_BROKEN
    };

    //actions
    enum eStateActions
    {
        EVENT_COIN_DETECTED = 0,
        EVENT_PASS,
        EVENT_FIXED,
        EVENT_FAILED
    };

    //enum machine working state
    enum eMachineWorkingStatus
    {
        STATUS_MACHINE_INVALID = 0,
        STATUS_MACHINE_WORKING,
        STATUS_MACHINE_REPAIR
    };

    //enum gate status
    enum eMachineGateStatus
    {
        STATUS_GATE_INVALID = 0,
        STATUS_GATE_OPENED,
        STATUS_GATE_CLOSED
    };


    //forward declarations
    class CLockedState;
    class CCoinMachine;

    //Interface class for coin machine state and actions
    class IMachineState
    {
        private:
        static eMachineWorkingStatus workingStatus;
        static eMachineGateStatus gateStatus;
        static bool isInitialised;

        public:
        void initVariables()
        {
            //Init variables only once 
            if (!isInitialised)
            {
                workingStatus = STATUS_MACHINE_WORKING;
                gateStatus = STATUS_GATE_CLOSED;
                isInitialised = true;
            }
        }
        //state action fuctions which has no actions to take
        //When called from the inappropriate state objects
        virtual void machineFailed(CCoinMachine* machine)
        {
            cout << "IMachineState::machineFailed:: wrong state ::no action " << endl;
        }
        virtual void coinDetected(CCoinMachine* machine)
        {
            cout << "IMachineState::coinDetected:: wrong state :: no action " << endl; 
        }
        virtual void personPassed(CCoinMachine* machine)
        {
            cout << "IMachineState::personPassed:: wrong state :: no action " << endl;
        }
        virtual void machineFixed(CCoinMachine* machine) 
        {
            cout << "IMachineState::machineFixed:: wrong state :: no action " << endl;
        }
        virtual void enterState(CCoinMachine* machine)
        { 
            cout << "IMachineState::enterState:: wrong state :: no action " << endl;
        }
        virtual void exitState(CCoinMachine* machine)
        { 
            cout << "IMachineState::exitState:: no action " << endl;
        }

        //behavioural functions 
        bool openGate();

        bool closeGate();

        inline void setMachineStatus(const eMachineWorkingStatus status)
        {
            if (status != workingStatus)
            {
                workingStatus = status;
            }
        }
        //machine working status
        inline bool isMachineInWorkingStatus() const
        {
            return (workingStatus == STATUS_MACHINE_WORKING) ? (true):(false);
        }

        //set gate status
        inline void setGateStatus(const eMachineGateStatus status)
        {
            if (status != gateStatus)
            {
                gateStatus = status;
            }
        }

        //get gate status
        inline eMachineGateStatus getGateStatus() const
        {
            return gateStatus;
        }

        //utility functions
        inline void playAlarm()
        {
            cout << "Locked state:: ALARM!!! Person trying to pass in Locked State" << endl;
        }
        inline void printErrorMsg()
        {
            cout << "MACHINE OUT OF ORDER!!!!!!!" << endl;
        }
        inline void printThankYou()
        {
            cout << "THANK YOU!!!!!!!" << endl;
        }
        virtual ~IMachineState() {}
    };

    //FSM context class 
    class CCoinMachine
    {
        IMachineState *machineState; //pointer to state class

        public:
        CCoinMachine();
        ~CCoinMachine() {}
        void setState(IMachineState *newState); //changestate
        void placeCoin();
    };

    //Locked state class
    class CLockedState: public IMachineState
    {
        private:
        static CLockedState* lockedStateObj; //singleton object

        public:
        static IMachineState* getLockedStateObj();

        //override functions
        void coinDetected(CCoinMachine* machine) override; //when coin detected
        void machineFailed(CCoinMachine* machine) override; // when machine failed
        void enterState(CCoinMachine* machine) override; //when entering to the locked state
        void exitState(CCoinMachine* machine) override; //when exiting from locked state
        void personPassed(CCoinMachine* machine) override; //when person passed

        //destructor
        ~CLockedState(){}        
    };


    //Unlocked state class
    class CUnlockedState: public IMachineState
    {
        private:
        static CUnlockedState* unlockedStateObj;//singleton object

        public:
        static IMachineState* getUnlockedStateObj();
    
        //override functions
        void coinDetected(CCoinMachine* machine) override; //when coin detected
        void machineFailed(CCoinMachine* machine) override; // when machine failed        
        void enterState(CCoinMachine* machine) override;  //when entering to the unlocked state  
        void exitState(CCoinMachine* machine) override;   //when exiting from unlocked state
        void personPassed(CCoinMachine* machine) override; //when person passed
        //destructor
        ~CUnlockedState(){}
    };    

    ////Broken state class
    class CBrokenState: public IMachineState
    {
        private:
        static CBrokenState* brokenStateObj;//singleton object

        public:
        static IMachineState* getBrokenStateObj();

        //override functions
        void enterState(CCoinMachine* machine) override; //when entering to the broken state  
        void exitState(CCoinMachine* machine) override {} //when exiting from broken state
        void machineFixed(CCoinMachine* machine) override; //when machine fixed

        //destructor
        ~CBrokenState() {}
    };    

    void testFSMPattern()
    {
        //TESTING THE FUNCTIONALITY
        CCoinMachine *coinMachine = new CCoinMachine;
        int count = 0;
        while (count <= 25)
        {
            coinMachine->placeCoin();
            count++;
        }
    }
}

#endif