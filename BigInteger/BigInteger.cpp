#include <iostream>
#include "BigInteger.h"
#include "List.h"

const int power = 9;
const long base = 1000000000;

BigInteger::BigInteger() {
    this->digits = List();
    this->signum = 0;
}

//Helper
bool needCarry(const long x){
    if(x >= base){
        return true;
    } else if (x <= -base){
        return true;
    } else{
        return false;
    }
}

bool isZero(List&L){
    int x = 0;
    L.moveBack();
    while (L.position() > 0){
        if (L.peekPrev() == 0){
            x++;
        }
        L.movePrev();
    }
    if (x == L.length()){
        return true;
    }
    return false;
}

void leadZero(List &L){
    L.moveFront();
    while (L.peekNext() == 0){
        L.eraseAfter();
    }
}

int checkNeg(List &L){
    L.moveFront();
    if (L.front() < 0){
        int x = L.front() * -1;
        L.eraseAfter();
        L.insertAfter(x);
        return -1;
    }
    return 1;
}

int Normalize(List &L){
    if (isZero(L)) {
        L.clear();
        return 0;
    }
    leadZero(L);
    L.moveBack();
    long carry = 0;
    while (L.position() > 0) {
        long x = L.peekPrev() + carry;
        if (x < 0) {
            carry = -1;
            x += base;
        } else if (x >= base) {
            carry = x / base;
            x %= base;
        } else {
            carry = 0;
        }
        L.eraseBefore();
        L.insertBefore(x);
        L.movePrev();
    }
    L.moveFront();
    if (L.front() < 0) {
        L.moveFront();
        while (L.position() < L.length()) {
            long val = L.peekNext();
            L.setAfter(-val);
        }
        return -1;
    }
    leadZero(L);
    return 1;
}

//Constructor


BigInteger::BigInteger(long x) {
    this->digits = List();
    if (x > 0){
        this->signum = 1;
    } else if (x < 0){
        this->signum = -1;
    }else {
        this->signum = 0;
        return;
    }

    this->digits.insertBefore(x);
    Normalize(this->digits);
}

BigInteger::BigInteger(std::string s) {
    this->digits = List();
    int startIdx = 0;
    if (s[0] == '-') {
        this->signum = -1;
        startIdx = 1;
    } else if (s[0] == '+') {
        this->signum = 1;
        startIdx = 1;
    } else {
        this->signum = 1;
    }

    for (int i = s.length(); i > startIdx; i -= power) {
        int chunkStart = std::max(startIdx, i - power);
        std::string chunk = s.substr(chunkStart, i - chunkStart);
        long chunkValue = std::stol(chunk);
        this->digits.insertAfter(chunkValue);
    }

    if (this->digits.length() == 1 && this->digits.front() == 0) {
        this->digits.clear();
        this->signum = 0;
        return;
    }
    Normalize(digits);
}

BigInteger::BigInteger(const BigInteger &N) {
    this->signum = N.signum;
    this->digits = N.digits;
}

//Helper
int equals(List A, List B){
    A.moveFront();
    B.moveFront();
    while (A.position() < A.length()){
        if (A.peekNext() == B.peekNext()){
            A.moveNext();
            B.moveNext();
            continue;
        } else if (A.peekNext() > B.peekNext()){
            return 1;
        } else if (A.peekNext() < B.peekNext()){
            return -1;
        }
    }
}

// Access
int BigInteger::sign() const {
    return this->signum;
}

int BigInteger::compare(const BigInteger &N) const {
    if (this->signum > N.signum){
        return 1;
    } else if (this->signum < N.signum){
        return -1;
    } else if (this->signum == 0 && N.signum == 0){
        return 0;
    }else if(this->signum == N.signum && this->signum == 1){
        if (this->digits.length() > N.digits.length()){
            return 1;
        } else if (this->digits.length() < N.digits.length()){
            return -1;
        } else{
            return equals(this->digits, N.digits);
        }
    } else if(this->signum == N.signum && this->signum == -1){
        if (this->digits.length() < N.digits.length()){
            return 1;
        } else if (this->digits.length() > N.digits.length()){
            return -1;
        } else{
            return equals( N.digits, this->digits);
        }
    }


}


// Manipulation
void BigInteger::makeZero() {
    this->digits.clear();
    this->signum = 0;
}

void BigInteger::negate() {
    if(this->sign() == -1) {
        this->signum = 1;
    } else if(this->sign() == 1){
        this->signum = -1;
    }
}


//Arithmatic Helpers
void sumList(List &S, List A, List B, int signA, int signB){
    A.moveBack();
    B.moveBack();
    while (A.position() > 0 || B.position() > 0){
        if (A.position() == 0){
            S.insertAfter(B.peekPrev() * signB);
            B.movePrev();
            continue;
        } else if (B.position() == 0){
            S.insertAfter(A.peekPrev() * signA);
            A.movePrev();
            continue;
        } else {
            long x = (A.peekPrev() * signA) + (B.peekPrev() * signB);
            S.insertAfter(x);
            A.movePrev();
            B.movePrev();
        }
    }
}

void mul(List &S, List A, List B){
    List partial;
    A.moveBack();
    int shift = 0;
    while (A.position() > 0) {
        long x = A.peekPrev();
        B.moveBack();
        partial.clear();
        for (int i = 0; i < shift; ++i) {
            partial.insertAfter(0);
        }
        long carry = 0;
        while (B.position() > 0) {
            long y = B.peekPrev();
            long product = x * y + carry;
            partial.insertAfter(product % base);
            carry = product / base;
            B.movePrev();
        }

        if (carry > 0) {
            partial.insertAfter(carry);
        }
        List temp = S;
        S.clear();
        sumList(S, temp, partial, 1, 1);

        A.movePrev();
        ++shift;
    }

}

//Arithmetic
BigInteger BigInteger::add(const BigInteger &N) const {
    List S = List();
    BigInteger out = BigInteger();
    if (N.sign() != 0){
        sumList(S, this->digits, N.digits, this->signum, N.signum);
        int x = Normalize(S);
        out.digits = S;
        out.signum = x;
    }
    return out;
}

BigInteger BigInteger::sub(const BigInteger &N) const {
    List S = List();
    BigInteger out = BigInteger();
    if (N.sign() != 0){
        int x = this->compare(N);
        if (x == -1){
            sumList(S, N.digits, this->digits, N.signum * -1, this->signum * -1);
        } else{
            sumList(S, this->digits, N.digits, this->signum, (N.signum * -1));
        }
        int y = Normalize(S);
        out.digits = S;
        out.signum = y;
        if (x == -1){
            out.signum = out.signum * -1;
        }
    }
    return out;
}

BigInteger BigInteger::mult(const BigInteger &N) const {
    List S = List();
    BigInteger out = BigInteger();
    if (this->signum == 0|| N.signum == 0){
        out.digits = S;
        out.signum = 0;
        return out;
    } else{
        mul(S, this->digits, N.digits);
        int x = Normalize(S);
        out.digits = S;
        out.signum = this->signum * N.signum;
        return out;
    }
}

//Other
std::string BigInteger::to_string() {
    std::string out = "";
    if(this->signum == 0){
        out = "0";
        return out;
    } else if(this->signum == -1){
        out = "-";
    }
    this->digits.moveFront();
    int i = 0;
    while (this->digits.position() < this->digits.length()){
        std::string temp = std::to_string(this->digits.peekNext());
        while (temp.length() != power && i != 0){
            temp = "0" + temp;
        }
        out = out + temp;
        temp = "";
        this->digits.moveNext();
        i++;
    }
    return out;
}

//Overridden
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    stream << N.to_string();
    return stream;
}

bool operator==( const BigInteger& A, const BigInteger& B ){
    if (A.digits == B.digits && A.signum == B.signum){
        return true;
    } else {
        return false;
    }
}

bool operator<( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1){
        return true;
    } else{
        return false;
    }
}

bool operator<=( const BigInteger& A, const BigInteger& B ){
    if (A.digits.equals(B.digits) && A.signum == B.signum){
        return true;
    } else if (A.compare(B) == 0 || A.compare(B) == -1){
        return true;
    } else{
        return false;
    }
}

bool operator>( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1){
        return true;
    } else{
        return false;
    }
}

bool operator>=( const BigInteger& A, const BigInteger& B ){
    if (A.digits.equals(B.digits) && A.signum == B.signum){
        return true;
    } else if (A.compare(B) == 0 || A.compare(B) == 1){
        return true;
    } else{
        return false;
    }
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    List S = List();
    BigInteger out = BigInteger();
    if (A.signum == 1 && B.signum == -1 ){
        BigInteger negB = BigInteger(B);
        negB.negate();
        out = (A-negB);
        return out;
    }
    if (A.signum == -1 && B.signum == -1 ){
        BigInteger negB = BigInteger(B);
        negB.negate();
        out = (A-negB);
        return out;
    }
    if (B.sign() != 0){
        sumList(S, A.digits, B.digits, A.signum, B.signum);
        int x = Normalize(S);
        out.digits = S;
        out.signum = x;
    }
    return out;
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    List S = List();
    if (B.sign() != 0){
        if (A.signum == 1 && B.signum == -1){
            BigInteger negB = BigInteger(B);
            negB.negate();
            A = (A-negB);
            return A;
        }
        if (A.signum == -1 && B.signum == -1){
            BigInteger negB = BigInteger(B);
            negB.negate();
            A = (A-negB);
            return A;
        }
        sumList(S, A.digits, B.digits, A.signum, B.signum);
        int x = Normalize(S);
        A.digits = S;
        A.signum = x;
    }
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    List S = List();
    BigInteger out = BigInteger();
    if (B.sign() != 0){
        int x = A.compare(B);
        if (x == -1){
            sumList(S, B.digits, A.digits, B.signum, (A.signum * -1));
        } else{
            sumList(S, A.digits, B.digits, A.signum, (B.signum * -1));
        }
        int y = Normalize(S);
        out.digits = S;
        out.signum = y;
        if (x == -1){
            out.signum = out.signum * -1;
        }
    }
    return out;
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    List S = List();
    if (B.sign() != 0){
        int x = A.compare(B);
        if (x == -1){
            sumList(S, B.digits, A.digits, B.signum, (A.signum * -1));
        } else{
            sumList(S, A.digits, B.digits, A.signum, (B.signum * -1));
        }
        int y = Normalize(S);
        A.digits = S;
        A.signum = y;
        if (x == -1){
            A.signum = A.signum * -1;
        }
    }
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    List S = List();
    BigInteger out = BigInteger();
    if (A.signum == 0|| B.signum == 0){
        out.digits = S;
        out.signum = 0;
        return out;
    } else{
        mul(S, A.digits, B.digits);
        int x = Normalize(S);
        out.digits = S;
        out.signum = A.signum * B.signum;
        return out;
    }
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    List S = List();
    if (A.signum == 0|| B.signum == 0){
        A.digits = S;
        A.signum = 0;
        return A;
    } else{
        mul(S, A.digits, B.digits);
        Normalize(S);
        A.digits = S;
        A.signum = A.signum * B.signum;
        return A;
    }
}
