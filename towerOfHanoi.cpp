#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

//Prints the state of one of the poles for a certain height
void printLevel(const vector<int>& pole, int level, int height) {
    if (level >= 0 && level < pole.size()) {
        int disk = pole[level];
        cout << setw(height - disk) << "" 
             << string(disk * 2 + 1, '=') 
             << setw(height - disk) << "";
    } else {
        cout << setw(height + 1) << "|" << setw(height) << "";
    }
}

//main
int main(){
    //variables
    int ringCount;
    string move;

    //gets difficulty level
    while (true){
        system("cls");
        cout << "Tower of Hanoi is a game where you move all the rings from the first pole to the third\n";
        cout << "You can only move 1 ring at a time and you cant place larger rings on smaller ones\n";
        cout << "Enter an amount of rings to play with(3-8): ";
        cin >> ringCount;
        
        //input validate
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (ringCount >= 3 && ringCount <= 8) {
            break; 
        } 
    }


    // some more variables
    bool explain = false;
    int moveCount = 0;
    int minimumMoves = (1 << ringCount) - 1;

    vector<int> pole1;
    vector<int> pole2;
    vector<int> pole3;
    
    //places the rings
    for (int i = ringCount; i>0;i--){
        pole1.push_back(i);
    }

    //main game loop
    while(true){
        system("cls");
        // print state
        cout << setw(ringCount + 1) << "|" << setw(ringCount) << "";
        cout << setw(ringCount + 1) << "|" << setw(ringCount) << "";
        cout << setw(ringCount + 1) << "|" << setw(ringCount) << "\n";
        for (int i = ringCount - 1; i >= 0; i--) {
            printLevel(pole1,i,ringCount);
            printLevel(pole2,i,ringCount);
            printLevel(pole3,i,ringCount);
            cout << "\n";
        }
        cout << string(ringCount*7,'-') <<"\n";

        //win con
        if (pole3.size() == ringCount && pole1.empty() && pole2.empty()) {
            cout << "You win!!!!!\n";
            break;
        }

        //moving
        if (explain == false){
            explain = true;
            cout << "Send move with two digits, first denoting source, second destination, example:13\n";
        }
        cout << "Minimum moves (" << minimumMoves << "), moves count: " << moveCount << "\n";
        cout << "Enter your move: ";
        cin >> move;
        
        //input validate
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            explain = false;
            continue;
        }
        if (move.size() != 2) {
            explain = false;
            continue;
        }
        int source = move[0] - '0';
        int dest = move[1] - '0';
        if (source < 1 || source > 3 || dest < 1 || dest > 3 || source == dest) {
            explain = false;
            continue;
        } 
        
        // Attempt move
        vector<int> *from, *to;

        if (source == 1) from = &pole1;
        else if (source == 2) from = &pole2;
        else from = &pole3;

        if (dest == 1) to = &pole1;
        else if (dest == 2) to = &pole2;
        else to = &pole3;

        if ((*from).empty()){
            explain = false;
            continue;
        };

        if (!(*to).empty() && (*from).back() > (*to).back()) {
            explain = false;
            continue;
        }
        (*to).push_back((*from).back());
        (*from).pop_back();
        moveCount++;

    }
}