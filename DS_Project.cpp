// DS_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Manager.h"
#include "KDTree.h"
#include "KDTree.h"
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>

void setcolor(int ForgC) 
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
using namespace std;
struct s {
    string salam;
    int a;
};
int main()
{
    setcolor(2);
    
    bool new_time = true;
    Manager manager;
    string command="";
    while (command != "Y" && command != "N") {
        cout << "do you want to read data from file?(Y,N)";
        cin >> command;
    }
    if (command == "Y") {
        string path;
        cout << "path: ";
        cin >> path;
        try {
            manager.readFromFile(path);
        }
        catch (const char* err) {
            //pass 
        }
    }
    
    while (1) {

        if (new_time) {
            setcolor(1);
            cout << manager.get_currBranch() << "(" << manager.get_time() << ")" << ">>> ";
        }
        setcolor(6);
        cin >> command;
        try {
            int time,subtime;
            int top, bottom, right, left;
            int x, y;
            float R;
            string name, individual_name,path;
            if (command == "Add-P") {
                cin >> x >> y >> name;
                manager.addStore(Store({ x,y }, name, true), new_time);



            }
            else if (command == "Add-Br") {
                cin >> x >> y >> name >> individual_name;
                try {
                    manager.addStore(Store({ x,y }, name, individual_name, false), new_time);
                    int x=1;
                    x *= 2;
                }
                catch (const char* err) {
                    cout << err << endl;
                }

            }
            else if (command == "Del-Br") {
                try {
                    cin >> x >> y;
                    manager.deleteByCoo(x, y, new_time);
                }
                catch (const char  err) {
                    cout << err << endl;
                }
            }
            else if (command == "List-P") {
                cin >> name;
                manager.printInNeighbor(name);

            }
            else if (command == "List-Brs") {
                cin >> name;
                manager.printAllBranches(name);
            }
            else if (command == "Near-P") {
                cin >> x >> y;
                manager.printNearest(x, y);
            }
            else if (command == "Near-Br") {
                cin >> x >> y >> name;
                manager.printNearestBranch(name, x, y);

            }
            else if (command == "Avail-P") {
                cin >> x >> y >> R;
                manager.printAllInRange(x, y, R);

            }
            else if (command == "Most-Brs") {
                manager.printLargest();
            }
            else if (command == "Add-N") {
                cin >> top >> right >> bottom >> left;
                cin >> name;
                manager.addNeighborhood(Neighborhood(name, left, right, top, bottom), new_time);
            }
            else if (command == "List-P") {
                cin >> name;
                manager.printInNeighbor(name);
            }
            else if (command == "write") {
                cin >> path;
                manager.writeInFile(path);
            }
            else if (command == "exit") {
                exit(0);
            }
            else if (command == "Undo") {
                cin >> time>>subtime;

                string branch_name = "master";
                cin >> branch_name;
                manager.changeTimeOrBranch(time, subtime, branch_name);
            }
            else if (command == "branch") {
                cin >> name;
                manager.create_branch(name);
            }
            else if (command == "List-Branches") {
                manager.printAllBranches();
            }
            else if (command == "time") {
                cin >> time;
                manager.printTimeStat(time);

            }
           /* else if (command == "Check-Out") {
                cin >> name >> time >> subtime;
               manager.changeTimeOrBranch(time,subtime,branch)
            }*/
            else if(command!="&&") {
                throw  "unknown command";
            }
        }
        catch (const char* err) {
            setcolor(4);
            cout << err<<endl;
        }
        new_time = true;
        if (command == "&&") {
            new_time = false;
        }
        
    }
    /*manager.addStore(Store({1,2}, "1", 0));
    manager.addStore(Store({ 0,3 }, "2", 1));
    manager.addStore(Store({ 1,4 }, "2", 1));
    manager.addStore(Store({ 1,1 }, "3", 1));
    manager.addStore(Store({ 1,2 }, "4", 1));
    manager.addStore(Store({ 1,10 }, "4", 0));
    manager.addStore(Store({ -1,2 }, "4", 1));
    manager.addStore(Store({ 2,4 }, "5", 1));
    manager.addStore(Store({ 1,1 }, "6", 1));
    //manager.printNearest(1, 1);
    manager.DEBUG();*/
   // manager.printCooByName("4");
    //manager.printKDTree_DEBUG();

    /*string commmand;
    Vector<string> vec;
    bool add = false;;
    while (cin>>commmand) {
        if (commmand=="&&") {
            add = true;
        }
        else {
            vec.push(commmand);

        }


    }*/

}

