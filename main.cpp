/*
 *File:     main.cpp
 *Author:   Jeremy Olsen & Chad Lewis
 *
 *Purpose:  This program serves to implement mod, mod-inverse, and RSA encryption/decryption.
 *
 *Created on September 24, 2016 13:55
 */



/*
 What still needs to be done: 
 - getMessage() in main somehow returning a message that is not what the user entered
 - Finish RSA-encrypt/RSA-decrypt
    - Decrypted message coming back as 0 for some reason, couldn't figure it out
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "hw.hpp"

int getOption();
void runOption(int option);
void problem1_13();
void modInverse();
void Primality2();
void getKeyValues();
void RSAKeyGenerate();
std::vector<int> getMessage();
void RSAEncrypt();
void printVector(std::vector<int> vec);
void printBinary(std::vector<int> vec);


RSAKey globalRSAKey;
bool globalHasKey = false;

struct RSAKeyValues {
    int numDigits;
    int k;
};

RSAKeyValues globalKeyValues;    // Holds numDigits and confidence parameter k
bool globalHasKeyValues = false;


int main() {
//    int option;
//    problem1_13();
//    modInverse();
//    Primality2();
    while (true) {
        int option = getOption();
        runOption(option);
    }

//    std::vector<int> _144;
//    std::vector<int> _137;
//    _144.push_back(0); _144.push_back(0);
//    _144.push_back(0); _144.push_back(0);
//    _144.push_back(1); _144.push_back(1);
//    _144.push_back(0); _144.push_back(0);
//    
//    print(_144); print(reverse(_144)); print(trim(_144));

    return 0;
}

int getOption() {
    int option;
    std::cout << "You may choose one of the following options: " << std::endl;
    std::cout << "1.  Extended GCD" << std::endl;
    std::cout << "2.  Primality Testing" << std::endl;
    std::cout << "3.  RSA-key-generate" << std::endl;
    std::cout << "4.  RSA-encrypt and RSA-decrypt" << std::endl;
    std::cout << "5.  Quit" << std::endl;
    std::cout << "Enter which option you would like to do: ";
    std::cin >> option;
    if (option == 5) exit(0);
    while (option < 1 || option > 5 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "That is not a valid option. Try again: ";
        std::cin >> option;
    }
    return option;
}

void runOption(int option) {
    if (option == 1) {
        modInverse();
        return;
    }
    else if (option == 2) {
        Primality2();
        return;
    }
    else if (option == 3) {
//        std::cout << "Can't do that option yet." << std::endl;
        RSAKeyGenerate();
        return;
    }
    else {
        RSAEncrypt();
        return;
    }
}
void problem1_13() {
    // Pre-condition: None
    // Post-condition: True if (a ^ b) - (c ^ d) mod e == 0,
    // false otherwise
    
    std::vector<int> iArray;
    int temp;
    
    std::cout << std::endl << "Problem 1.13:" << std::endl;
    std::cout << "Output:  True if (a ^ b) - (c ^ d) mod e == 0" << std::endl;
    
    std::cout << "Enter 5 integer values (a, b, c, d, and e) where n > 0: ";
    for (int i = 0; i < 5; i++) {
        std::cin >> temp;
        while (temp <= 0) {
            std::cout << "Value must be non-negative. Try again: ";
            std::cin >> temp;
        }
        iArray.push_back(temp);
    }
    
    quoRem res;
    std::vector<int> ab = aPowerB(dec2bin(iArray[0]), dec2bin(iArray[1]));
    std::vector<int> cd = aPowerB(dec2bin(iArray[2]), dec2bin(iArray[3]));
    std::vector<int> sub = subtract(ab, cd);
    std::vector<int> divisor = dec2bin(iArray[4]);
    res = divide(sub, divisor);
    if (Bin2Dec(res.r) == "0") {
        std::cout << "True" << std::endl;
        std::cout << "(" << iArray[0] << " ^ " << iArray[1] << ") - (" << iArray[2] << " ^ " << iArray[3] << ") mod " << iArray[4] << " == 0" << std::endl << std::endl;
    }
    else {
        std::cout << "False" << std::endl;
        std::cout << "(" << iArray[0] << " ^ " << iArray[1] << ") - (" << iArray[2] << " ^ " << iArray[3] << ") mod " << iArray[4] << " != 0" << std::endl << std::endl;
    }
    return;
}

void modInverse() {
    // Pre-condition: User must enter two positive integer values A,B
    // Post-condition: Returns x, y, d such that Ax + By = d
    int x;
    std::vector<int> a;
    std::vector<int> b;
    extEuclid euclid;
    
    std::cout << "Enter a positive integer: ";
    std::cin >> x;
    a = dec2bin(x);
    std::cout << "Enter another positive integer: ";
    std::cin >> x;
    b = dec2bin(x);
    
    euclid = extendedEuclid(a,b);
    if ( euclid.sign == 0 ) {
        // Both return values (euclid.x, euclid.y) are positive
        std::cout << Bin2Dec(euclid.x) << std::endl;
        std::cout << Bin2Dec(euclid.y) << std::endl;
    }
    else if ( euclid.sign == 1 ) {
        // euclid.x is negative
        std::cout << "-" << Bin2Dec(euclid.x) << std::endl;
        std::cout << Bin2Dec(euclid.y) << std::endl;
    }
    else {
        // euclid.y is negative
        std::cout << Bin2Dec(euclid.x) << std::endl;
        std::cout << "-" << Bin2Dec(euclid.y) << std::endl;
    }
    std::cout << Bin2Dec(euclid.d) << std::endl;
    
    return;
}

// Still needs some work to allow for larger inputs
void Primality2() {
    // Prompts the user for integers N and k
    // N will be the number to test for primality,
    // k is a confidence parameter that reduces probability
    // of a false positive to below 1/(2^k)
    
    std::string N;
    int k;
    
    std::cout << "Enter a positive integer N: ";
    std::cin >> N;
    std::cout << "Enter a confidence parameter (positive integer) k: ";
    std::cin >> k;
    
    // Initialize random number generator
    srand((unsigned int)time(NULL));
    
    // Array to hold decimal representations of all ai's
    std::vector<std::vector<int> > aSubI;
    
    for (int i = 0; i < k; i++) {
        aSubI.push_back(randBinGenerator(N));
    }
    
    bool result = primality2(strDec2Bin(N), aSubI);
    if ( result )
        std::cout << N << " is prime." << std::endl << std::endl;
    else
        std::cout << N << " is not prime." << std::endl << std::endl;
    
    return;
}



void getKeyValues() {
    int numDigits;
    int k;
    std::cout << "Enter the number of digits n for p and q (1 <= n <= 50): ";
    std::cin >> numDigits;
    
    while (numDigits < 1 || numDigits > 50 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');    // Error handling for non-int inputs
        std::cout << "You must enter a valid integer between 1 and 50, inclusive: ";
        std::cin >> numDigits;
    }
    globalKeyValues.numDigits = numDigits;
    
    std::cout << "Enter a confidence parameter k (1 <= k): ";
    std::cin >> k;
    
    while (k < 1 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');    // Error handling for non-int inputs
        std::cout << "That is not a valid integer for k. Try again: ";
        std::cin >> k;
    }
    globalKeyValues.k = k;
    globalHasKeyValues = true;
}

void RSAKeyGenerate() {
    // Pre-condition: User input n must be at most 50 digits
    // Post-condition: function will output p, q, and N such that
    // p and q are n-digit primes and N = p * q
    std::cout << "RSA-key-generate:" << std::endl;
    
    // User has already entered values n and k
    if (globalHasKeyValues) {
        char answer;    // y or n for yes/no
        std::cout << "You've already generated a key. Would you like to generate a different one ('y' or 'n')?: ";
        std::cin >> answer;
        
        while ( (answer != 'y' && answer != 'n') || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "You idiot, I said 'y' or 'n'! Try again: ";
            std::cin >> answer;
        }
        if (answer == 'y') {    // User wants to generate another key
            getKeyValues();
            globalRSAKey = rsaKeyGenerate(globalKeyValues.numDigits, globalKeyValues.k);
            globalHasKey = true;
        }
        else {      // User does not want to generate another key; use the one we have already
            std::cout << "Nothing to see here, I'll use your previously generated key. Returning..." << std::endl;
            return;
        }
    }
    // User has not entered values for n and k
    else {
        getKeyValues();
        globalRSAKey = rsaKeyGenerate(globalKeyValues.numDigits, globalKeyValues.k);
        globalHasKey = true;
        return;
    }
    
    return;
}

std::vector<int> getMessage() {
    std::string message = "";
    std::vector<int> binMessage;
    std::cout << "Please enter a message to encrypt/decrypt (up to 50 digits long): " << std::endl;
    std::cin >> message;
    
    while (message.length() > 50 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Try again: " << std::endl;
        std::cin >> message;
    }
    binMessage = strDec2Bin(message);
    return binMessage;
}

void RSAEncrypt() {
    char answer;
    std::vector<int> message;
    std::vector<int> encryptedMessage;
    std::vector<int> decryptedMessage;
    message = getMessage();
    printBinary(message);
    std::cout << Bin2Dec(message) << std::endl;
    
    // User has already done option 3, and has generated an RSA key
    if (globalHasKey) {
        std::cout << "Looks like you've generated an RSA key already. Would you like to use that one for RSA-encrypt/RSA-decrypt ('y' or 'n')?: ";
        std::cin >> answer;
        while ( (answer != 'y' && answer != 'n') || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "You idiot, I said 'y' or 'n'! Try again: ";
            std::cin >> answer;
        }
        // User wants to use the previously generated RSA key
        if (answer == 'y') {
            std::cout << "Using same encryption key for RSA-encrypt." << std::endl;
        }
        // User wants to generate a different RSA key
        else {
            getKeyValues();
            globalRSAKey = rsaKeyGenerate(globalKeyValues.numDigits, globalKeyValues.k);
            globalHasKey = true;
        }
    }
    // User has not done option 3, and first needs to generate an RSA key
    else {
        std::cout << "Looks like you haven't generated an RSA key yet." << std::endl;
        getKeyValues();
        globalRSAKey = rsaKeyGenerate(globalKeyValues.numDigits, globalKeyValues.k);
        globalHasKey = true;
        std::cout << "test" << std::endl;
    }
    std::cout << "Original message: " << Bin2Dec(message) << std::endl;
    message = rsaEncrypt(message, globalRSAKey.e, globalRSAKey.N);
    std::cout << "Encrypted message: " << Bin2Dec(message) << std::endl;
    message = rsaEncrypt(message, globalRSAKey.d, globalRSAKey.N);
    std::cout << "Decrypted message: " << Bin2Dec(message) << std::endl;
    return;
}

void printVector(std::vector<int> vec) {
    std::cout << std::endl;
    std::cout << "Now printing vector." << std::endl;
    for (int i = 0; i < vec.size(); i++ ) {
        std::cout << vec.at(i) << std::endl;
    }
}

void printBinary(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++ ) {
        std::cout << vec.at(i);
    }
    std::cout << std::endl;
}
