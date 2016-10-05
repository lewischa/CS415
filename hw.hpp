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
#include <string>

sstd::vector<int> trim(std::vector<int> vec);
bool isOne(std::vector<int> vec);

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

struct RSAKey {
    std::vector<int> p;
    std::vector<int> q;
    std::vector<int> N;
    std::vector<int> k;
    std::vector<int> e;     // e will be 3
    std::vector<int> d;     // d--> d*e = 1 mod N, MODULAR INVERSE
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
//    if(a.size() > 0 && a.at(0) == 0){
////        std::cout << "invalid binary format" << std::endl;
////        std::cout << "printing a ";
////        print(a);
//    }
//    if(b.size() > 0 && b.at(0) == 0){
////        std::cout << "invalid binary format" << std::endl;
////        std::cout << "printing b ";
////        print(b);
//    }
    
    /////////////////////////////////////////////
//    std::cout << "a: "; print(a);
//    std::vector<int> trimA = trim(a);
//    std::cout << "trimA: "; print(trimA);
//    std::cout << "b: "; print(b);
//    std::vector<int> trimB = trim(b);
//    std::cout << "trimB: "; print(trimB);
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
    std::vector<int> trimA;
    std::vector<int> trimB;
    trimA = trim(a);
    trimB = trim(b);
    if(trimA.size() != trimB.size()){
        return false;
    }
    else{
        bool equal = true;
        for(int i = 0; i < trimA.size() && equal == true; i++){
            if(trimA.at(i) != trimB.at(i)){
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
//    std::cout << "zero" << std::endl;
    if(a.size() == 0){
        return true;
    }
    else{
//        std::cout << a.size() << std::endl;
//        std::cout << "zero else" << std::endl;
        /////////
        for ( int i = 0; i < a.size(); i++ ) {
            if ( a.at(i) == 1 ) return false;
        }
        return true;
    }
    return true;
}

std::vector<int> add(std::vector<int> a, std::vector<int> b){
    if (zero(a) && zero(b)) return a;
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
//    std::cout << "in mult" << std::endl;
    if(lessThan(a, b) && !equal(a, b)){
        return mult(b,a);
    }
    std::vector<int> multiply;
    //    if(lessThan(b, a)){
    while(!zero(b)){
//        if (isOne(a)) return b;
//        if (isOne(b)) return a;
        if(!even(b)){
            std::vector<int> temp = multiply;
            multiply = add(temp, a);
        }
        a = shiftLeft(a);
        b = shiftRight(b);
    }
    
    return multiply;
    
//    std::vector<int> multiply;
//    if (zero(b)) {
//        std::vector<int> zero;
////        std::cout << "it's zero" << std::endl;
//        return zero;
//    }
//    if (isOne(a)) return b;
//    if (isOne(b)) return a;
////    std::cout << "hitting mult again" << std::endl;
//    multiply = mult(a, shiftRight(b));
//    if (even(b)) {
////        std::cout << "mult even" << std::endl;
//        return add(multiply, multiply);
//    }
//    else {
////        std::cout << "mult else" << std::endl;
//        return add(a, add(multiply, multiply));
//    }
    
}

std::vector<int> aPowerB(std::vector<int> a, std::vector<int> b){
//    std::cout << "aPowerB start" << std::endl;
    if(zero(b)){
        std::vector<int> one;
        one.push_back(1);
        return one;
    }
//    else {
//        std::vector<int> A1;
//        std::vector<int> B1;
////        std::cout << "aPower B before mult" << std::endl;
//        A1 = mult(a, a);
////        std::cout << "aPower B after mult" << std::endl;
//        B1 = shiftRight(b);
//        if (even(b)) {
////            std::cout << "aPower B even" << std::endl;
//            return aPowerB(A1, B1);
//        }
//        else {
////            std::cout << "aPower B else" << std::endl;
//            return mult(a, aPowerB(A1, B1));
//        }
//    }
    std::vector<int> z;
//    std::cout << "aPowerB mid" << std::endl;
    z = aPowerB(a, shiftRight(b));
    if(even(b)){
//        std::cout << "aPowerB even1" << std::endl;
        z = mult(z, z);
//        std::cout << "aPowerB even2" << std::endl;
        return z;
    }
    else{
//        std::cout << "aPowerB else" << std::endl;
        z = mult(z, z);
        z = mult(a, z);
        return z;
    }
//    std::cout << "aPowerB end" << std::endl;
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
    
    if (vec.size() == 0) return vec;
    std::vector<int> trimmed;
    trimmed = reverse(vec);
    
    while(trimmed.back() == 0) {
        trimmed = shiftRight(trimmed);
    }
    
//    for (int i = trimmed.size() - 1; i > 0; i--) {
//        if (trimmed.at(i) == 0)
//            trimmed.pop_back();
//    }
//    std::cout << "inside trim" << std::endl;
    return reverse(trimmed);
}

bool isOne(std::vector<int> vec) {
    // Returns true if vec == 1, false otherwise
    
    std::vector<int> one;
    one.push_back(1);
    
//    std::cout << "inside isOne" << std::endl;
    return equal(trim(vec), one);
//    return equal(vec, one);
    
//    if (Bin2Dec(vec) == "1") return true;
//    return false;
}

std::vector<int> modexp(std::vector<int> x, std::vector<int> y, std::vector<int> N) {
    // Pre-condition: integers x, y, N > 0
    // Post-condition: x^y mod N
    
    std::vector<int> z;
    if (zero(y)) {
        z.push_back(1);
        return z;
    }
    
    z = modexp(x, shiftRight(y), N);
    if (even(y)) {
        return mod(mult(z,z), N);
    }
    else {
        return mod(mult(x, mult(z, z)), N);
    }
}

bool primality2(std::vector<int> N, std::vector<std::vector<int> > aiVector) {
    // Pre-condition: N is a positive integer, 1 <= k <= N
    // Post-condition: Returns true if N is prime, false otherwise
    
    // ai ^ (N - 1)
    std::vector<int> exponent;
    
    // ai ^ (N - 1) mod N
    std::vector<int> modulus;
    
    std::vector<int> nMinusOne = subtractOne(N);
    
//    std::cout << Bin2Dec(N) << Bin2Dec(nMinusOne) << std::endl;
    for (int i = 0; i < aiVector.size(); i++) {
        modulus = modexp(aiVector.at(i), nMinusOne, N);
//        std::cout << Bin2Dec(aiVector.at(i)) << std::endl;
//        exponent = aPowerB(aiVector.at(i), nMinusOne);
//        modulus = mod(exponent, N);
        
//        std::cout << Bin2Dec(exponent) << " mod " << Bin2Dec(N) << " = " << Bin2Dec(modulus) << std::endl;
//        std::cout << Bin2Dec(modulus) << std::endl;
        if ( !isOne(modulus) ) return false;
    }
    return true;
}

bool primality(std::vector<int> N) {
    // Pre-condition: none
    // Post-condition: returns true (false) if N is prime
    // NO confidence level in this function
    std::vector<int> aSubI = dec2bin(3);
    std::vector<int> nMinusOne = subtractOne(N);
    std::vector<int> exponent = aPowerB(aSubI, nMinusOne);
    std::vector<int> modulus = mod(exponent, N);
    
    if ( !isOne(modulus) ) return false;
    return true;
}


static std::vector<int> dec2bin1(char c){
    // handles the case of single digit input. Ex: c = '5' produces output [1,0,1] etc.
    std::vector<int> temp;
    switch(c) {
        case '0':
            return temp;
        case '1':
            temp.push_back(1);
            return temp;
        case '2':
            temp.push_back(0);
            temp.push_back(1);
            return temp;
        case '3':
            temp.push_back(1);
            temp.push_back(1);
            return temp;
        case '4':
            temp.push_back(0);
            temp.push_back(0);
            temp.push_back(1);
            return temp;
        case '5':
            temp.push_back(1);
            temp.push_back(0);
            temp.push_back(1);
            return temp;
        case '6':
            temp.push_back(0);
            temp.push_back(1);
            temp.push_back(1);
            return temp;
        case '7':
            temp.push_back(1);
            temp.push_back(1);
            temp.push_back(1);
            return temp;
        case '8':
            temp.push_back(0);
            temp.push_back(0);
            temp.push_back(0);
            temp.push_back(1);
            return temp;
        case '9':
            temp.push_back(1);
            temp.push_back(0);
            temp.push_back(0);
            temp.push_back(1);
            return temp;
            
    }
    std::cout << "incorrect input" << std::endl; return temp; // code to avoid warning
}

bool exc_or(bool a, bool b, bool c){
    return a^(b^c);
}

//bool nextCarry(bool a, bool b, bool c) {
//    if ((a&b) | (b & c) | (c & a))
//        return true;
//    else
//        return false;
//}


static std::vector<int> add(std::vector<int> x, std::vector<int> y, bool carry) {
    if (x.size() == 0) {
        if (!carry)
            return y;
        else {
            std::vector<int> v1; v1.push_back(1);
            return add(v1, y, false);
        }
    }
    else if (y.size() == 0) {
        if (!carry)
            return x;
        else {
            std::vector<int> v1; v1.push_back(1);
            return add(x, v1, false);
        }
    }
    else {
        std::vector<int> x1 = x;
        x1.erase(x1.begin()); //////////////////////////////////
        std::vector<int> y1 = y;
        y1.erase(y1.begin());
        bool newcarry = nextCarry(x[0], y[0], carry);
        std::vector<int> temp = add(x1, y1, newcarry);
        temp.insert(temp.begin(), exc_or(x[0], y[0], carry));
        return temp;
    }
}

static std::vector<int> mult10(std::vector<int> num) {
    // multiplies a binary vector by 10
    // Example: input num = [0, 1], output = [0, 0, 1, 0, 1
    if (num.size() == 0)
        return num;
    std::vector<int> num1 = num;
    num1.insert(num1.begin(), 0);
    std::vector<int> num2 = num1;
    num2.insert(num2.begin(), 0);
    num2.insert(num2.begin(), 0);
    return add(num1, num2, false);
}

std::vector<int> longDec2Bin(std::string x)
// Ex: x = "23", y = [0, 0, 0, 0, 0, 1]
{
    if (x == "") {
        std::vector<int> temp;
        return temp;
    }
    else if (x.length() == 1)
        return dec2bin1(x[0]);
    else {
        std::vector<int> y = mult10(longDec2Bin(x.substr(1, x.size()-1)));
        std::vector<int> z = dec2bin1(x[0]);
        return add(y, z, false);
    }
}


std::vector<int> randBinGenerator(int n) {
    std::vector<int> result;
//    srand(time(NULL));
    result.push_back(1);
    
    for (int i = 0; i < n - 1; i++ ) {
        result.push_back(rand() % 2);
    }
    
    return result;
}

std::vector<int> generatePrime(int n, int k) {
    // Pre-condition: n is a positive integer <= 50
    // Post-condition: returns a vector containing a
    // prime number of n bits, represented in binary
    
    std::vector<int> prime;
    prime.push_back(1); // MSB must be 1
    
    for (int i = 1; i < n-1; i++) {
        prime.push_back(rand() % 2);
    }
    

    if(prime.back() == 0){
        prime.back() = 1;
    }
    
    std::vector<std::vector<int> > aSubI;
    for (int i = 0; i < k; i++) {
        aSubI.push_back(randBinGenerator(Bin2Dec(prime)));
    }
    
    
    // Test for primality:
//    std::vector<int> three;
//    three.push_back(1);
//    three.push_back(1);
//    
//    while (!primality2(prime, aSubI) || isOne(mod(prime, three))) {
//        prime = generatePrime(n, k);
//    }
//    return prime;
    std::vector<int> modulus;
    std::vector<int> three;
    three.push_back(1);
    three.push_back(1);
    std::vector<int> two;
    two.push_back(1);
    two.push_back(0);
    modulus = mod(prime, three);
    if (primality2(prime, aSubI) && equal(two, modulus)) {
        return prime;
    }
        
    else
        return generatePrime(n, k);
}

std::vector<int> shiftInverse2(std::vector<int> d, std::vector<int> N) {
    std::vector<int> result;
    result = add(d, N);
    return result;
}

std::vector<int> shiftInverse(std::vector<int> d, std::vector<int> N) {
    std::vector<int> result;
    result = subtract(N, d);
    return result;
}

std::vector<int> getModInverse(RSAKey key) {
    std::vector<int> result;
    std::vector<int> test;
    extEuclid modInverse;
    std::vector<int> e;
    e.push_back(1);
    e.push_back(1);
    std::vector<int> modulus;
    modulus = mult(subtractOne(key.p), subtractOne(key.q));
    
    modInverse = extendedEuclid(e, modulus);
//    std::cout << Bin2Dec(modInverse.x) << std::endl;
//    std::cout << modInverse.sign << std::endl;
    
    if (modInverse.sign == 1) {
        result = shiftInverse(modInverse.x, mult(subtractOne(key.p), subtractOne(key.q)));
//        std::cout << Bin2Dec(result) << std::endl;
//        std::cout << Bin2Dec(shiftInverse2(result, modulus)) << std::endl;
//        std::cout << "helloooo" << std::endl;
        test = mult(e, result);
        while(!isOne(mod(test, modulus))) {
            test = shiftInverse2(test, modulus);
//            std::cout << "after 2" << std::endl; print(test);
        }
//        result = test;
    }
    else {
        result = modInverse.x;
//        std::cout << "inside if" << std::endl; print(result);
    }
//    print(result);
//    test = mult(e, result);
//    
//    while(!isOne(mod(test, modulus))) {
//        test = shiftInverse2(test, modulus);
//    }
//    result = test;
    return result;
}


RSAKey rsaKeyGenerate(int n, int k) {
    // Pre-condition: n is a positive integer <= 50
    // Post-condition: prints two n-bit primes p, q in decimal
    // and prints N, which is p * q
    
    std::vector<int> p = generatePrime(n, k);
    std::vector<int> q = generatePrime(n, k);
    std::vector<int> three;
    three.push_back(1);
    three.push_back(1);
    while (equal(p,q)) {
        q = generatePrime(n, k);
    }
    std::vector<int> N = mult(p, q);
    RSAKey key;
    key.p = p;
    key.q = q;
    key.N = N;
    key.e.push_back(1);
    key.e.push_back(1);
    key.d = getModInverse(key);
    
    std::cout << "p: " << Bin2Dec(p) << std::endl;
    std::cout << "q: " << Bin2Dec(q) << std::endl;
    std::cout << "N: " << Bin2Dec(N) << std::endl;
    std::cout << "e: " << Bin2Dec(key.e) << std::endl;
    std::cout << "d: " << Bin2Dec(key.d) << std::endl;
    return key;
}


std::vector<int> strDec2Bin(std::string str){
    //keep track of last char in str to be converted to bin
    int endPos = 0;
    std::vector<int> result;
    
    //starting from last char in str, convert str to binary
    for(long long i = str.length()-1; i > -1; i--){
        //convert char at str[i] to a binary value
        std::vector<int> temp = dec2bin1(str[i]);
//        print(temp);
        for(int j = 0; j < endPos; j++){
            //temp * 10 to put value in correct position
            temp = mult10(temp);
        }
        //Add temp to result
        result = add(reverse(temp), result);
        //increment endPos
        endPos++;
    }
    
    //return result
    return result;
}

std::vector<int> randBinGenerator(std::string str){
    std::vector<int> result;
    //since the least amount any value can be divided by is 2, divide
    //convert str to binary representation and divide by 2;
//    std::vector<int> N = shiftRight(strDec2Bin(str));
    std::vector<int> N = strDec2Bin(str);
    do{
        //create a temp array for creating a random binary number
        std::vector<int> temp;
        //ensure most significant bit = 1
        temp.push_back(1);
        
        //create a randomSize for the temp array that is 0 < randSize <= N
//        srand((unsigned int)time(NULL));
        int randSize = (rand()%N.size());        
        
        //insert random bits into temp
        for(int i = 1; i < randSize; i++){
//            srand((unsigned int)time(NULL));
            temp.push_back(rand()%2);
        }
        //result = temp
        result = temp;
    }//if result > N, try again
    while(!lessThan(result, N));
//    print(result);
//    print(N);
    return result;
}

std::vector<int> rsaEncrypt(std::vector<int> message, std::vector<int> exponent, std::vector<int> N) {
    std::vector<int> result;
//    std::cout << "test2" << std::endl;
//    std::cout << Bin2Dec(message) << std::endl;
//    std::cout << Bin2Dec(exponent) << std::endl;
//    std::cout << Bin2Dec(N) << std::endl;
    
    result = modexp(message, exponent, N);
//    std::cout << Bin2Dec(message) << std::endl;
//    std::cout << Bin2Dec(exponent) << std::endl;
//    result = mod( aPowerB(message, exponent), N);

    
    //    std::cout << "test3" << std::endl;
    return result;
}

void printDec(std::vector<int> printMe){
    std::cout << Bin2Dec(printMe) << std::endl;
}


#endif	/* HW1_HPP */

