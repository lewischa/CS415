/*
 *File:     main_hw2.cpp
 *Author:   Jeremy Olsen & Chad Lewis
 *
 *Purpose:  This program serves to implement mod, mod-inverse, and RSA encryption/decryption.
 *
 *Created on September 24, 2016 13:55
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "hw.hpp"

void problem1_13();
void modInverse();
void printVector(std::vector<int> vec);
void printBinary(std::vector<int> vec);


int main() {
    problem1_13();
    modInverse();
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