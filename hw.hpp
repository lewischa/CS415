/* 
 * File:   hw.hpp
 * Author: Jeremy Olsen & Chad Lewis
 *
 * Purpose: this file contains the functions for homework 1 and homework 2
 * Created on September 12, 2016, 11:48 PM
 */

#ifndef HW1_HPP
#define	HW1_HPP

#include <vector>
#include <math.h>
#include <iostream>
#include <time.h>

struct quoRem {
    std::vector<int> q;
    std::vector<int> r;
};

struct extEuclid {
    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> d;
    int sign;
};

void print(std::vector<int> pMe){
    for(int i = 0; i < pMe.size(); i++){
        std::cout << pMe.at(i);
    }
    std::cout << std::endl;
}

std::vector<int> shiftLeft(std::vector<int> shiftMe){
    if(shiftMe.size() == 0){
        return shiftMe;
    }
    if(shiftMe.size() == 1 && shiftMe.at(0) == 0){
        return shiftMe;
    }
    shiftMe.push_back(0);
    return shiftMe;
}

//std::vector<int> shiftRight(std::vector<int> shiftMe){
//    if(shiftMe.size() == 0){
//        return shiftMe;
//    }
//    shiftMe.pop_back();
//    return shiftMe;
//}

std::vector<int> shiftRight(std::vector<int> shiftMe){
    if(shiftMe.size() == 0){
        return shiftMe;
    }
    ///
    else if ( shiftMe.size() == 1 ) {
        shiftMe.at(0) = 0;
    }
    else {
        shiftMe.pop_back();
    }
    return shiftMe;
}

bool even(std::vector<int> n){
    if(n.size() == 0 || n.at(n.size() - 1) == 0){
        return true;
    }
    
    return false;
}
bool lessThan(std::vector<int> a, std::vector<int> b){
//    print(b);
    if(a.size() > 0 && a.at(0) == 0){
//        std::cout << "invalid binary format" << std::endl;
//        std::cout << "printing a ";
//        print(a);
    }
    if(b.size() > 0 && b.at(0) == 0){
//        std::cout << "invalid binary format" << std::endl;
//        std::cout << "printing b ";
//        print(b);
    }
    if(a.size() < b.size()){
        return true;
    }
    else if(a.size() > b.size()){
        return false;
    }
    else{
        for(int i = 0; i < a.size(); i++){
            if(a.at(i) != b.at(i) && a.at(i) > b.at(i)){
                return false;
            }
            else if(a.at(i) != b.at(i) && a.at(i) < b.at(i)){
                return true;
            }
        }
        
        return false;
    }
}

bool equal(std::vector<int> a, std::vector<int> b){
    if(a.size() != b.size()){
        return false;
    }
    else{
        bool equal = true;
        for(int i = 0; i < a.size() && equal == true; i++){
            if(a.at(i) != b.at(i)){
                equal = false;
            }
        }
        
        return equal;
    }
}

std::vector<int> reverse(std::vector<int> revMe){
    std::vector<int> result;
    if(revMe.size() < 2){
        return revMe;
    }
    for(int i = revMe.size() - 1; i >= 0; i--){
        result.push_back(revMe.at(i));
    }
    return result;
}

int xOr(int a, int b, int carry){

    if(a xor (b xor carry)){
        return 1;
    }
    else{
        return 0;
    }
}

int nextCarry(int a, int b, int carry){
    if((a && b) || (a && carry) || (b && carry)){
        return 1;
    }
    else{
        return 0;
    }
}

//bool zero(std::vector<int> a){
//     
//    if(a.size() == 0){
//        return true;
//    }
//    else{
//        return false;
//    }
//}

bool zero(std::vector<int> a){
    if(a.size() == 0){
        return true;
    }
    else{
        /////////
        for ( int i = 0; i < a.size(); i++ ) {
            if ( a.at(i) == 1 ) return false;
        }
    }
    return true;
}

std::vector<int> add(std::vector<int> a, std::vector<int> b){
    
    if(zero(a)){
        return b;
    }
    if(zero(b)){
        return a;
    }
    if(equal(a,b)){
        return shiftLeft(a);
    }
    if(lessThan(a, b) && !equal(a, b)){
        return add(b, a);
    }
    int carry = 0;
    std::vector<int> result;
    

        int n = a.size() - b.size();
        for(int i = 0; i < b.size(); i++){
            result.push_back(xOr(reverse(a).at(i), reverse(b).at(i), carry));
            carry = nextCarry(reverse(a).at(i), reverse(b).at(i), carry);
        }
        for(int i = n -1; i >= 0; i--){
            result.push_back(xOr(a.at(i), 0, carry));
            carry = nextCarry(a.at(i), 0, carry);
        }
        if(carry == 1){
            result.push_back(carry);
        }

    return reverse(result);
}

bool isGreaterOrEqualTo(std::vector<int> a, std::vector<int> b) {
    // is a >= b? return true if yes, false if not
//    if ( a.size() > b.size() ) return true;
//    else if ( a.size() < b.size() ) return false;
//    else {
        for ( int i = 0; i < a.size(); i++ ) {
            if ( a.at(i) < b.at(i) ) return false;
            if ( a.at(i) > b.at(i) ) return true;
        }
        return true;
//    }
}


std::vector<int> addOne(std::vector<int> a) {
    int carry = 0;
    if(a.size() == 0){
       a.push_back(1);
       return a;
    }
    for (int i = a.size() - 1; i >=0; i--) {
        if ( carry == 0 ) {
            if ( a.at(i) == 0 ) {
                a.at(i) = 1;
                break;
            }
            else {
                a.at(i) = 0;
                carry = 1;
            }
        }
        else {
            if ( a.at(i) == 0 ) {
                a.at(i) = 1;
                break;
            }
            else {
                a.at(i) = 0;
                carry = 1;
            }
        }
    }
    return a;
}

std::vector<int> twosComplement(std::vector<int> a) {
    std::vector<int> complement;
    for (int i = 0; i < a.size(); i++) {
        if ( a.at(i) == 0 ) {
            complement.push_back(1);
        }
        else {
            complement.push_back(0);
        }
    }
    return complement;
}

std::vector<int> addComplement(std::vector<int> a, std::vector<int> b){
    
    if(lessThan(a, b) && !equal(a, b)){
        return addComplement(b, a);
    }
    int carry = 0;
    std::vector<int> result;
    
    if ( b.size() == 0 ) return a;
    
    
    int n = a.size() - b.size();
    for(int i = 0; i < b.size(); i++){
        result.push_back(xOr(reverse(a).at(i), reverse(b).at(i), carry));
        carry = nextCarry(reverse(a).at(i), reverse(b).at(i), carry);
    }
    for(int i = n -1; i >= 0; i--){
        result.push_back(xOr(a.at(i), 0, carry));
        carry = nextCarry(a.at(i), 0, carry);
    }

    return reverse(result);
}

std::vector<int> subtract(std::vector<int> a, std::vector<int> b) {
    
    if(lessThan(a, b) && !equal(a, b)){
        return subtract(b, a);
    }
    // ONLY WORKS FOR POSITIVE/ZERO VALUES
    std::vector<int> result;
    if ( equal(a,b) ) {
        return result;
    }
    int n = a.size() - b.size();
    b = reverse(b);
    for ( int i = 0; i < n; i++ ) {
        b.push_back(0);
    }
    b = reverse(b);
    
    b = twosComplement(b);
    b = addOne(b);
    
    result = reverse(addComplement(a,b));
    
    while ( result.at(result.size() - 1) == 0 ) {
        result.pop_back();
    }
    return reverse(result);
}

static std::string next(char c) {
  // returns the next digit in the sequence 0->1, 1->2, ..., 8->9
  std::string s1[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
  return s1[c- '0'];
}

static std::string increment(std::string x) {
	// increments the number represented by string x. Example: if x = â€˜912â€™, then increment(x) will return â€˜022â€™
	if (x.length() == 0) // input is 0, so out = 1
	  return "1";
	if (x[0] < '9')
	  return next(x[0]) + x.substr(1, x.length() - 1);
	else
	  return "0" + increment(x.substr(1, x.length() - 1));
}

static std::string twice(char x) {
  // precondition: x is '0', '1', '2', '3' or '4'
      switch (x) {
      case '0': return "0";
      case '1': return "2";
      case '2': return "4";
      case '3': return "6";
      case '4': return "8";
      }
      std::cout << "incorrect input" << std::endl; return "";  // code to avoid warning
}

static std::string mod_twice(char x) {
  //precondition: x is in {'5', ..., '9'}
  switch (x) {
    case '5': return "0";
    case '6': return "2";
    case '7': return "4";
    case '8': return "6";
    case '9': return "8";
    }
    std::cout << "incorrect input" << std::endl; return ""; // code to avoid warning
}

static std::string mult2(std::string x) {
  // takes a string of decimal digits as input, and produces a string that represents twice the value
  // represented by integer x. For example, if x = â€™87â€™, mult2(x) will return â€˜651â€™ Note that the string 
  // stores the digits from least to most significant digit
  // we assume that number 0 is represented by null string
  if (x.length() == 0) 
    return "";
  std::string y = x.substr(1, x.length()-1); // Ex: if x = â€™87â€™ then y will be â€˜7â€™
  if (x[0] < '5') 
    return twice(x[0]) + mult2(y);
  else
    return mod_twice(x[0]) + increment(mult2(y));
 }

static std::string bin2dec(std::string x) {
  // input is a string representing a binary integer such as 01001 (0 is LSB, 1 is MSB). call to bin2dec(â€˜01001â€™) will return â€™81â€™ since decimal of 10010 is 18
  if (x.length() == 0) // assume null string represents integer 0. this is reasonable if we assume that MSB should always be 1
    return "0"; // same convention holds for decimal as well
  std::string y = x.substr(1, x.length() - 1);
  if (x[0] == '0')
    return mult2(bin2dec(y));
  else
    return increment(mult2(bin2dec(y)));;
} 

static std::string vecToStr(std::vector<int> vec) {
    std::string temp = "";
    for (int j = 0; j < vec.size(); j++) {
        if(vec[j] == 1)
            temp += "1";
        else
            temp += "0";
    }
  if (temp.length() == 0)
    return "0";
  else      
    return temp;
}

static std::string reverse(std::string x) {
  // returns the reversed string
  std::string temp = x;
  for (int j = x.length()-1; j >= 0; j--)
    temp[x.length()-1-j] = x[j];
  return temp;
}

std::string Bin2Dec(std::vector<int> vec){
    return reverse(bin2dec(vecToStr(reverse(vec))));
}

quoRem divide(std::vector<int> a, std::vector<int> b) {
    quoRem res;
    
    if ( zero(a) ) {
        res.q;
        res.r;
        return res;
    }
    
    res = divide( shiftRight(a), b);
    
    res.q = shiftLeft(res.q);
    res.r = shiftLeft(res.r);
    
    if (!even(a)) {
        res.r = addOne(res.r);
    }
    
    if(!lessThan(res.r, b)) {
        res.r = subtract(res.r, b);        
        res.q = addOne(res.q);
    }
    
    return res;
}

std::vector<int> dec2bin(int n){
    
    std::vector<int> result;
    
    while(n != 0){
        result.push_back(n % 2);
        n /= 2;
    }
    result = reverse(result);
    return result;
}

//not finished
std::vector<int> mult(std::vector<int> a, std::vector<int> b){
    
    if(lessThan(a, b) && !equal(a, b)){
        return mult(b,a);
    }
    std::vector<int> multiply;
    //    if(lessThan(b, a)){
    while(!zero(b)){
        
        if(!even(b)){
            std::vector<int> temp = multiply;
            multiply = add(temp, a);
        }
        a = shiftLeft(a);
        b = shiftRight(b);
    }
    
    return multiply;
    
}

std::vector<int> aPowerB(std::vector<int> a, std::vector<int> b){
    if(zero(b)){
        std::vector<int> one;
        one.push_back(1);
        return one;
    }
    std::vector<int> z;
    z = aPowerB(a, shiftRight(b));
    if(even(b)){
        z = mult(z, z);
        return z;
    }
    else{
        z = mult(z, z);
        z = mult(a, z);
        return z;
    }
}

std::vector<int> mod(std::vector<int> a, std::vector<int> b) {
    quoRem res;
    
    res = divide(a, b);
    
    return res.r;
}


extEuclid extendedEuclid(std::vector<int> a, std::vector<int> b) {
    extEuclid temp;
    
    if (zero(b)) {
        temp.x = dec2bin(1);
        temp.y = dec2bin(0);
        temp.d = a;
        temp.sign = 0;
        return temp;
    }
    
    temp = extendedEuclid(b, mod(a, b));
    extEuclid res;
    quoRem q = divide(a,b);
    std::vector<int> product = mult(q.q, temp.y);
    res.x = temp.y;
    
    
    if ( temp.sign == 0 ) {
        // Both temp.x and temp.y are positive
        res.y = subtract(temp.x, product);
        if ( lessThan(temp.x, product) ) {
            // Subtracting product from temp.x will return a negative value,
            // so set the sign for res.y as negative
            res.sign = 2;
        }
        else {
            res.sign = 0;
        }
    }
    else if ( temp.sign == 1 ) {
        // temp.x has been returned as a negative value
        // Since we do temp.x - (a/b)*temp.y, we can return
        // temp.x + (a/b)*temp.y and set the sign to show that as a negative
        res.y = add(temp.x, product);
        res.sign = 2;
    }
    else {
        // temp.y has been returned as a negative,
        // so temp.x - (a/b)*temp.y can be returned as
        // temp.x + (a/b)*temp.y
        res.y = add(temp.x, product);
        // Since we return temp.y as the first return value,
        // set the sign to reflect that
        res.sign = 1;
    }
    
    res.d = temp.d;
    return res;
}

std::vector<int> subtractOne(std::vector<int> vec) {
    // Subtracts one from binary representation held in vec
    
    std::vector<int> temp;
    temp.push_back(1);
    
    return subtract(vec, temp);
}

std::vector<int> trim(std::vector<int> vec) {
    // Removes leading zeroes
    vec = reverse(vec);
    
    for (int i = vec.size() - 1; i > 0; i++) {
        if (vec.at(i) == 0)
            vec.pop_back();
    }
//    std::cout << "inside trim" << std::endl;
    return vec;
}

bool isOne(std::vector<int> vec) {
    // Returns true if vec == 1, false otherwise
    
    std::vector<int> one;
    one.push_back(1);
    
//    std::cout << "inside isOne" << std::endl;
//    return equal(trim(vec), one);
    return equal(vec, one);
}

bool primality2(std::vector<int> N, std::vector<int> k, std::vector<unsigned int> aiVector) {
    // Pre-condition: N is a positive integer, 1 <= k <= N
    // Post-condition: Returns true if N is prime, false otherwise
    
    
    
    // This vector holds binary representations of all ai's
    std::vector<std::vector<int> > aSubI;
    // Convert decimal ai's to binary representation and load the vector
    for (int i = 0; i < aiVector.size(); i++) {
//        std::cout << "test" << std::endl;
        aSubI.push_back(dec2bin(aiVector.at(i)));
    }
    
    // ai ^ (N - 1)
    std::vector<int> exponent;
    
    // ai ^ (N - 1) mod N
    std::vector<int> modulus;
    
//    std::cout << "N - 1: " << Bin2Dec(subtractOne(N)) << std::endl;
//    
//    std::cout << "Printing ai's: ";
//    for (int i = 0; i < aSubI.size(); i++) {
//        std::cout << Bin2Dec(aSubI.at(i)) << ", ";
//    }
//    std::cout << std::endl;
    
    std::vector<int> nMinusOne = subtractOne(N);
    
    for (int i = 0; i < aSubI.size(); i++) {
        exponent = aPowerB(aSubI.at(i), nMinusOne);
        modulus = mod(exponent, N);
//        std::cout << Bin2Dec(modulus) << std::endl;
        if ( !isOne(modulus) ) return false;
    }
    return true;
}






#endif	/* HW1_HPP */

