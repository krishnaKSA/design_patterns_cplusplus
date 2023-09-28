#ifndef COMPOSITEPATTERN_HPP
#define COMPOSITEPATTERN_HPP

#include <iostream>
#include <vector>
using namespace std;

//Example:: List the directories name and file name under the given folder
namespace compositepattern
{
    //Component class
    class AbstractFile
    {
        public:
        virtual void listFiles() = 0;
    };

    //Leaf class
    class File :  public AbstractFile
    {
        private:
        string fileName;
        public:
        File(string name)
        {
            fileName  = name;
        }
        void listFiles() override
        {
            cout<<fileName<<endl;
        }
    };

    //Composite class
    class Directory :  public AbstractFile
    {
        private:
        string fileName;
        vector<AbstractFile*> fileList;
        public:
        Directory(string name)
        {
            fileName  = name;
            fileList = vector<AbstractFile*>();
        }
        void add(AbstractFile* obj)
        {
            fileList.push_back(obj);
        }
        void listFiles() override
        {
            cout<<fileName<<endl;
            for(AbstractFile* obj:fileList)
            {
                obj->listFiles();
            }            
        }
    };

    void testClientCode()
    {
        Directory* one = new Directory("Folder1");
        Directory* two = new Directory("Folder2");
        Directory* three = new Directory("Folder3");

        File* fone =new File("File 1");
        File* ftwo =new File("File 2");
        File* fthree =new File("File 3");
        File* ffour =new File("File 4");
        File* ffive =new File("File 5");
        File* fsix =new File("File 6");
        File* fseven =new File("File 7");

        one->add(fone);
        one->add(ftwo);
        two->add(fthree);
        two->add(ffour);
        three->add(ffive);
        three->add(fsix);
        three->add(fseven);
        one->add(two);
        two->add(three);
        one->listFiles();
    }

}
#endif
