#ifndef FLYWEIGHTPATTERN_HPP
#define FLYWEIGHTPATTERN_HPP

#include <iostream>
#include <unordered_map>
#include <stdint.h>
using namespace std;

/*Problem:
you are working on the open game application. In this application , you need to show trees on the green land.

There are two types of the trees. 1. Green 2. Brown.

Tree has the attributes of "color", "height", and position of the tree. 

To store color you can use char variable like 'G', 'B'. height is int variable. X, Y corodinates are uint16_t variables 
char 1 byte , height 2 bytes
*/

namespace flyweight
{
    //flyweight
    class Tree
    {
        private:
        //intrinsic state
        string color;
        int height;

        public:
        Tree(string color)
        {
            this->color = color;
            height = 10;
        }
        void draw(int x_pos, int y_pos)
        {
            cout <<"Using object "<<this<< " Tree with color  " << this->color<<" and height "<< height << " placed in this X,Y position  " << x_pos << " " << y_pos << endl;
        }
    };

    //Flyweight factory class
    class TreeFactory
    {
        private:
        std::unordered_map<string, Tree*> objectPools; //cache

        public:
        //constructor
        TreeFactory()
        {
            objectPools =  std::unordered_map<string, Tree*>();
        }
        Tree* getTree(string color)
        {
            Tree* object = nullptr;
            //check whether the tree is in object pool
            auto iterator = objectPools.find(color);
            if(iterator != objectPools.end())
            {
                object = iterator->second;
            }
            else{
                //create new Tree object with specific intrinsic states
                object = new Tree(color);
                objectPools[color] = object;
                return object;
            }
            return object;
        }
    };

    class Game
    {
        private:
        TreeFactory *factory;
        public:
        Game()
        {
            factory =new TreeFactory;
        }
        void plantTrees(string color, int X, int Y)
        {
            factory->getTree(color)->draw(X, Y);    
        }
    };

    void testFlyweightPattern()
    {
        Game* game = new Game;
        game->plantTrees("green", 10, 20);
        game->plantTrees("brown", 34, 100);
        game->plantTrees("brown", 40, 89);
        game->plantTrees("green", 112, 56);
        game->plantTrees("green", 34, 78);
        game->plantTrees("green", 45, 23);
        game->plantTrees("brown", 89, 56);
        game->plantTrees("green", 12, 67);
        game->plantTrees("brown", 78, 90);

    }
}
#endif