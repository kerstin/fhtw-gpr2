#ifndef MAZES_H
#define MAZES_H


class robots{
public:	
	char robotcharacter;	// character the robot draws on the labyrinth,
							// has to be accessible from outside
private:
	void exit_search(); // function that will contain the search algorithm
};

#endif // MAZES_H