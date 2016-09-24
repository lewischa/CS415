/* 
 * File:   main.cpp
 * Author: Jeremy Olsen & Chad Lewis
 *
 * Purpose: This program takes in four integers from a user, converts those ints
 * into a binary representation and performs bit-level math.
 * 
 * Created on September 10, 2016, 2:45 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "hw1.hpp"
//void problemThreeA(std::vector<int> &itVeect);
//void problemThreeB(std::vector<int> &intVect);
/*
 * 
 */
int main(int argc, char** argv) {
    int option;
    
    std::cout << "Choose option number:\n";
    std::cout << "1. Problem3a\n";
    std::cout << "2. Problem3b\n";
    std::cout << "3. Quit program\n";
    
    std::cin >> option;
    
    while(option != 3){
        std::vector<int> iArray;
        std::vector<int> binArray[4];
        int tempValue;
        bool validInt = true;
        
        
        if(option >= 1 && option <=3){
            std::cout << "Enter 4 integer values where for each integer 0 < n < 1000: ";
            for(int i = 0; i < 4; i++){
                 std::cin >> tempValue;       
                iArray.push_back(tempValue);
                if(tempValue <= 0 || tempValue > 1000){
                    validInt = false;
                }
            }

            for(int i = 0; i < 4; i++){
                binArray[i] = dec2bin(iArray.at(i));                
            }

            if(!validInt || iArray.size() != 4 ){
                option = 0;
            }
        }
        if(option == 1){
          //(A^B - C^D)
            if(lessThan(aPowerB(binArray[2], binArray[3]),
                    aPowerB(binArray[0], binArray[1]))){
                std::cout << Bin2Dec(subtract(aPowerB(binArray[0], binArray[1]),
                        aPowerB(binArray[2], binArray[3])));
                std::cout << std::endl;
            }
            else{
                std::cout << '-';
                std::cout << Bin2Dec(subtract(aPowerB(dec2bin(iArray[0]), dec2bin(iArray[1])),
                        aPowerB(dec2bin(iArray[2]), dec2bin(iArray[3]))));
                std::cout << std::endl;
            }
        }
        else if(option == 2){
            //(A^B/C^D)
            quoRem res;
            std::vector<int> ab = aPowerB(dec2bin(iArray[0]), dec2bin(iArray[1]));
            std::vector<int> cd = aPowerB(dec2bin(iArray[2]), dec2bin(iArray[3]));
//            print(ab);
//            print(cd);
            res = divide(ab, cd);
//            std::cout << "res.q size " << res.q.size() << std::endl;
            std::cout << "quotient = " << Bin2Dec(res.q) << std::endl;
            std::cout << "remainder = " << Bin2Dec(res.r) << std::endl;
        }
        else if (option == 0){            
            std::cout << "Invalid integers selected! Returning to option menu.\n";
        }
        else{
            std::cout << "Invalid option chosen. Returning to option menu.\n";
        }
        
        
        std::cout << "Choose option number:\n";
        std::cout << "1. Problem3a\n";
        std::cout << "2. Problem3b\n";
        std::cout << "3. Quit program\n";
    
        std::cin >> option;
    }
    return 0;
}

