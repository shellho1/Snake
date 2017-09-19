/*
	C++ Snake Console Game for Windows OS
	by Weston Shellhorn
	Summer 2016
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <conio.h>

void start();
void print_grid();
void initialize();
void move(int dx, int dy);
void update();
void cdirect(char key);
void clear();
void create_goal();
char translate(int value);

/*
	---Global Variables---
	Todo: reduce by either creating class and using getters/setters
		  or passing via functions
*/

// grid dimensions
const int WIDTH = 20;
const int HEIGHT = 20;
const int SIZE = WIDTH * HEIGHT;

// Initialize grid
int grid[SIZE];

// Snake info
int x_pos;
int y_pos;
int direction;

// Starting value of snake
int goal = 3;

// flag that determines if game is running
bool flag;

int main() {
	cout << "\t\t================== Snake Tutorial ====================" << endl;
	cout << "\t\tUse WASD keys to move the snake and collect 'x'" << endl;
	cout << endl;
	cout << "\t\t==================== Game Start =======================" << endl;
	cout << "\t\tWould you like to play? [y/n]: ";
	char play='n';
	cin >> play;
	if (play == 'y'){
		clear();
		start();
	}
	else {
		cout << "Exiting game..." << endl;
		cin.ignore();
	}
	
	return 0;
}

void start() {
    // Initialize the grid
    initialize();
    flag = true;
    while (flag) {
        // If a key is pressed
        if (kbhit()) {
            // Change to direction determined by key pressed
            cdirect(getch());
        }
        //Update, clear, and then print the grid followed by a .5 second delay
        update();
        clear();
        print_grid();
        _sleep(500);
    }

    cout << "\t\tGame Over" << endl << "\t\tYour score is: " << goal;

    // Prevent console from closing
    std::cin.ignore();
}

void initialize()
{
    // Places the initual head location in middle of grid
    x_pos = WIDTH / 2;
    y_pos = HEIGHT / 2;
    grid[x_pos + y_pos * WIDTH] = 1;

    // Places top and bottom walls 
    for (int x = 0; x < WIDTH; ++x) {
        grid[x] = -1;
        grid[x + (HEIGHT - 1) * WIDTH] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < HEIGHT; y++) {
        grid[0 + y * WIDTH] = -1;
        grid[(WIDTH - 1) + y * WIDTH] = -1;
    }

    // Generates first goal
    create_goal();
}

void cdirect(char key) {
    /*
    	Key:
    		W = 1
    		D = 2
    		S = 3
    		A = 4
    */
    switch (key) {
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 4) direction = 2;
        break;
    case 'a':
        if (direction != 5) direction = 3;
        break;
    }
}

void move(int dx, int dy) {
    // determine new head position
    int newx = x_pos + dx;
    int newy = y_pos + dy;

    // Check if there is goal at location
    if (grid[newx + newy * WIDTH] == -2) {
        goal++; //increase length (score)
        create_goal(); //generate new goal on grid
    }

    // is location available? No? Game over
    else if (grid[newx + newy * WIDTH] != 0) {
        flag = false;
    }

    // Move head to new location
    x_pos = newx;
    y_pos = newy;
    grid[x_pos + y_pos * WIDTH] = goal + 1;

}

void clear() {
    system("cls"); //system call to clear the screen
}

void create_goal() {
	//generate random x,y values within grid boundaries
    int x = rand() % (WIDTH - 2)+1;
    int y = rand() % (HEIGHT -2)+1;
    
    //loop until both x,y are available
	while (grid[x + y * WIDTH] != 0){
        x = rand() % (WIDTH - 2) + 1;
        y = rand() % (HEIGHT - 2) + 1;

    } 
    
    // set new goal
    grid[x + y * WIDTH] = -2;
}

void update() {
    // Based on direction send values to move function
    switch (direction) {
    case 0: move(-1, 0);
        break;
    case 1: move(0, 1);
        break;
    case 2: move(1, 0);
        break;
    case 3: move(0, -1);
        break;
    }

    // Reduce snake values on grid by 1
    for (int i = 0; i < SIZE; i++) {
        if (grid[i] > 0){
			grid[i]--;
    	}
	}
}

void print_grid()
{
	cout << endl;
	cout << "\t\tSnake Game" << endl;
	cout << endl;
    for (int x = 0; x < WIDTH; ++x) {
    	cout << "\t";
        for (int y = 0; y < HEIGHT; ++y) {
            // Prints the value at current x,y location
            cout << translate(grid[x + y * WIDTH]);
        }
        // Ends the line for next x value
        cout << endl;
    }
}

char translate(int value) {
    // Returns a part of snake body
    if (value > 0) {
		return 'o';
	}
	
    switch (value) {
    	case -1: return '%'; //border
    	case -2: return 'x'; //goal
    
    }
}


