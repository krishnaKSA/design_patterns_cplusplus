#ifndef PROTOTYPEPATTERN_HPP
#define PROTOTYPEPATTERN_HPP

#include <iostream>
#include <vector>
using namespace std;

namespace prototypepattern
{
    //Prototype class
    class Shape
    {
        private:
        int x;
        int y;
        string color;

        public:
        Shape(int x, int y, string color)
        {
            this->x = x;
            this->y = y;
            this->color = color;
        }
        void setColor(string color)
        {
            this->color = color;
        }
        string getColor()
        {
            return this->color;
        }

        virtual Shape* clone()=0;
    };

    //rectangle class
    class rectangle:public Shape
    {
        private:
        int length;
        int width;

        public:
        rectangle(int len, int wid, int x, int y, string color):Shape(x,y,color)
        {
            length = len;
            width = wid;
        }

        Shape* clone() override
        {
            return new rectangle(*this);
        }

    };

    //circle class
    class circle:public Shape
    {
        private:
        int radius;

        public:
        circle(int radius, int x, int y, string color):Shape(x,y,color)
        {
            this->radius = radius;
        }

        Shape* clone() override
        {
            return new circle(*this);
        }
    };

    //class shapefactory
    class ShapeFactory
    {
        private:
        vector<Shape*> circleList;
        vector<Shape*> rectangleList;
        Shape* pcircle;
        Shape* prectangle;

        public:
        ShapeFactory()
        {
            pcircle = new circle(10,1,2,"red");
            prectangle = new rectangle(10,20,1,2,"red");
        }
        void buildDifferntColorShapes(string color)
        {
            circleList.push_back(pcircle->clone());
            circleList.back()->setColor(color);
            rectangleList.push_back(prectangle->clone());
            rectangleList.back()->setColor(color);
        }

        void printList()
        {
            for(Shape* p:circleList)
            {
                printf("object color=%s \n",p->getColor().c_str());
            }
        }
    };

    void testPrototypePattern()
    {
        ShapeFactory* factory = new ShapeFactory;
        factory->buildDifferntColorShapes("green");
        factory->buildDifferntColorShapes("yellow");
        factory->buildDifferntColorShapes("purple");
        factory->buildDifferntColorShapes("white");
        factory->buildDifferntColorShapes("black");
        factory->buildDifferntColorShapes("pink");
        factory->buildDifferntColorShapes("maroon");
        factory->printList();
    }
}

#endif