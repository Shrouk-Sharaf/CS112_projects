// program: the code aims to create an interactive and engaging text-based game where players compete to strategically
//         remove items from a pile, with the ultimate goal of being the player to remove the last item and win the game
//         (GAME 3).
// Author: Shrouk Sayed Ahmed Mohammed
// Version: 2.0
// Date: 28/2/2024

#include <iostream>
#include <cmath>
using namespace std;
// Function to check if a number is a valid square
bool validSquare(int num, int pile) {
    return 1 <= num && num <= pile && pow(num, 0.5) == int(pow(num, 0.5));
}
int main() {
    // Display the game menu
    cout << "*** Subtract a square game ***\n";
    cout << "A) Start the game\nB) Check the game instructions\n";
    bool cases = true; // Variable to control game flow
    int score_player_1 = 0;
    int score_player_2 = 0;
    // Main game loop
    while (cases) {
        char choice;
        cin >> choice;
        if (choice == 'A' || choice == 'a') {
            string player_1, player_2;
            // Get names of players
            cout << "Player 1: enter your name\n";
            cin >> player_1;
            cout << "Player 2: enter your name\n";
            cin >> player_2;
            while (cases) {
                int pile;
                // Get the initial size of the pile
                cout << "Enter the number of starting pile\n";
                cin >> pile;
                // Validate the input for the starting pile
                while (pile <= 0 || pile * pile == pile) {
                    cout << "Invalid input. Please enter a positive non-square number.\n";
                    cin >> pile;
                }
                // Game loop for each pile
                while (pile > 0) {
                    int t_1, t_2;
                    // Display the current state of the pile
                    cout << "Current pile = " << pile << endl;
                    // Player 1's turn
                    cout << player_1 << ": enter your square number (1 to " << pile << ")\n";
                    cin >> t_1;
                    // Validate the input for player 1's move
                    while (!validSquare(t_1, pile)) {
                        cout << "Please enter a valid square number.\n";
                        cin >> t_1;
                    }
                    // Update the pile based on player 1's move
                    pile -= t_1;
                    // Check if Player 1 wins
                    if (pile == 0) {
                        // Display the winner and the updated scores
                        cout << player_1 + " Wins!!!" << endl;
                        score_player_1++;
                        cout << "Scores: " << player_1 << " - " << score_player_1 << ", " << player_2 << " - "
                             << score_player_2 << endl;
                        // check if they want to play a new game
                        char choice2;
                        cout << "Do you want to start a new game?\nA)Yes\nB)No\n";
                        cin >> choice2;
                        cases = (choice2 == 'a' || choice2 == 'A');
                        break;
                    }
                    // Player 2's turn
                    cout << "Current pile = " << pile << endl;
                    cout << player_2 << ": enter your square number (1 to " << pile << ")\n";
                    cin >> t_2;
                    // Validate the input for player 2's move
                    while (!validSquare(t_2, pile)) {
                        cout << "Please enter a valid square number.\n";
                        cin >> t_2;
                    }
                    // Update the pile based on player 2's move
                    pile -= t_2;
                    // Check if Player 2 wins
                    if (pile == 0) {
                        // Display the winner and the updated scores
                        cout << player_2 + " Wins!!!" << endl;
                        score_player_2++;
                        cout << "Scores: " << player_1 << " - " << score_player_1 << ", " << player_2 << " - "
                             << score_player_2 << endl;
                        // check if they want to play a new game
                        char choice2;
                        cout << "Do you want to start a new game?\nA)Yes\nB)No\n";
                        cin >> choice2;
                        cases = (choice2 == 'a' || choice2 == 'A');
                        break;
                    }
                }
            }
        } else if (choice == 'B' || choice == 'b') {
            // Display game instructions
            cout << "The instructions are the following:\n"
                 << "1) The Game should be played by 2 players.\n"
                 << "2) First, you have to put a starting value for the pile.\n"
                 << "3) Second, the players take turns removing valid non-zero square numbers from the pile.\n"
                 << "4) The player removing the last coin wins.\n"
                 << "If you want to start playing, Press \"A\".\n";
        } else {
            // Invalid choice
            cout << "Please, enter a valid choice.\n";
        }
    }
    return 0;
}
