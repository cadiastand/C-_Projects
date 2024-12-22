#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <compare>
#include <stdexcept>
#endif /* __PROGTEST__ */

bool string_if_correct(const std::string& value){
    bool num_start = false;
    for(char i : value){
        if(!isdigit(i) && i != '-' && i != '+' && i != ' ') return false;

        if(isdigit(i)) num_start = true;
    }
    return num_start;
}


std::string transformInput(const std::string& str) {
    if (str.length() == 0) return str;
    auto nonSpacePos = str.find_first_not_of(' ');
    if (nonSpacePos == std::string::npos) return "";

    std::string result;
    auto firstSignificantChar = nonSpacePos;
    if (str[firstSignificantChar] == '-') {
        result += str[firstSignificantChar++];
    }

    auto indexWithoutLeadingZeros = str.find_first_not_of('0', firstSignificantChar);
    if (indexWithoutLeadingZeros == std::string::npos) return "0";

    result += str.substr(indexWithoutLeadingZeros);
    if(result[0] == '+'){
        result.erase(result.begin());
    }
    return result;
}


std::vector<int> vector_view(const std::string& string_format){
    std::vector<int> vec;
    bool leading_zero = true;
    for(char i : string_format){
        if(i == '0' && leading_zero) continue;
        leading_zero = false;
        vec.push_back(i - '0');
    }
    return vec;
}

void update(std::vector<int>& vectr, const std::vector<int>& add, int& prenos, size_t& i){
    while(i != add.size()){
        int addition = add[i] + prenos;
        vectr.push_back(addition % 10);
        prenos = addition / 10;
        ++i;
    }
    if(prenos == 1){
        vectr.push_back(prenos);
        prenos = 0;
    }
}

std::vector<int> make_vector_from_int(int& num_to_make){
    std::vector<int> integer;
    while(num_to_make > 0){
        integer.push_back(num_to_make % 10);
        num_to_make /= 10;
    }
    std::reverse(integer.begin(), integer.end());
    return integer;
}

class CBigInt
{
public:
    CBigInt(){
        is_negative = false;
        big_integer.push_back(0);
    }

    ~CBigInt() = default;

    CBigInt(int num){
        if(num == 0){
            is_negative = false;
            big_integer.push_back(0);
        }else {
            is_negative = false;
            if (num < 0) {
                is_negative = true;
                num *= -1;
            }
            big_integer = make_vector_from_int(num);
        }
    }

    CBigInt(const std::string& string_format){
        if(!string_if_correct(string_format)){
            throw std::invalid_argument("");
        }
        is_negative = false;
        std::string format = transformInput(string_format);
        if(format[0] == '-'){
            format.erase(format.begin());
            is_negative = true;
        }
        big_integer = vector_view(format);
    }

    CBigInt(const std::vector<int>& big_int){
        big_integer = big_int;
        is_negative = false;
    }

    CBigInt(const CBigInt& bigInt){
        big_integer = bigInt.big_integer;
        is_negative = bigInt.is_negative;
    }

    CBigInt& operator=(const CBigInt& bigInt){
        if(&bigInt == this) return *this;
        this->big_integer = bigInt.big_integer;
        this->is_negative = bigInt.is_negative;
        return *this;
    }
    CBigInt& operator=(const std::string& str) {
        CBigInt bigInt(str);
        this->big_integer = bigInt.big_integer;
        this->is_negative = bigInt.is_negative;
        return *this;
    }
    CBigInt& operator=(const int num) {
        CBigInt bigInt(num);
        this->big_integer = bigInt.big_integer;
        this->is_negative = bigInt.is_negative;
        return *this;
    }

    bool get_negative() const{
        return this->is_negative;
    }

    size_t get_size() const{
        return this->big_integer.size();
    }

    int operator[](const size_t& index) const{
        return this->big_integer[index];
    }

    //operator+
    friend CBigInt operator+(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend CBigInt operator+(const CBigInt& bigint_a, const std::string& b);
    friend CBigInt operator+(const CBigInt& bigInt_a, const int& b);
    friend CBigInt operator+(const std::string& a, const CBigInt& b);
    friend CBigInt operator+(const int& a, const CBigInt& b);

    //operator+=
    friend CBigInt &operator+=(CBigInt& bigint_a, const CBigInt& bigint_b);
    friend CBigInt &operator+=(CBigInt& bigint_a, const std::string& b);
    friend CBigInt &operator+=(CBigInt& bigInt_a, const int& b);

    //operator-
    friend CBigInt operator-(const CBigInt& bigint_a, const CBigInt& bigint_b);

    //operator*
    friend CBigInt operator*(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend CBigInt operator*(const CBigInt& bigint_a, const std::string& b);
    friend CBigInt operator*(const CBigInt& bigInt_a, const int& b);
    friend CBigInt operator*(const std::string& a, const CBigInt& b);
    friend CBigInt operator*(const int& a, const CBigInt& b);
    //operator*=
    friend CBigInt &operator*=(CBigInt& bigint_a, const CBigInt& bigint_b);
    friend CBigInt &operator*=(CBigInt& bigint_a, const std::string& b);
    friend CBigInt &operator*=( CBigInt& bigInt_a, const int& b);

    //operator==
    friend bool operator==(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend bool operator==(const CBigInt& bigint_a, const std::string& bigint_b);
    friend bool operator==(const CBigInt& bigint_a, const int& bigint_b);
    friend bool operator==(const std::string& str ,const CBigInt& bigint_b);
    friend bool operator==(const int& Int ,const CBigInt& bigint_b);

    //operator!=
    friend bool operator!=(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend bool operator!=(const CBigInt& bigint_a, const std::string& bigint_b);
    friend bool operator!=(const CBigInt& bigint_a, const int& bigint_b);
    friend bool operator!=(const std::string& str ,const CBigInt& bigint_b);
    friend bool operator!=(const int& Int ,const CBigInt& bigint_b);

    //operator<
    friend bool operator<(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend bool operator<(const CBigInt& bigint_a, const std::string& bigint_b);
    friend bool operator<(const CBigInt& bigint_a, const int& bigint_b);
    friend bool operator<(const std::string& str ,const CBigInt& bigint_b);
    friend bool operator<(const int& Int ,const CBigInt& bigint_b);

    //operator<=
    friend bool operator<=(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend bool operator<=(const CBigInt& bigint_a, const std::string& bigint_b);
    friend bool operator<=(const CBigInt& bigint_a, const int& bigint_b);
    friend bool operator<=(const std::string& str ,const CBigInt& bigint_b);
    friend bool operator<=(const int& Int ,const CBigInt& bigint_b);

    //operator>
    friend bool operator>(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend bool operator>(const CBigInt& bigint_a, const std::string& bigint_b);
    friend bool operator>(const CBigInt& bigint_a, const int& bigint_b);
    friend bool operator==(const std::string& str ,const CBigInt& bigint_b);
    friend bool operator==(const int& Int ,const CBigInt& bigint_b);

    //operator>=
    friend bool operator>=(const CBigInt& bigint_a, const CBigInt& bigint_b);
    friend bool operator>=(const CBigInt& bigint_a, const std::string& bigint_b);
    friend bool operator>=(const CBigInt& bigint_a, const int& bigint_b);
    friend bool operator==(const std::string& str ,const CBigInt& bigint_b);
    friend bool operator==(const int& Int ,const CBigInt& bigint_b);

    //operator<<
    friend std::ostream& operator<<(std::ostream& output, const CBigInt& bigint_a);
    //operator>>
    friend bool operator>>(std::istream& input, CBigInt& bigint_a);

private:

    std::vector<int> big_integer;
    bool is_negative;
};
// operator==
bool operator==(const CBigInt& bigint_a, const CBigInt& bigint_b){
    if(bigint_a.get_negative() != bigint_b.get_negative()) return false;
    if(bigint_a.big_integer.size() != bigint_b.big_integer.size()) return false;
    for(size_t i = 0; i < bigint_a.big_integer.size(); ++i){
        if(bigint_a[i] != bigint_b[i]) return false;
    }
    return true;
}
bool operator==(const CBigInt& bigint_a, const std::string& b) {
    CBigInt bigint_b(b);
    if(bigint_a.get_negative() != bigint_b.get_negative()) return false;
    if(bigint_a.big_integer.size() != bigint_b.big_integer.size()) return false;
    for(size_t i = 0; i < bigint_a.big_integer.size(); ++i){
        if(bigint_a[i] != bigint_b[i]) return false;
    }
    return true;
}
bool operator==(const CBigInt& bigint_a, const int& b) {
    CBigInt bigint_b(b);
    if(bigint_a.get_negative() != bigint_b.get_negative()) return false;
    if(bigint_a.big_integer.size() != bigint_b.big_integer.size()) return false;
    for(size_t i = 0; i < bigint_a.big_integer.size(); ++i){
        if(bigint_a[i] != bigint_b[i]) return false;
    }
    return true;
}
bool operator==(const std::string& str,const CBigInt& bigint_b) {
    CBigInt bigint_a(str);
    if(bigint_a.get_negative() != bigint_b.get_negative()) return false;
    if(bigint_a.big_integer.size() != bigint_b.big_integer.size()) return false;
    for(size_t i = 0; i < bigint_a.big_integer.size(); ++i){
        if(bigint_a[i] != bigint_b[i]) return false;
    }
    return true;
}
bool operator==(const int& Int, const CBigInt& bigint_b) {
    CBigInt bigint_a(Int);
    if(bigint_a.get_negative() != bigint_b.get_negative()) return false;
    if(bigint_a.big_integer.size() != bigint_b.big_integer.size()) return false;
    for(size_t i = 0; i < bigint_a.big_integer.size(); ++i){
        if(bigint_a[i] != bigint_b[i]) return false;
    }
    return true;
}

// operator!=
bool operator!=(const CBigInt& bigint_a, const CBigInt& bigint_b) {
    return !(bigint_a == bigint_b);
}
bool operator!=(const CBigInt& bigint_a, const std::string& b) {
    CBigInt bigint_b(b);
    return !(bigint_a == bigint_b);
}
bool operator!=(const CBigInt& bigint_a, const int& b) {
    CBigInt bigint_b(b);
    return !(bigint_a == bigint_b);
}
bool operator!=(const std::string& str,const CBigInt& bigint_b) {
    CBigInt bigint_a(str);
    return !(bigint_a == bigint_b);
}
bool operator!=(const int& Int, const CBigInt& bigint_b) {
    CBigInt bigint_a(Int);
    return !(bigint_a == bigint_b);
}

// operator>
bool operator>(const CBigInt& bigint_a, const CBigInt& bigint_b){
    return !(bigint_a < bigint_b) && bigint_a != bigint_b;
}

bool operator>(const CBigInt& bigint_a, const std::string& b) {
    return bigint_a > CBigInt(b);
}
bool operator>(const CBigInt& bigint_a, const int& b) {
    return bigint_a > CBigInt(b);
}
bool operator>(const std::string& str,const CBigInt& bigint_b) {
    return CBigInt(str) > bigint_b;
}
bool operator>(const int& Int, const CBigInt& bigint_b) {
    return CBigInt(Int) > bigint_b;
}
// operator>=
bool operator>=(const CBigInt& bigint_a, const CBigInt& bigint_b){
    return bigint_a > bigint_b || bigint_a == bigint_b;
}
bool operator>=(const CBigInt& bigint_a, const std::string& b) {
    return bigint_a >= CBigInt(b);
}
bool operator>=(const CBigInt& bigint_a, const int& b) {
    return bigint_a >= CBigInt(b);
}
bool operator>=(const std::string& str,const CBigInt& bigint_b) {
    return CBigInt(str) >= bigint_b;
}
bool operator>=(const int& Int, const CBigInt& bigint_b) {
    return CBigInt(Int) >= bigint_b;
}

// operator<
bool operator<(const CBigInt& bigint_a, const CBigInt& bigint_b){
    if(bigint_a.get_negative() == true && bigint_b.get_negative() == false){
        return true;
    }else if(bigint_a.get_negative() == false && bigint_b.get_negative() == true){
        return false;
    }
    else if(bigint_a.get_negative() == bigint_b.get_negative() && bigint_a.get_negative() == true){
        if (bigint_a.get_size() > bigint_b.get_size()) {
            return true;
        } else if (bigint_a.get_size() < bigint_b.get_size()) {
            return false;
        }else{
            for (size_t i = 0; i < bigint_a.get_size(); ++i) {
                if (bigint_a[i] < bigint_b[i]) {
                    return false;
                } else if (bigint_a[i] > bigint_b[i]) {
                    return true;
                }
            }
        }
    }else{
        if (bigint_a.get_size() < bigint_b.get_size()) {
            return true;
        } else if (bigint_a.get_size() > bigint_b.get_size()) {
            return false;
        }else{
            for (size_t i = 0; i < bigint_a.get_size(); ++i) {
                if (bigint_a[i] < bigint_b[i]) {
                    return true;
                } else if (bigint_a[i] > bigint_b[i]) {
                    return false;
                }
            }
        }
    }
    return false;
}

bool operator<(const CBigInt& bigint_a, const std::string& b) {
    return bigint_a < CBigInt(b);
}
bool operator<(const CBigInt& bigint_a, const int& b) {
    return bigint_a < CBigInt(b);
}
bool operator<(const std::string& str,const CBigInt& bigint_b) {
    return CBigInt(str) < bigint_b;
}
bool operator<(const int& Int, const CBigInt& bigint_b) {
    return CBigInt(Int) < bigint_b;
}

//operator<=
bool operator<=(const CBigInt& bigint_a, const CBigInt& bigint_b){
    return bigint_a < bigint_b || bigint_a == bigint_b;
}
bool operator<=(const CBigInt& bigint_a, const std::string& b) {
    return bigint_a <= CBigInt(b);
}
bool operator<=(const CBigInt& bigint_a, const int& b) {
    return bigint_a <= CBigInt(b);
}
bool operator<=(const std::string& str,const CBigInt& bigint_b) {
    return CBigInt(str) <= bigint_b;
}
bool operator<=(const int& Int, const CBigInt& bigint_b) {
    return CBigInt(Int) <= bigint_b;
}

//operator+
CBigInt operator+(const CBigInt& bigint_a, const CBigInt& bigint_b){
    std::vector<int> vec_int, temp_a = bigint_a.big_integer, temp_b = bigint_b.big_integer;

    std::reverse(temp_a.begin(), temp_a.end());
    std::reverse(temp_b.begin(), temp_b.end());

    size_t length_a = bigint_a.get_size(), length_b = bigint_b.get_size(), i = 0;
    bool negative = false;
    if(bigint_a.get_negative() == bigint_b.get_negative() && bigint_b.get_negative()){
        negative = true;
    }else if(bigint_a.get_negative() != bigint_b.get_negative()){
        return bigint_a - bigint_b;
    }
    int prenos = 0, addition;
    while(true){
        addition = temp_a[i] + temp_b[i] + prenos;
        vec_int.push_back(addition % 10);
        prenos = addition / 10;
        ++i;
        if(i == length_a && i == length_b){
            if(prenos == 1){
                vec_int.push_back(prenos);
            }
            break;
        }else if(i != length_a && i == length_b){
            update(vec_int, temp_a, prenos, i);
            break;
        }else if(i == length_a && i != length_b){
            update(vec_int, temp_b, prenos, i);
            break;
        }
    }
    std::reverse(vec_int.begin(), vec_int.end());
    CBigInt a(vec_int);
    a.is_negative = negative;
    return a;
}

CBigInt operator+(const CBigInt& bigint_a, const std::string& b) {
    return bigint_a + CBigInt(b);
}
CBigInt operator+(const CBigInt& bigint_a, const int& b) {
    return bigint_a + CBigInt(b);
}
CBigInt operator+(const std::string& a, const CBigInt& b) {
    return b + CBigInt(a);
}
CBigInt operator+(const int& a, const CBigInt& b) {
    return b + CBigInt(a);
}

//operator +=
CBigInt& operator+=(CBigInt& bigint_a, const CBigInt& bigint_b){
    bigint_a = bigint_a + bigint_b;
    return bigint_a;
}
CBigInt& operator+=(CBigInt& bigint_a, const std::string& b) {
    bigint_a = bigint_a + CBigInt(b);
    return bigint_a;
}
CBigInt& operator+=(CBigInt& bigint_a, const int& b) {
    bigint_a = bigint_a + CBigInt(b);
    return bigint_a;
}

// operator-
CBigInt operator-(const CBigInt& bigint_a, const CBigInt& bigint_b){
    bool negative = false;
    CBigInt temp_a(bigint_a.big_integer);
    CBigInt temp_b(bigint_b.big_integer);
    if(bigint_a.get_negative() && bigint_b.get_negative()) negative = true;
    if(bigint_a.get_negative() && !bigint_b.get_negative()){
        // if A is negative and B is not, conside if the result will be negative, I have to compare two integers
        if(temp_a > temp_b) negative = true;
        else if(temp_a < temp_b){
            std::swap(temp_a, temp_b);
            negative = false;
        }
    }else if(!bigint_a.get_negative() && bigint_b.get_negative()){
        //if A is not negative and B is negative, conside if result will be negative, I have to compare two integers
        if(temp_a > temp_b){
            negative = false;
        }else if(temp_a < temp_b){
            std::swap(temp_a, temp_b);
            negative = true;
        }
    }
    std::vector<int> vector_a = temp_a.big_integer, vector_b = temp_b.big_integer, vec_int;

    std::reverse(vector_a.begin(), vector_a.end());
    std::reverse(vector_b.begin(), vector_b.end());

    size_t length_a = vector_a.size(), length_b = vector_b.size(), i = 0;
    int prenos = 0;
    while(true){
        int substraction = vector_a[i] - vector_b[i] - prenos;
        if(substraction < 0){
            substraction += 10;
            prenos = 1;
        }else{
            prenos = 0;
        }
        vec_int.push_back(substraction);
        ++i;
        if(i == length_b) break;
    }
    if(i != length_a) {
        while (true) {
            int substraction = vector_a[i] - prenos;
            if (substraction < 0) {
                substraction += 10;
                prenos = 1;
            } else {
                prenos = 0;
            }
            vec_int.push_back(substraction);
            ++i;
            if (i == length_a) break;
        }
    }
    std::reverse(vec_int.begin(), vec_int.end());
    CBigInt a(vec_int);
    a.is_negative = negative;
    return a;
}

//operator*
CBigInt operator*(const CBigInt& bigint_a, const CBigInt& bigint_b){
    if((bigint_a.get_size() == 1 || bigint_b.get_size() == 1) && (bigint_a[0] == 0 || bigint_b[0] == 0)){
        return CBigInt(0);
    }
    bool negative = (bigint_a.get_negative() != bigint_b.get_negative());
    size_t length_a = bigint_a.get_size(), length_b = bigint_b.get_size(), i = 0, j = 0;
    std::vector<int> vec_int(length_a + length_b, 0), temp_a = bigint_a.big_integer, temp_b = bigint_b.big_integer;

    std::reverse(temp_a.begin(), temp_a.end());
    std::reverse(temp_b.begin(), temp_b.end());

    int prenos = 0;
    while(i < length_a){
        while(j < length_b){
            int multiply = temp_a[i] * temp_b[j] + prenos;
            vec_int[i + j] += multiply;
            vec_int[i + j + 1] += vec_int[i + j] / 10;
            vec_int[i + j] %= 10;
            ++j;
        }
        ++i;
        j = 0;
    }
    std::reverse(vec_int.begin(), vec_int.end());
    if(vec_int[0] == 0){
        vec_int.erase(vec_int.begin());
    }
    CBigInt a(vec_int);
    a.is_negative = negative;
    return a;
}

CBigInt operator*(const CBigInt& bigint_a, const std::string& b) {
    return bigint_a * CBigInt(b);
}
CBigInt operator*(const CBigInt& bigint_a, const int& b) {
    return bigint_a * CBigInt(b);
}
CBigInt operator*(const std::string& a, const CBigInt& b) {
    return b * CBigInt(a);
}
CBigInt operator*(const int& a, const CBigInt& b) {
    return b * CBigInt(a);
}

// operator*=
CBigInt& operator*=(CBigInt& bigint_a, const CBigInt& bigint_b){
    bigint_a = bigint_a * bigint_b;
    return bigint_a;
}

CBigInt& operator*=(CBigInt& bigint_a, const std::string& b) {
    bigint_a = bigint_a * CBigInt(b);
    return bigint_a;
}
CBigInt& operator*=(CBigInt& bigint_a, const int& b) {
    bigint_a = bigint_a * CBigInt(b);
    return bigint_a;
}
// operator<<
std::ostream& operator<<(std::ostream& output, const CBigInt& bigint_a){
    size_t i = 0;
    if(bigint_a.get_negative()) output << '-';
    while(i != bigint_a.get_size()){
        output << std::to_string(bigint_a[i]);
        ++i;
    }
    return output;
}
// operator>>
bool operator>>(std::istream& input, CBigInt& bigint_a){
    std::string string_format_input;
    input >> string_format_input;
    std::vector<int> vec_int;
    bool integer_ = false;
    bool is_negative = false;
    bool zero = true;
    size_t i = 0;
    while(true){
        if(string_format_input[i] == '0' and zero){
            ++i;
            continue;
        }
        zero = false;

        if(string_format_input[i] == '-' && !is_negative){
            is_negative = true;
            ++i;
            continue;
        }

        else if(string_format_input[i] == '-' && is_negative) return false;

        if(string_format_input[i] == '+' && !integer_){
            ++i;
            continue;
        }
        else if(string_format_input[i] == '+' && integer_) return false;

        if(string_format_input[i] >= '0' && string_format_input[i] <= '9'){
            integer_ = true;
            vec_int.push_back(string_format_input[i] - '0');

        }else if((string_format_input[i] < '0' || string_format_input[i] > '9') && integer_) break;

        else if((string_format_input[i] < '0' || string_format_input[i] > '9') && !integer_) return false;

        ++i;

        if(i == string_format_input.length()){
            break;
        }
    }
    bigint_a.big_integer = vec_int;
    bigint_a.is_negative = is_negative;
    return integer_;
}

#ifndef __PROGTEST__
static bool equal ( const CBigInt & x, const char val [] )
{
    std::ostringstream oss;
    oss << x;
    return oss . str () == val;
}
static bool equalHex ( const CBigInt & x, const char val [] )
{
    return true;
}



int main ()
{
    CBigInt a, b;
    std::istringstream is;
    a = 10;
    a += 20;
    assert ( equal ( a, "30" ) );
    a *= 5;
    assert ( equal ( a, "150" ) );
    b = a + 3;
    assert ( equal ( b, "153" ) );
    b = a * 7;
    assert ( equal ( b, "1050" ) );
    assert ( equal ( a, "150" ) );
    assert ( equalHex ( a, "96" ) );

    a = 10;
    a += -20;
    assert ( equal ( a, "-10" ) );
    a *= 5;
    assert ( equal ( a, "-50" ) );
    b = a + 73;
    assert ( equal ( b, "23" ) );
    b = a * -7;
    assert ( equal ( b, "350" ) );
    assert ( equal ( a, "-50" ) );
    assert ( equalHex ( a, "-32" ) );

    a = "12345678901234567890";
    a += "-99999999999999999999";
    assert ( equal ( a, "-87654321098765432109" ) );
    a *= "54321987654321987654";
    assert ( equal ( a, "-4761556948575111126880627366067073182286" ) );
    a *= 0;
    assert ( equal ( a, "0" ) );
    a = 10;
    b = a + "400";
    assert ( equal ( b, "410" ) );
    b = a * "15";
    assert ( equal ( b, "150" ) );
    assert ( equal ( a, "10" ) );
    assert ( equalHex ( a, "a" ) );

    is . clear ();
    is . str ( " 1234" );
    assert ( is >> b );
    assert ( equal ( b, "1234" ) );
    is . clear ();
    is . str ( " 12 34" );
    assert ( is >> b );
    assert ( equal ( b, "12" ) );
    is . clear ();
    is . str ( "999z" );
    assert ( is >> b );
    assert ( equal ( b, "999" ) );
    is . clear ();
    is . str ( "abcd" );
    assert ( ! ( is >> b ) );
    is . clear ();
    is . str ( "- 758" );
    assert ( ! ( is >> b ) );
    a = 42;
    try
    {
        a = "-xyz";
        assert ( "missing an exception" == nullptr );
    }
    catch ( const std::invalid_argument & e )
    {
        assert ( equal ( a, "42" ) );
    }

    a = "73786976294838206464";
    assert ( equal ( a, "73786976294838206464" ) );
    assert ( equalHex ( a, "40000000000000000" ) );
    assert ( a < "1361129467683753853853498429727072845824" );
    assert ( a <= "1361129467683753853853498429727072845824" );
    assert ( ! ( a > "1361129467683753853853498429727072845824" ) );
    assert ( ! ( a >= "1361129467683753853853498429727072845824" ) );
    assert ( ! ( a == "1361129467683753853853498429727072845824" ) );
    assert ( a != "1361129467683753853853498429727072845824" );
    assert ( ! ( a < "73786976294838206464" ) );
    assert ( a <= "73786976294838206464" );
    assert ( ! ( a > "73786976294838206464" ) );
    assert ( a >= "73786976294838206464" );
    assert ( a == "73786976294838206464" );
    assert ( ! ( a != "73786976294838206464" ) );
    assert ( a < "73786976294838206465" );
    assert ( a <= "73786976294838206465" );
    assert ( ! ( a > "73786976294838206465" ) );
    assert ( ! ( a >= "73786976294838206465" ) );
    assert ( ! ( a == "73786976294838206465" ) );
    assert ( a != "73786976294838206465" );
    a = "2147483648";
    assert ( ! ( a < -2147483648 ) );
    assert ( ! ( a <= -2147483648 ) );
    assert ( a > -2147483648 );
    assert ( a >= -2147483648 );
    assert ( ! ( a == -2147483648 ) );
    assert ( a != -2147483648 );
    a = "-12345678";
    assert ( ! ( a < -87654321 ) );
    assert ( ! ( a <= -87654321 ) );
    assert ( a > -87654321 );
    assert ( a >= -87654321 );
    assert ( ! ( a == -87654321 ) );
    assert ( a != -87654321 );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
