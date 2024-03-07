#include <iostream>
#include <string>
using namespace std;
// Function to perform encryption on plain text using a key
string encryption(string text, string key) {
// Array containing alphabets from A to Z
    char alpha[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z'};
    // Create a modified alphabet by excluding characters present in the key
    string modified_alpha;
    for (char i : alpha) {
        bool flag = true;
        for (char j : key) {
            if (i == j) {
                flag = false;
                break;
            }
        }
        if (flag)
            modified_alpha += i;
    }
    // Append the modified alphabet to the key
    key += modified_alpha;
    // Encrypt the text by replacing each character with the corresponding key character
    for (int i = 0; i < text.size(); i++){
        char ch = text[i];
        if (isalpha(ch)) {
            ch = tolower(ch);
            int index = ch - 'a';
            if (0 <= index && index < 26)
                text[i] = key[index];
        }
    }
    return text;
}
// Function to perform decryption on encrypted text using a key
string decryption(string text, string key) {
// Array containing alphabets from A to Z
    char alpha[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z'};
    // Create a modified alphabet by excluding characters present in the key
    string modified_alpha;
    for (char i : alpha) {
        bool flag = true;
        for (char j : key) {
            if (i == j) {
                flag = false;
                break;
            }
        }
        if (flag)
            modified_alpha += i;
    }
    // Append the modified alphabet to the key
    key += modified_alpha;
    // Create a dictionary to map key characters to the original alphabet characters
    char alpha_dict[26];
    for (int i = 0; i < 26 && i < key.size(); ++i)
        alpha_dict[key[i] - 'a'] = alpha[i];
    // Decrypt the text by replacing each character with the corresponding dictionary value
    for (int i = 0; i < text.size(); ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            ch = tolower(ch);
            int index = ch - 'a';
            if (0 <= index && index < 26)
                text[i] = alpha_dict[index];
        }
    }
    return text;
}
// Main function
int main() {
    string key, text;
    int choice;
    // Loop to run the program repeatedly until the user chooses to exit
    while (true) {
        // Prompt the user for encryption, decryption, or exit
        cout << "\nWhat would you like to do?\n1) Encrypt a message.\n2) Decrypt a message.\n3) Exit.\n";
        // Validate user input for choice
        while (true){
            if (!(cin >> choice) || !(choice == 1 || choice == 2 || choice == 3)) {
                cout << "Please enter a valid choice.\n";
                // Clear input buffer and discard invalid input
                cin.clear();
                while (cin.get() != '\n');
            }
            else {
                break;
            }
        }
        // Check if the user wants to exit
        if (choice == 3) {
            cout << "Exiting the program....";
            break;  // Exit the loop and end the program
        }
            // For encryption or decryption, continue with the following steps
        else if (choice == 1 || choice == 2) {
            // Prompt the user to enter the key
            cout << "Enter the key word.\n";
            while (true) {
                cin >> key;
                // Validate the key (only alphabets)
                bool isValidKey = true;
                for(char ch : key){
                    if(!isalpha(ch)){
                        isValidKey = false;
                        cout << "Please enter a valid key (only alphabets).\n";
                        break;
                    }
                }
                // Break the loop if the key is valid
                if (isValidKey)
                    break;
            }
            // Prompt the user to enter the text
            cout << "Enter the text.\n";
            cin.ignore();
            getline(cin, text);
            // Perform encryption or decryption based on user choice
            if (choice == 1){
                string encryptedText = encryption(text, key);
                cout << "The encrypted text: " << encryptedText << "\n";
            }
            else if (choice == 2){
                string decryptedText = decryption(text, key);
                cout << "The decrypted text: " << decryptedText << "\n";
            }
        }
        else {
            cout << "Please enter a valid choice\n";
        }
    }
    return 0;
}
