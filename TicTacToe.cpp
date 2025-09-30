/*
 *
 * Use C++ and only it's standard library to create Tic Tac Toe
 * By @ReactivePlayZ
 * Finished this project initially on 25/09/2025 @ 4:20am (In 2 hours).
 * To-Do: Bug fixes (If any) and Commenting/Documenting and definitely optimization.
 *
 */
#include <iostream>
#include <cstdlib> // Needed for random values
#include <ctime> // To actually make them random each time
using std::cout; using std::cin; using std::endl;

void showGrid(char grid[3][3]) {
    for (int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << "[" << grid[i][j] << "]"; 
        }
        cout << endl;
    }
    cout << "^ Here's the grid." << endl;
}

char swapPlayers(char currentPlayer, char p1, char p2) {
    if (currentPlayer == p1) { return p2; }
    else { return p1; }
}

bool winConditionForPlayer(char grid[3][3], char p1) {
    /*
     * p1 is current player and checks if the winning conditions
     * of 3 in a row horizontally, vertically, or diagonally is met.
     * Will update later to be a loop instead.
     */
    if(grid[0][0] == p1 && grid[0][1] == p1 && grid[0][2] == p1) { return true; }
    if(grid[1][0] == p1 && grid[1][1] == p1 && grid[1][2] == p1) { return true; }
    if(grid[2][0] == p1 && grid[2][1] == p1 && grid[2][2] == p1) { return true; }
    if(grid[0][0] == p1 && grid[1][1] == p1 && grid[2][2] == p1) { return true; }
    if(grid[0][2] == p1 && grid[1][1] == p1 && grid[2][0] == p1) { return true; }
    return false;
}

bool tieChecker(char grid[3][3]) {
    // Only checks and returns true if the board is filled out (Will improve later)
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(grid[i][j]==' ') { return false; }
        }
    }
    return true;
}

/*
 *
 * Additional Tasks:
 * (If needed) ignore limiting yourself to just the standard library.
 * Create a bot player to play against the user.
 * 
 * Optional Task:
 * Make the grid scalable (3x3 -> 4x4, 5x5, 6x6, etc)
 * 
 */

int emptyWinPos(char grid[3][3], char p) {
    // Returns the next move to win (rather the move that should be blocked by opponent of p)
    // Otherwise returns 0
    // Doesn't check diagonals for now
    int count; int countY;
    int emptyPos; int emptyPosY;
    for (int i=0; i<3; i++) {
        count = 0;
        countY = 0;
        for (int j=0; j<3; j++) {
            if (grid[i][j]==p) { count++; }
            else if (grid[i][j]==' ') { emptyPos=j; }
            else { count = 0; }

            if (grid[j][i]==p) { countY++; }
            else if (grid[j][i]==' ') { emptyPosY=j; }
            else { countY = 0; } 

            if (j==2 && countY>1) {
                return (i + 1) + (emptyPosY * 3);
            }
        }
        if (count>1) {
            return (emptyPos + 1) + (i * 3);
        }
    }
    return 0;
}

int nextBestMove(char grid[3][3], char player, char opp, int turns) {
    int win = emptyWinPos(grid, player);
    if (win!=0) { return win; }
 
    int block = emptyWinPos(grid, opp);
    if (block!=0) { return block; }
 
    if (turns==8 && grid[1][1]!=opp) { return 5; }
    else if (turns==8 && grid[1][1]==opp) { return 1; }
    else if (turns==9) { return 5; }

    int pos;
    int row;
    int col;
    do {
        pos = (rand() % 9)+1;
        row = (pos - 1) / 3;
        col = (pos - 1) % 3;
    } while(grid[row][col]!=' ');
    return pos;
}

void play() {
    const char p1 = 'X'; // Players 1 and 2 abbreviated to p1 and p2
    const char p2 = 'O';
    char grid[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    cout << "[1][2][3]\n[4][5][6]\n[7][8][9]" << endl;
    cout << "These are the positions, pick a position to play." << endl;
    char choice;
    cout << "Enable bot opponent? (y/n - defaults to y): ";
    cin >> choice;
    if (choice!='n') {
        choice = 'y';
    }
    const bool bot = (choice=='y') ? true : false;
    int turns = 9;
    int pos = 0;
    char currentPlayer = p2;
    int row;
    int col;
    bool incorrect = false;
    while (turns>0) {
        if (incorrect==true) {
            turns++;
            currentPlayer = swapPlayers(currentPlayer, p1, p2);
            if (pos<1 || pos>9) { cout << "Invalid choice, go again" << endl; }
            incorrect = false;
        }
        if (turns==0) { break; }
        currentPlayer = swapPlayers(currentPlayer, p1, p2);
        cout << endl;
        showGrid(grid);
        cout << "Current Player: " << currentPlayer << endl;
        cout << currentPlayer << " | Squares left: " << turns << " | input: ";

        if (bot && currentPlayer==p2) {
            pos = nextBestMove(grid, p2, p1, turns);
            cout << pos << endl;
        } else {
            while (!(cin >> pos)) {
                cout << "Please enter a valid move (1-9): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        // convert pos to array pos
        row = (pos - 1) / 3;
        col = (pos - 1) % 3;
        if (grid[row][col]==' ') { grid[row][col] = currentPlayer; }
        else {
            cout << "Please pick one of the free squares within 1-9." << endl;
            incorrect = true;
        }
        
        if (winConditionForPlayer(grid, currentPlayer)) { break; }
        if (tieChecker(grid)) { break; }
        turns--;
    };
    if (winConditionForPlayer(grid, p1)) { cout << p1 << " Won!" << endl; }
    else if (winConditionForPlayer(grid, p2)) { cout << p2 << " Won!" << endl; } 
    else { cout << "It's a tie!" << endl; }
    showGrid(grid);
}

int main() {
    srand(time(0));
    cout << "Welcome to Tic Tac Toe!" << endl;
    char again = 'n';
    do {
        play();
        cout << "Play again? (y/n - defaults to n): ";
        cin >> again; cout << endl;
        if (again!='y') { again = 'n'; }
    }
    while (again=='y');

    return 0;
}