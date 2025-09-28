/*
 *
 * Use C++ and only it's standard library to create Tic Tac Toe
 * By @ReactivePlayZ
 * Finished this project initially on 25/09/2025 @ 4:20am (In 2 hours).
 * To-Do: Bug fixes (If any) and Commenting/Documenting and definitely optimization.
 *
 */
#include <iostream>
using namespace std;

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
    /* p1 is current player and checks if the winning conditions
       of 3 in a row horizontally, vertically, or diagonally is met. */
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

int main() {
    char p1 = 'X'; // Players 1 and 2 abbreviated to p1 and p2
    char p2 = 'O';
    char grid[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    cout << "[1][2][3]\n[4][5][6]\n[7][8][9]" << endl;
    cout << "These are the positions, pick a position to play." << endl;
    int turns = 9;
    int pos = 0;
    char currentPlayer = p2;
    bool incorrect = false;
    cout << "Current player: " << currentPlayer << endl;
    while (turns>0) {
        if (incorrect==true) {
            turns++;
            currentPlayer = swapPlayers(currentPlayer, p1, p2);
            if (!pos<1 || !pos>9) { cout << "Invalid choice, go again" << endl; }
            incorrect = false;
        }
        if (turns==0) { break; }
        currentPlayer = swapPlayers(currentPlayer, p1, p2);
        showGrid(grid);
        cout << currentPlayer << " | Turns left: " << turns << " | input: ";
        cin >> pos; cout << endl;
        switch(pos) {
            // Way too cluttered at the moment, maybe needs some optimization and rewording
            case 1:
                if(grid[0][0]==' ') {
                    grid[0][0] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 2:
                if(grid[0][1]==' ') {
                    grid[0][1] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 3:
                if(grid[0][2]==' ') {
                    grid[0][2] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 4:
                if(grid[1][0]==' ') {
                    grid[1][0] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 5:
                if(grid[1][1]==' ') {
                    grid[1][1] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 6:
                if(grid[1][2]==' ') {
                    grid[1][2] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 7:
                if(grid[2][0]==' ') {
                    grid[2][0] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 8:
                if(grid[2][1]==' ') {
                    grid[2][1] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            case 9:
                if(grid[2][2]==' ') {
                    grid[2][2] = currentPlayer;
                } else {
                    incorrect = true;
                } break;
            default:
                cout << "Please pick one of the free squares within 1-9." << endl;
                incorrect = true;
        }
        
        if (winConditionForPlayer(grid, p1)) { break; }
        if (tieChecker(grid)) { break; }
        turns--;
    };
    if (winConditionForPlayer(grid, p1)) { cout << p1 << " Won!" << endl; }
    else if (winConditionForPlayer(grid, p2)) { cout << p2 << " Won!" << endl; } 
    else { cout << "It's a tie!" << endl; }
    showGrid(grid);
    return 0;
}

/*
 *
 * Additional Tasks:
 * (If needed) ignore limiting yourself to just the standard library.
 * Create a bot player to play against the user.
 * 
 */