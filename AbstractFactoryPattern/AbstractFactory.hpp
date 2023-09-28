#ifndef ABSTRACTPATTERN_HPP
#define ABSTRACTPATTERN_HPP

#include <iostream>
using namespace std;

namespace abstractpattern
{
    //Abstract product class
    class Button
    {
        public:
        virtual void draw() =0;
    };
    class Checkbox
    {
        public:
        virtual void draw() =0;
    };

    //concrete product class
    //windows button
    class WindowsButton : public Button
    {
        public:
        void draw() override
        {
            cout<<"Windows button created !!!"<<endl;
        }
    };
    //Mac button
    class MacButton : public Button
    {
        public:
        void draw()  override
        {
            cout<<"MAC button created !!!"<<endl;
        }
    };
    //windows checkbox
    class WindowsCheckbox : public Checkbox
    {
        public:
        void draw() override
        {
            cout<<"Windows Checkbox created !!!"<<endl;
        }
    };
    //Mac checkbox
    class MacCheckbox : public Checkbox
    {
        public:
        void draw() override
        {
            cout<<"MAC Checkbox created !!!"<<endl;
        }
    };

    //Abstract factory class
    class GUIFactory
    {
        public:
        virtual Button* createButton() =0;
        virtual Checkbox* createCheckbox() =0;
    };

    //Concrete factory class

    //Windows
    class WindowsFactory: public GUIFactory
    {
        public:
        Button* createButton()
        {
            return new WindowsButton;
        }
        Checkbox* createCheckbox()
        {
            return new WindowsCheckbox;
        }
    };

    //MAC
    class MacFactory: public GUIFactory
    {
        public:
        Button* createButton()
        {
            return new MacButton;
        }
        Checkbox* createCheckbox()
        {
            return new MacCheckbox;
        }
    };

    //Application class
    class Application
    {
        private:
        GUIFactory* factory; //abstract factory class
        //abstract product class
        Button* button;
        Checkbox* checkbox;

        public:
        //constructor
        Application(GUIFactory* factory)
        {
            this->factory = factory;
            this->button = this->factory->createButton();
            this->checkbox = this->factory->createCheckbox();
        }

        void draw()
        {
            this->button->draw();
            this->checkbox->draw();
        }

    };

    void testClientCode()
    {
        std::string config = "mac";
        //windows widgets
        GUIFactory* factory = nullptr;
        
        if("windows" == config)
        {
            factory = new WindowsFactory;
        }
        else if("mac" == config)
        {
            factory = new MacFactory;
        }
        else{
            //nullptr
        }

        if(nullptr != factory)
        {
            Application* appl = new Application(factory);
            appl->draw();
        }
    }
}
#endif