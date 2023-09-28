#ifndef TEMPLATEMETHOD_HPP
#define TEMPLATEMETHOD_HPP

#include <iostream>
using namespace std;

namespace templatemethod
{
    //template class
    class CSort
    {    
        void processArray()
        {
            cout<<"CSort: "<<__FUNCTION__<<endl;
        }
        
        void printArray()
        {
            cout<<"CSort: "<<__FUNCTION__<<endl;
        }

        public:
        virtual void sortArray() final
        {
            processArray();
            compare();
            printArray();
        }

        virtual void compare() = 0;        
    };

    class CBubbleSort :  public CSort
    {
        public:
        void compare()
        {
            cout<<"CBubbleSort: "<<__FUNCTION__<<endl;
        }

    };
    class CSelectionSort :  public CSort
    {
        public:
        void compare()
        {
            cout<<"CSelectionSort: "<<__FUNCTION__<<endl;
        }
    };
    class CQuickSort :  public CSort
    {
        public:
        void compare()
        {
            cout<<"CQuickSort: "<<__FUNCTION__<<endl;
        }
    };

    void testTemplateMethod()
    {
        CSort* qSort = new CQuickSort;
        qSort->sortArray();
        CSort* bSort = new CBubbleSort;
        bSort->sortArray();
        CSort* sSort = new CSelectionSort;
        sSort->sortArray();
    }
}
#endif