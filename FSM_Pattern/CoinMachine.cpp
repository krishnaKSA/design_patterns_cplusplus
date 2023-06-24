#include <iostream>
#include "CoinMachineState.h"

using namespace coinMachine;

/* static variable initialization*/
CLockedState* CLockedState::lockedStateObj = 0;
CUnlockedState* CUnlockedState::unlockedStateObj = 0;
CBrokenState* CBrokenState::brokenStateObj = 0;

bool IMachineState::isInitialised = false;
eMachineWorkingStatus IMachineState::workingStatus = STATUS_MACHINE_INVALID;
eMachineGateStatus IMachineState::gateStatus = STATUS_GATE_INVALID;

/****** COIN MACHINE *****/

CCoinMachine::CCoinMachine()
{
    machineState = CLockedState::getLockedStateObj(); //default state
    machineState->initVariables();
}

void CCoinMachine::setState(IMachineState* newState)
{
    machineState->exitState(this);//exit functionalities called for old state
    machineState = newState;
    machineState->enterState(this); //enter functionlities called for new state
}

void CCoinMachine::placeCoin()
{
    machineState->coinDetected(this);
}

/***** INTERFACE STATE CLASS **********/

bool IMachineState::openGate()
{
    bool retStaus = false;
    if (isMachineInWorkingStatus())
    {
        setGateStatus(STATUS_GATE_OPENED);
        retStaus = true;
    }

    return retStaus;
}

bool IMachineState::closeGate()
{
    bool retStaus = false;
    if (isMachineInWorkingStatus())
    {
        setGateStatus(STATUS_GATE_CLOSED);
        return retStaus;
    }

    return retStaus;
}


/***** LOCKED STATE CLASS **********/

//get object
IMachineState* CLockedState::getLockedStateObj()
{
    if (0 == lockedStateObj)
    {
        lockedStateObj = new CLockedState;
    }
    return lockedStateObj;
}

//COin detected in locked state
void CLockedState::coinDetected(CCoinMachine* machine)
{
    cout << "CLockedState::coin detected " << endl;
    machine->setState(CUnlockedState::getUnlockedStateObj());
    
}

//functionality when entering locked state
void CLockedState::enterState(CCoinMachine* machine)
{
    if (!isMachineInWorkingStatus())
    {
        machineFailed(machine);
    }
    else
    {
        setGateStatus(STATUS_GATE_CLOSED);
    }
}

//functionality when exit from locked state
void CLockedState::exitState(CCoinMachine* machine)
{

}

//person passing whilst in locked state
void CLockedState::personPassed(CCoinMachine* machine)
{
    playAlarm();
}

//If machine in failed state
void CLockedState::machineFailed(CCoinMachine* machine)
{
    setMachineStatus(STATUS_MACHINE_REPAIR);
    machine->setState(CBrokenState::getBrokenStateObj());
}

/***** UNLOCKED STATE CLASS **********/

//COin detected in unlocked state
void CUnlockedState::coinDetected(CCoinMachine* machine)
{
    cout << "CUnlockedState::coin detected no action as already in unlocked state" << endl;
}

//If machine in failed state
void CUnlockedState::machineFailed(CCoinMachine* machine)
{
    setMachineStatus(STATUS_MACHINE_REPAIR);
    machine->setState(CBrokenState::getBrokenStateObj());
}

//person passing whilst in unlocked state
void CUnlockedState::personPassed(CCoinMachine* machine)
{
    cout << "CUnlockedState:: person passed" << endl;
    machine->setState(CLockedState::getLockedStateObj());
}

//functionality when entering unlocked state
void CUnlockedState::enterState(CCoinMachine* machine)
{
    cout << "CUnlockedState:: Entered to unlock state" << endl;
    if (openGate())
    {
        personPassed(machine);
    }
    else
    {
        machineFailed(machine);
    }

}

//functionality when exiting from unlocked state
void CUnlockedState::exitState(CCoinMachine* machine)
{
    if (isMachineInWorkingStatus())
    {
        closeGate();
        printThankYou();
    }
}

//get instance of unlocked state object
IMachineState* CUnlockedState::getUnlockedStateObj()
{
    if (0 == unlockedStateObj)
    {
        unlockedStateObj = new CUnlockedState;
    }
    return unlockedStateObj;
}


/***** BROKEN STATE CLASS **********/

//get instance of broken state object
IMachineState* CBrokenState::getBrokenStateObj()
{
    if (0 == brokenStateObj)
    {
        brokenStateObj = new CBrokenState;
    }
    return brokenStateObj;
}


//If machine fixed
void CBrokenState::machineFixed(CCoinMachine* machine)
{
    setMachineStatus(STATUS_MACHINE_WORKING);
    machine->setState(CLockedState::getLockedStateObj());
}

//when machine goes to broken state
void CBrokenState::enterState(CCoinMachine* machine)
{
    printErrorMsg();
    machineFixed(machine);
}