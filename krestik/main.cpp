#include <iostream>
#include <stdio.h>
#include <cstdlib>

/**
@file main.cpp
*/
/**
@mainpage Application for play tic tac toe
Tasks:
- learning strategies
- have fun

\authors
Spekll
\version
0.0.1
*/

using namespace std;

void output(char** field) {
    cout << "  1 2 3" << endl; // outputs the column numbers
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " "; // outputs the row number
        for (int j = 0; j < 3; j++) {
            cout << field[i][j] << " "; // outputs the elements of the 2D array representing the game field
        }
        cout << endl;
    }
}
/**
 \brief Function responsible for the main gameplay

 \details
 Sets the value in the array and changes the player

 */
void input(char** field, bool& gamer, string& Name1, string& Name2) {

    int answer;
    while (true) {

        if (gamer) {
            cout << Name1; // outputs the name of the first player
        }
        else {
            cout << Name2; // outputs the name of the second player
        }
        cout << ", enter row and column number: ";


        cin >> answer; // reads the player's input
        if (answer > 10 && answer < 34) { // checks if the input is within a valid range
            int i = answer / 10; // calculates the row number
            int j = answer % 10; // calculates the column number

            if (0 < j && j < 4) { // checks if the column number is within a valid range
                if (field[i - 1][j - 1] != 'X' && field[i - 1][j - 1] != 'O') { // checks if the selected cell is empty
                    if (gamer) {
                        field[i - 1][j - 1] = 'X'; // assigns 'X' to the selected cell for the first player
                    }
                    else {
                        field[i - 1][j - 1] = 'O'; // assigns 'O' to the selected cell for the second player
                    }
                    gamer = !gamer; // switches the current player
                    break;
                }
            }
        }
        cout << "Wrong section" << endl; // outputs an error message if the input is invalid
    }
}
/**
\brief Array initiation


 \return field (dinamically 2d array)
 */

char** fieldCreate(char c = '_') {
    int const n = 3;
    char** field = new char* [n]; // dynamically allocates memory for an array of pointers to char
    for (int i = 0; i < n; i++) {
        field[i] = new char[n]; // dynamically allocates memory for each row of the 2D array
        field[i][0] = c; // initializes the first column with the specified character
        field[i][1] = c; // initializes the second column with the specified character
        field[i][2] = c; // initializes the third column with the specified character
    }
    return field; // returns the dynamically created 2D array
}
/**
 \brief Winner check

 \details
 Checks whether one of the players has won at the moment of  the move

 \return outputs the result of game
 */

bool chekWin(char** field, string& Name1, string& Name2) {
    bool chekWin = false, gamer = false;

    if (field[0][0] == field[1][1] && field[0][0] == field[2][2] && (field[0][0] == 'X' || field[0][0] == 'O') || field[2][0] == field[1][1] && field[2][0] == field[0][2] && (field[2][0] == 'X' || field[2][0] == 'O')) {
        chekWin = true; // sets the win flag to true
        if (field[1][1] == 'X') {
            gamer = true; // sets the winning player to player 1
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (field[i][0] == field[i][1] && field[i][0] == field[i][2] && (field[i][0] == 'X' || field[i][0] == 'O') || field[0][i] == field[1][i] && field[0][i] == field[2][i] && (field[0][i] == 'X' || field[0][i] == 'O')) {
                chekWin = true; // sets the win flag to true
                if (field[i][i] == 'X') {
                    gamer = true; // sets the winning player to player 1
                }
                break;
            }
        }
    }

    if (chekWin) {
        if (gamer) {
            cout << "winner !" << Name1 << endl; // outputs the winner's name
        }
        else {
            cout << "winner  !" << Name2 << endl; // outputs the winner's name
        }
        return true; // returns true indicating the game is over
    }
    else {
        bool draw = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] != 'X' && field[i][j] != 'O') {
                    draw = false; // sets the draw flag to false if there is still an empty cell
                }
            }
        }

        if (draw) {
            cout << "draw" << endl; // outputs a message that the game ended in a draw
            return true; // returns true indicating the game is over
        }
    }

    return false; // returns false indicating the game is not over yet
}
/**
 \brief Generating default array

 \details
 Generate 2d playing field array with "_"

 */

void defoultMassive(char** field, char c = '_') {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            field[i][j] = c; // initializes each cell of the 2D array with the specified character
        }
    }
}
/**
 \brief Game Restarting

 \details
 Asks players if they want to play again

 \return flag - user's decision
 */

bool continueGame() {
    bool flag = true;
    while (true) {
        string answer;
        cout << "One more game?(Y/N)" << endl << "Enter answer: "; // prompts the user to enter their answer
        cin >> answer; // reads the user's answer
        if (answer == "Y") {
            break; // breaks out of the loop in case of a positive answer
        }
        else if (answer == "N") {
            flag = false; // sets the flag to false in case of a negative answer
            break; // breaks out of the loop
        }
        else {
            cout << "What is it?!"; // outputs an error message for an invalid answer
        }
    }
    return flag; // returns the user's decision
}
/**
 \brief Array clearing
 */

void deleteMassive(char** field) {
    for (int i = 0; i < 3; i++) {
            delete[] field[i]; // deallocates memory for each row of the 2D array
    }
    delete[] field; // deallocates memory for the array of pointers
}
/**
 \brief Player random

 \details
 The function generates random numbers to swap sequence of moves

 */

void randomPlayer(string& Name1, string& Name2) {
    srand(time(NULL)); // seeds the random number generator
    int num = rand() % 2; // generates a random number either 0 or 1
    cout << "First player name: "; // prompts the user to enter the first player's name
    cin >> Name1; // reads the first player's name
    cout << "Second player name: "; // prompts the user to enter the second player's name
    cin >> Name2; // reads the second player's name
    if (num) {
        string tmp = Name1;
        Name1 = Name2;
        Name2 = tmp; // swaps the players' names based on the random number generated
    }
    cout << "First turn: " << Name1 << endl; // outputs the name of the player who goes first
}
/**
 \brief Application entry point

 \details
 The main function of the application.

 */

int main() {

    bool gamer = true; // initializes the player flag to player 1
    char** field = fieldCreate(); // creates the game field
    string Name1, Name2;
    randomPlayer(Name1,Name2); // assigns the players' names and decides who goes first
    while (true) {
       defoultMassive(field); // initializes the game field
        while (true) {

            output(field); // outputs the current state of the game field
            if (chekWin(field, Name1, Name2)) // checks if there is a winner or a draw
                break;
            input(field, gamer, Name1, Name2); // takes the player's input for their move

        }
        if (!continueGame()) // checks if the players want to continue the game
            break;
    }
    deleteMassive(field); // deallocates memory for the game field
    return 0; // returns 0 to indicate successful program execution
}
