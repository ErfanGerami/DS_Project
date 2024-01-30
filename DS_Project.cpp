// DS_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Manager.h"
#include "KDTree.h"
#include "KDTree.h"
using namespace std;
struct s {
    string salam;
    int a;
};
int main()
{
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
        manager.readFromFile(path);
    }
    
    while (1) {
        cout << ">>> ";
        cin >> command;
        try {
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
        }
        catch (const char* err) {
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

