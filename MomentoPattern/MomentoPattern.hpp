#ifndef MOMENTOPATTERN_HPP
#define MOMENTOPATTERN_HPP

#include <iostream>
#include <vector>
using namespace std;

namespace momentopattern
{
    //forward declaration
    class Orginator;

    //Momento 
    class Momento
    {
        //Orignator declared as friend class
        friend class Orginator;

        //state
        uint8_t state;

        //only orginator can access getstate     
        uint8_t getState()
        {
            return this->state;
        }

        public:
        Momento(uint8_t state)
        {
            this->state = state;
        }
    };

    //Class orginator
    class Orginator
    {
        private:
        //state
        uint8_t state;

        public:
        Orginator()
        {
            state = 0;
        }
        void doSomething()
        {
            state += 1;
        }

        //take snapshot of the state
        Momento* saveState()
        {
            printf("Orginator saved state %d \n",this->state);
            return new Momento(this->state);
        }

        //restore to previous state
        void undo(Momento* momento)
        {
            uint8_t currentState = this->state;
            this->state = momento->getState();
            printf("Orginator restore state current state %d  , restoring state %d \n",currentState, this->state);
        }

    };

    //Caretaker class
    class Caretaker
    {
        private:
        //Momento list
        vector<Momento*> momentoList;

        //orginator object
        Orginator* orginator;

        public:
        Caretaker(Orginator* org)
        {
            this->orginator = org;
        }
        //save the state
        void backup()
        {
            //get the momento from originator and save it to vector
            momentoList.push_back(orginator->saveState());
        }
        
        //Undo or rollback
        void restore()
        {
            if(momentoList.empty())
            {
                cout<<"Caretaker:: momento list is empty "<<endl;                
            }
            else
            {
                //send the momento to orginator
                orginator->undo(momentoList.back());
                //remove the last state from vector
                momentoList.pop_back();
            }            
        }
    };

    void testClientCode()
    {
        Orginator* org = new Orginator();
        Caretaker* caretaker = new Caretaker(org);
        org->doSomething();
        caretaker->backup();
        org->doSomething();
        caretaker->backup();
        org->doSomething();
        caretaker->restore();
        caretaker->restore();
        caretaker->restore();
        caretaker->backup();
    }

}
#endif