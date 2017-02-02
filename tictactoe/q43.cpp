#include <iostream>
using namespace std;


void getInput(int playerid, int *arr, int SIZE){
    // get user choice
    char token = (playerid == 1) ? 'X' : 'O';
    int row, col;
    cout << "Player " << playerid << ", it's your turn." << endl;
    do{
        cout << "Where would you like to place an " << token << "? Row (1, 2...): ";
        cin >> row;
        cout << "Col (1, 2...): ";
        cin >> col;
        if(col < 1 || col > SIZE)
            cout << "Column must be between 1 and " << SIZE << endl;
        if(row < 1 || row > SIZE)
            cout << "Row must be between 1 and " << SIZE << endl;
        if(arr[(row - 1) * SIZE + (col - 1)] != 0)
            cout << "That square is already occupied" << endl;
    } while( row < 1 || row > SIZE || col < 1 || col > SIZE || arr[(row - 1) * SIZE + (col - 1)] != 0);
    
    // store in data structure
    arr[(row - 1) * SIZE + (col - 1)] = playerid;
}

void printBoard(int *arr, int SIZE){
    for(int i = 0; i < SIZE; i++){
        // print first row of grid square
        for(int j = 0; j < SIZE; j++){
            int index = i * SIZE + j;
            if(arr[index] == 0)
                cout << " ";
            else if (arr[index] == 1)
                cout << "X";
            else
                cout << "O";
            cout << "  ";
            if(j != SIZE - 1)
                cout << "|";
        }
        cout << endl;
        // print second row of grid square
        if(i != SIZE - 1){
            for(int j = 0; j < SIZE; j++){
                cout << "___";
                if(j != SIZE - 1)
                    cout << "|";
            }
        }
        else{
            for(int j = 0; j < SIZE; j++){
                cout << "   ";
                if(j != SIZE -1)
                    cout << "|";
            }
        }
        cout << endl;
    }
}

int check(int *arr, int SIZE){
    int col, row, diag;
    int col2, row2, diag2;

    for(int i = 0; i < SIZE; i++){
        row = row2 = 0;
        col = col2 = 0;
        for(int j = 0; j < SIZE; j++){
            if(arr[i * SIZE + j] == 1) row++;
            else row = 0;
            if(row == 3) return 1;

            if(arr[i * SIZE + j] == 2) row2++;
            else row2 = 0; 
            if(row2 == 3) return 2;

            if(arr[j * SIZE + i] == 1) col++;
            else col = 0;
            if(col == 3) return 1;

            if(arr[j * SIZE + i] == 2) col2++;
            else col2 = 0;
            if(col2 == 3) return 2;
        }
    }

    for(int offset = -(SIZE - 3); offset <= SIZE - 3; offset++){
        diag = diag2 = 0;
        for(int x = 0; x < SIZE - offset; x++){
            int index = x + SIZE * (x + offset);
            if(arr[index] == 1) diag++;
            else diag = 0;
            if(diag == 3) return 1;

            if(arr[index] == 2) diag2++;
            else diag2 = 0;
            if(diag2 == 3) return 2;

        }
    }

    for(int offset = 0; offset <= SIZE - 3; offset++){
        diag = diag2 = 0;
        int offset2 = SIZE + offset + 1;
        for(int x = offset2; x < SIZE; x++){
            int index = x + SIZE * (offset2 - x);
            if(arr[index] == 1) diag++;
            else diag = 0;
            if(diag == 3) return 1;

            if(arr[index] == 2) diag2++;
            else diag2 = 0;
            if(diag2 == 3) return 2;
        }



        offset2 = SIZE - offset - 1;
        for(int x = 0; x <= offset2; x++){
            int index = x + SIZE * (offset2 - x);
            if(arr[index] == 1) diag++;
            else diag = 0;
            if(diag == 3) return 1;

            if(arr[index] == 2) diag2++;
            else diag2 = 0;
            if(diag2 == 3) return 2;
        }


    }
    return 0;
}

int main(){
    int size;
    int *arr;
    cout << "WElCOME TO TIC-TAC-TOE 5000\nHow large would you like the nxn board to be? n=";
    cin >> size;
    arr = new int[size*size];
    // initialize board
    for(int i = 0; i < size*size; i++){
        arr[i] = 0;
    }
    cout << "LET'S BEGIN!" << endl;
    int turn = 0;
    int player = 1;
    int winner;
    while(turn < size*size){
        printBoard(arr, size);
        cout << "PLAYER " << player << " it's your move.";
        getInput(player, arr, size);
        if(check(arr, size)){
            winner = check(arr, size);
            printBoard(arr, size);
            cout << "PLAYER " << winner << " WINS!" << endl;
            delete [] arr;
            return 0;
        }
        player = (player == 1) ? 2 : 1;
        turn++;
    }
    printBoard(arr, size);
    cout << "Cat's game." << endl;
    delete [] arr;
    return 0;
}
