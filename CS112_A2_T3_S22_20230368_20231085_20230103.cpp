// File: CS112_A2_T3_S22_20230368_20231085_20230103.cpp

// Purpose: rational number calculator that is capable of taking two rational numbers and an operation to perform on them.

// Author: Mahmoud Ahmed Ibrahim Mohamed , S22
// Author: Shrouk Sayed Ahmed Mohammed , S21
// Author: Jasmine Mohammed El-said mostafa , S21

// Emails: ma3549681@gmail.com
//         jasminemohamed174005@gmail.com
//         sayedahmedroka@gmail.com

// ID1: 20231085 – Function to handle input using getline, use regex library to make sure that the operation entered matches the pattern.
// ID2: 20230103 – Function for addition and subtraction, negative input and numerator without denominator, simplify the results to the simplest form.
// ID3: 20230368 – Function for multiplication, division and integrate the functions of person 1 and 2 and defensive programming.

#include <iostream> // Including necessary header files
#include <regex>
#include <string>
#include <cmath>
using namespace std;

int gcd(int a, int b) { // Function to find the greatest common divisor
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void simplification(int a, int b) { // Function to simplify fractions
    int common = gcd(abs(a), abs(b)); // Finding the greatest common divisor
    if (b / common == 1)
        cout << a / common << endl; // Output the simplified fraction if denominator is 1
    else
        cout << a / common << " / " << b / common << endl; // Output the simplified fraction
}

void multiplication(int num1, int denom1, int num2, int denom2) { // Function to perform multiplication of fractions
    simplification(num1 * num2, denom1 * denom2); // Simplifying the result of multiplication
}

void division(int num1, int denom1, int num2, int denom2) { // Function to perform division of fractions
    if (num2 == 0) { // Checking for division by zero
        cout << "Error! Division by zero\n"; // Output error message
        return;
    }
    simplification(num1 * denom2, denom1 * num2); // Simplifying the result of division
}

void addition(int num1, int denom1, int num2, int denom2) { // Function to perform addition of fractions
    simplification(num1 * denom2 + num2 * denom1, denom1 * denom2); // Simplifying the result of addition
}

void subtraction(int num1, int denom1, int num2, int denom2) { // Function to perform subtraction of fractions
    simplification(num1 * denom2 - num2 * denom1, denom1 * denom2); // Simplifying the result of subtraction
}

int main() { // Main function
    cout << "Enter the two fraction numbers and an operation between them:" << endl; // Prompting user for input
    int num1, denom1, num2, denom2; // Declaring variables to store numerator and denominator of fractions
    char operation; // Variable to store operation symbol
    string input_data; // String variable to store user input
    regex form(R"(([+-]?\d+)(?:\/(\d+))?[\s]([*/+-])\s([+-]?\d+)(?:\/(\d+))?)"); // Regular expression pattern to validate input
    while (getline(cin, input_data)) { // Loop to continuously read user input
        smatch match; // Match object to store matched groups
        if (!regex_search(input_data, match, form)) { // Checking if input matches the required pattern
            cout << "Invalid input" << endl; // Output error message for invalid input
            continue; // Skip to next iteration
        }
        num1 = stoi(match[1]); // Extracting numerator of first fraction and converting to integer
        denom1 = match[2].matched ? stoi(match[2]) : 1; // Extracting denominator of first fraction and converting to integer, defaulting to 1 if not present
        num2 = stoi(match[4]); // Extracting numerator of second fraction and converting to integer
        denom2 = match[5].matched ? stoi(match[5]) : 1; // Extracting denominator of second fraction and converting to integer, defaulting to 1 if not present
        if (denom1 == 0 || denom2 == 0) { // Checking for division by zero
            cout << "Invalid Denominator cannot be zero. Please enter a valid fraction " << endl; // Output error message
            continue; // Skip to next iteration
        }
        operation = match[3].str()[0]; // Extracting operation symbol
        if (operation == '*') { // Checking for multiplication operation
            multiplication(num1, denom1, num2, denom2); // Calling multiplication function
        } else if (operation == '/') { // Checking for division operation
            division(num1, denom1, num2, denom2); // Calling division function
        } else if (operation == '+') { // Checking for addition operation
            addition(num1, denom1, num2, denom2); // Calling addition function
        } else if (operation == '-') { // Checking for subtraction operation
            subtraction(num1, denom1, num2, denom2); // Calling subtraction function
        } else { // Handling invalid operation
            cout << "Invalid operation" << endl; // Output error message
            continue; // Skip to next iteration
        }
    }
    return 0;
}
/* the algorithm
1-create a function to calculate the greatest common divisor of two integers a,b
2-create a function (simplification) which simplify the fraction by finding their GCD and divide them by GCD
3-create a function of multiplication which takes four arguments num1,denom1,num2,denom2 and calculate (num1*num2 )and( denom1*denom2) and then simplify them by function simplification
4-create a function for division which takes four parameters num1,denom1,num2,denom2 and calculate (num1*denom2) and (num2*denom1) and simplify the result if denom1 or denom2 =0 a warning message will appear
5-create a function for addition which takes four parameters num1,denom1,num2,denom2 and calculate (num1 * denom2) + (num2 * denom1) and (denom1 * denom2) and simplify the result
6-create a function for subtraction which takes four parameters num1, denom1,num2,denom2 and calculate (num1 denom2) - (num2 * denom1) and denom1 denom2 and simplify the result
7-we will print a message to the user to enter two fraction numbers between then an operator
8-we will declare five  variables  int num1, int num2, int denom1, int denom2 and char operation
9- we read the input in a loop until the program terminated
10- we use regular expression to validate the input into fraction and operation
11-then we will call the appropriate function based on the operation which entered by the user
12- if user enter + we will call addition function
13- if user enter - we will call subtraction function
14-if user enter * we call multiplication function
15- if user entered / we call division function



Algorithm for the Ciphers

Simple substitution cipher:
1. Encryption Function (`encryption`):
   - Initialize an array `alpha` containing alphabets from 'a' to 'z'.
   - Create a modified alphabet `modified_alpha` by excluding characters present in the key.
   - Append the modified alphabet to the key.
   - Encrypt the text by replacing each character with the corresponding key character.
   - Return the encrypted text.
2. Decryption Function (`decryption`):
   - Initialize an array `alpha` containing alphabets from 'a' to 'z'.
   - Create a modified alphabet `modified_alpha` by excluding characters present in the key.
   - Append the modified alphabet to the key.
   - Create a dictionary `alpha_dict` to map key characters to the original alphabet characters.
   - Decrypt the text by replacing each character with the corresponding dictionary value.
   - Return the decrypted text.
3. Main Function (`main`):
   - Initialize variables `key`, `text`, and `choice`.
   - Start a loop to run the program repeatedly until the user chooses to exit.
   - Prompt the user for encryption, decryption, or exit.
   - Validate user input for the choice.
   - If the user chooses to exit, print a message and break out of the loop.
   - If the user chooses encryption or decryption, proceed with the following steps:
     - Prompt the user to enter the key.
     - Validate the key (only alphabets and 5 characters, no repeated characters).
     - Prompt the user to enter the text.
     - Perform encryption or decryption based on the user's choice.
     - Print the encrypted or decrypted text.
   - End of the loop.
4. Input Validation:
   - Validate user input for the choice (1, 2, or 3).
   - Validate the key (only alphabets and 5 characters, no repeated characters).
5. Exit Message:
   - Print an exit message when the user chooses to exit.
6. Error Handling:
   - Print error messages for invalid choices and invalid keys.
This algorithm provides a step-by-step explanation of how the code works and what each function and section of the main function does.


XOR Cipher :
1. Encryption/Decryption Function (`encrypt_decrypt`):
- Initialize an empty string `text` to store the encrypted/decrypted result.
- Iterate through each character of the original text:
- Perform XOR operation between the character and the corresponding character in the key (using modulus to repeat the key if it's shorter than the text).
- Append the result of the XOR operation to the `text`.
- Return the encrypted/decrypted `text`.
2. Hexadecimal to String Conversion Function (`hex_to_string`):
- Initialize an empty string `result` to store the converted string.
- Iterate through the hexadecimal string by pairs:
- Extract two characters from the hexadecimal string.
- Convert the pair of characters to a single byte and append it to `result`.
- Return the converted string.
3. Validation Function (`Valid_option`):
- Prompt the user for input and validate whether the input is a valid option (1, 2, or 3).
- Return the valid option.
4. Main Function:
- Prompt the user to enter the sentence to be encrypted.
- Prompt the user to enter the keyword.
- Validate the keyword (only alphabetic characters).
- Encrypt the original sentence using the provided keyword.
- Display the encrypted sentence.
- Convert the encrypted sentence to a hexadecimal string and display it.
- Prompt the user to enter the hexadecimal string to be decrypted.
- Validate the hexadecimal string (only hexadecimal characters).
- Prompt the user to enter the keyword again for decryption.
- Decrypt the hexadecimal string using the provided keyword.
- Display the decrypted sentence.
5. Input Validation:
- Validate the keyword for encryption and decryption (only alphabetic characters).
- Validate the hexadecimal string (only hexadecimal characters).
6. Error Handling:
- Print error messages for invalid options, invalid keys, and invalid hexadecimal strings.


Vignere cipher:
1) Print welcome message to the user
2) A menu will appear to the user if the user choose (Encryption program)
3) We will ask the user to input the word that he wanted to be encrypted and the keyword which we use to cipher the word
4) We need to check that the keyword is only alphabets (and capital letters only) so if the user enter a white space or special characters or digits or lower case letters a warning message will print
5) After taking the word from the user we will loop to check if it is letters or not
6) If letter we will check if it small or capital if small we will make it capital
7) Then calculate the encrypted char
8) After that add the encrypted char to a string variable called encryptedResult
9) if it is not a letter we will print it without encryption
10) finally print the encryptedResult
11) If the user choose from the menu (Decryption program)
12) A welcome message will print to the user
13) we will ask the user to enter the encrypted word which he wants to be decrypted
14) and ask the user to enter the keyword
15) we must check that the keyword only capital letters if the user enter a white space or small letters or special characters or digits a warning message will appear
16) after taking the encrypted word from the user we will loop to check if it letter or not
17) If letter we will calculate the decrypted char and add it to a string variable called decryptionResult
18) if it is not a letter we will print it without decryption
19) finally print the decryptedResult
*/