#ifndef VISITORPATTERN_HPP
#define VISITORPATTERN_HPP

#include <iostream>
#include <vector>
using namespace std;

namespace visitorpattern
{
    //forward declaration
    class Shape;
    class Circle;
    class Square;
    class Dot;
    class Rectangle;

    //interface class
    class visitor
    {
        public:
        virtual void visitCircle(Circle* c) = 0;
        virtual void visitDot(Dot* d) = 0;
        virtual void visitSquare(Square* s) = 0;
        virtual void visitRectangle(Rectangle* r) = 0;
    };
    class visitorShape : public visitor
    {
        public:
        void visitCircle(Circle* c) override
        {
            cout<<"Dumped Circle details "<<endl;
        }
        void visitDot(Dot* d) override
        {
            cout<<"Dumped Dot details "<<endl;
        }
        void visitSquare(Square* s) override
        {
            cout<<"Dumped Square details "<<endl;
        }
        void visitRectangle(Rectangle* r) override
        {
            cout<<"Dumped Rectangle details "<<endl;
        }
    };
    //Element abstract class
    class Shape
    {
        protected:
        int xcord;
        int ycord;
        public:
        virtual void draw() = 0;
        virtual void accept(visitor* v) = 0;
    };

    //element concrete class
    class Circle : public Shape
    {
        public:
        void draw()
        {
            cout<<"circle placed in xcord "<<xcord<<" ycord "<<ycord<<endl;
        }
        void accept(visitor* v)
        {
            v->visitCircle(this);
        }
    };
    class Dot : public Shape
    {
        public:
        void draw()
        {
            cout<<"Dot placed in xcord "<<xcord<<" ycord "<<ycord<<endl;
        }
        void accept(visitor* v)
        {
            v->visitDot(this);
        }
    };
    class Square : public Shape
    {
        public:
        void draw()
        {
            cout<<"Square placed in xcord "<<xcord<<" ycord "<<ycord<<endl;
        }
        void accept(visitor* v)
        {
            v->visitSquare(this);
        }
    };
    class Rectangle : public Shape
    {
        public:
        void draw()
        {
            cout<<"Rectangle placed in xcord "<<xcord<<" ycord "<<ycord<<endl;
        }
        void accept(visitor* v)
        {
            v->visitRectangle(this);
        }
    };

    class ApplicationExport
    {
        private:
        vector<Shape*> shapeList;

        public:
        ApplicationExport()
        {
            shapeList = {new Circle, new Dot, new Rectangle, new Square};            
        }
        void exportInXMLFormat(visitor* v)
        {
            for(Shape* s:shapeList)
            {
                s->accept(v);
            }
        }
    };

    void testClientCode()
    {
        ApplicationExport* appl = new ApplicationExport();
        visitor* visit = new visitorShape;
        appl->exportInXMLFormat(visit);
    }
}
#endif