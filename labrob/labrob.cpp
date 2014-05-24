/*  labrob program
    labrob.cpp

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    Programm for sending robots with different search algorithms 
    *  through mazes and then printing stats about their performance.

    * 
    * Status:
    * - wrote function that saves robots to a linked list, which
    * is delcared in the "Mazes" class. Robots have no content yet,
    * so connot fully test this, but the cout output I can generate
    *  suggests this is fine.
    * - the method "exit_search" can be called and generates output
    * - the add_robot method now works both for Robots and for the derived class t1
    * - wrote a "print_robots" method for printing the list; might be
    * used later for going through the list in general (to print stats)

    * 
    * Issues:
    * - need to add error catching in user input (no file results in
    * segmentation fault right now)
    * - need to get the number for the robot type
    * (1, 2, 3, none, which means 1) back from checkuserinput() to main()
    * - need to work on ... something. I'll remember in a second,
    * but I want to push this now.
    * 
	Next steps:
	* - can start working on actual search algorithms?!!!
	* - need some automatised way of deciding which character the robot
	* will write into the labyrinth
	* - need to implement a way for the user to add several robots, and
	* then ask for the output, all of it over command line
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <getopt.h>
#include <unistd.h>
#include "robots.h"
#include "mazes.h"
#include "t1.h"

using namespace std;

void checkuserinput(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    string one_row;
    vector<string> v_maze;

    // create an instance of mazes
    // mazes mazefile;
    // mazes *mymaze = new mazes();

    // move the below from main to checkuserinput
    std::ifstream mazefile (argv[1], std::ifstream::in);

    if (mazefile.is_open())
    {
        while ( getline (mazefile,one_row) )
        {
            v_maze.push_back (one_row);
        }
    }
    mazefile.close();

    Mazes mymaze; //make an instance of mazeses called mymaze
    /*  the v_maze vector is equal to the vector v_maze here in main
		Can move this to a method in mazes, but this is not a priority
	*/
    mymaze.v_maze = v_maze;

    mymaze.add_robot(new t1());

	//add a robot to the list:
	mymaze.add_robot(new Robots());
	// print the cout message in the method "exit_search":
	//mymaze.head->a_robot_in_a_list->exit_search();

	mymaze.print_robots();

/*
	an int saving the robot type (1,2,3, needs to come from 
	* the checkuserinput function. 1 is default
	int robot_type = 1;
*/

    checkuserinput(argc, argv);

    cout << "Our current maze:\n";
    for(unsigned int i=0; i<mymaze.v_maze.size(); i++)
        cout << mymaze.v_maze[i] << endl;

    return 0;
}




void checkuserinput (int argc, char *argv[]) {

    string programname = argv[0];
    string helpmsg = "To send a robot through the labyrinth, \nplease "
                        "enter the filename of the maze you'd like to use\n"
                        "as well as the shortcut of the robot (t1 to t3), "
                        "like so:";

    int getflags;
    string *robot = new string();
    string *maze = new string();

    // print all arguments
    // std::cout << "argc: " << argc << std::endl;
    // for (int i = 0; i < argc; ++i)
    //     std::cout << "argv: "<< argv[i] << std::endl;

    while ((getflags = getopt(argc, (char **)argv, "t:h")) != -1) {

        switch(getflags) {
            case 'h':
                cout << helpmsg << endl; // prints help message
                exit(EXIT_FAILURE);
                break;
            case 't':
                    *robot = optarg;
                    // print number of robot
                    cout << "the robot number is " << *robot << endl;
                break;
        }
    }

    *maze = argv[optind];
    // print name of maze
    // cout << "the maze name is " << *maze << endl;
}


/* 
	create a node for the list (called "list_element")
	and put the robot into the "a_robot_in_a_list" part of the struct
*/
void Mazes::add_robot(Robots *a_robot)
{
	
	list* list_element = new list; //using "new", need to "delete" later
	list_element->a_robot_in_a_list = a_robot;

// Add at the start of the list	
    if (head!=NULL)
    {
        list_element->next = head;
        head = list_element;
    }

    else
    {
        head = list_element;
        list_element->next = NULL;
    }
}


void t1::exit_search()
{
	cout << "Robot of type 1 is looking for an exit" << endl;
}


void Robots::exit_search()
{
	cout << "This robot is looking for an exit" << endl;
}


void Mazes::print_robots(){
    list *travelling_node;
    travelling_node=head;
    while(travelling_node != NULL)
    {
		travelling_node->a_robot_in_a_list->exit_search();
		travelling_node = travelling_node->next;
    }
}
