#include <iostream>
#include <stdio.h>
#include <cstdlib>


using namespace std;

void output(char** field) {
    cout << "  1 2 3" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}
void input(char** field, bool& gamer, string& Name1, string& Name2) {

    int answer;
    while (true) {

        if (gamer) {
            cout << Name1;
        }
        else {
            cout << Name2;
        }
        cout << ", enter row and column number: ";


        cin >> answer;
        if (answer > 10 && answer < 34) {
            int i = answer / 10;
            int j = answer % 10;

            if (0 < j && j < 4) {
                if (field[i - 1][j - 1] != 'X' && field[i - 1][j - 1] != 'O') {
                    if (gamer) {
                        field[i - 1][j - 1] = 'X';
                    }
                    else {
                        field[i - 1][j - 1] = 'O';
                    }
                    gamer = !gamer;
                    break;
                }
            }
        }
        cout << "Wrong section" << endl;
    }
}
char** fieldCreate(char c = '_') {
    int const n = 3;
    char** field = new char* [n];
    for (int i = 0; i < n; i++) {
        field[i] = new char[n];
        field[i][0] = c;
        field[i][1] = c;
        field[i][2] = c;
    }
    return field;
}
bool chekWin(char** field, string& Name1, string& Name2) {
    bool chekWin = false, gamer = false;

    if (field[0][0] == field[1][1] && field[0][0] == field[2][2] && (field[0][0] == 'X' || field[0][0] == 'O') || field[2][0] == field[1][1] && field[2][0] == field[0][2] && (field[2][0] == 'X' || field[2][0] == 'O')) {
        chekWin = true;
        if (field[1][1] == 'X') {
            gamer = true;
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (field[i][0] == field[i][1] && field[i][0] == field[i][2] && (field[i][0] == 'X' || field[i][0] == 'O') || field[0][i] == field[1][i] && field[0][i] == field[2][i] && (field[0][i] == 'X' || field[0][i] == 'O')) {
                chekWin = true;
                if (field[i][i] == 'X') {
                    gamer = true;
                }
                break;
            }
        }
    }

    if (chekWin) {
        if (gamer) {
            cout << "winner !" << Name1 << endl;
        }
        else {
            cout << "winner  !" << Name2 << endl;
        }
        return true;
    }
    else {
        bool draw = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] != 'X' && field[i][j] != 'O') {
                    draw = false;
                }
            }
        }

        if (draw) {
            cout << "draw" << endl;
            return true;
        }
    }

    return false;
}
void defoultMassive(char** field, char c = '_') {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            field[i][j] = c;
        }
    }
}
bool continueGame() {
    bool flag = true;
    while (true) {
        string answer;
        cout << "One more game?(Y/N)" << endl << "Enter answer: "; //<< answer;
        cin >> answer;
        if (answer == "Y") {
            break;
        }
        else if (answer == "N") {
            flag = false;
            break;
        }
        else {
            cout << "What is it?!";
        }
    }
    return flag;
}
void deleteMassive(char** field) {
    for (int i = 0; i < 3; i++) {
            delete[] field[i];
    }
    delete[] field;
}
void randomPlayer(string& Name1, string& Name2) {
    srand(time(NULL));
    int num = rand() % 2;
    cout << "First player name: ";
    cin >> Name1;
    cout << "Second player name: ";
    cin >> Name2;
    if (num) {
        string tmp = Name1;
        Name1 = Name2;
        Name2 = tmp;
    }
    cout << "First turn: " << Name1 << endl;
}

int main() {

    bool gamer = true;
    char** field = fieldCreate();
    string Name1, Name2;
    randomPlayer(Name1,Name2);
    while (true) {
       defoultMassive(field);
        while (true) {

            output(field);
            if (chekWin(field, Name1, Name2))
                break;
            input(field, gamer, Name1, Name2);

        }
        if (!continueGame())
            break;
    }
    deleteMassive(field);
    return 0;
}
