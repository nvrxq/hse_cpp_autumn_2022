#include "BigInt.hpp"


BigInt::BigInt(): _len(1), _digit(new char[_len+1]) {
    _digit[0] = '0';
    _digit[1] = '\0';
}

BigInt::BigInt(const std::string &str) {
    if(str.size() == 0) {
        _len = 1;
        _digit = new char[_len+1];
        _digit[0] = '0';
        _digit[1] = '\0';
    }
    else {
        bool minus = str[0] == '-';
        bool plus = str[0] == '+';
        size_t j = minus + plus;
        size_t str_size = str.size();
        
        for(; j < str_size - 1 and str[j] == '0'; j++);
        _len = str.size() - j + minus;
        _digit = new char[_len+1];
        char t;
        if(minus) _digit[0] = str[0];
        for(size_t i=minus; i<_len; i++) {
            t = str[j + i - minus];
            if(!isdigit(t)) throw std::invalid_argument("Arg must be digit!");
            else _digit[i] = t;
        };
    }
    _digit[_len] = '\0';
}

BigInt::BigInt(int64_t value) {
    BigInt to_copy_from(std::to_string(value));
    _digit = to_copy_from._digit;
    _len = to_copy_from._len;
    to_copy_from._digit = nullptr;
    to_copy_from._len = 0;
}

BigInt::BigInt(const BigInt &other) {
    _len = other._len;
    _digit = new char[_len+1];
    for(size_t i=0; i<_len; i++) _digit[i] = other._digit[i];
    _digit[_len] = '\0';
}

BigInt::BigInt(BigInt &&other) {
    _digit = other._digit;
    _len = other._len;
    other._digit = nullptr;
    other._len = 0;
}

BigInt& BigInt::operator=(const BigInt &other) {
    if(this == &other) return *this;
    _len = other._len;
    char * tmp = new char[_len+1];
    delete[] _digit;
    _digit = tmp;
    tmp = nullptr;
    for(size_t i=0; i<_len; i++) _digit[i] = other._digit[i];
    _digit[_len] = '\0';
    return *this;
}

BigInt& BigInt::operator=(BigInt &&other) {
    if(this == &other) {
        return *this;
    }
    delete[] _digit;
    _digit = other._digit;
    _len = other._len;
    other._digit = nullptr;
    other._len = 0;
    return *this;
}

BigInt BigInt::operator-() const {
    if(_digit[0] == '0') return *this;
    bool minus = _digit[0] == '-';
    char * tmp = new char[_len + 1 - 2 * minus + 1];
    if(!minus) tmp[0] = '-';
    for(size_t i = !minus; i<_len + 1 - 2 * minus; i++) tmp[i] = _digit[i - 1 + 2 * minus];
    tmp[_len + 1 - 2 * minus] = '\0';
    BigInt val(tmp);
    delete[] tmp;
    return val;
}

bool BigInt::operator>(const BigInt &other) const {
    if(_digit[0] == '-')
        if(other._digit[0] == '-')
            if(_len != other._len) return _len < other._len;
            else {
                for(size_t i=1; i<_len; i++) {
                    if(_digit[i] < other._digit[i]) return true;
                    if(_digit[i] > other._digit[i]) return false;
                }
                return false;
            }
        else return false;  
    else 
        if(other._digit[0] != '-')
            if(_len != other._len) return _len > other._len;
            else {
                for(size_t i=0; i<_len; i++) {
                    if(_digit[i] < other._digit[i]) return false;
                    if(_digit[i] > other._digit[i]) return true;
                }
                return false;
            }
        else return true;       
}

bool BigInt::operator==(const BigInt &other) const {
    if(_digit[0] == '-' and other._digit[0] != '-' or _digit[0] != '-' and other._digit[0] == '-') return false;
    if(_len != other._len) return false;
    for(size_t i = 1; i<_len; i++) {
        if(_digit[i] != other._digit[i]) return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt &other) const {
    return not(*this == other);
}

bool BigInt::operator<(const BigInt &other) const {
    return not(*this > other) and not(*this == other);
}

bool BigInt::operator>=(const BigInt &other) const {
    return *this > other or *this == other;
}

bool BigInt::operator<=(const BigInt &other) const {
    return *this < other or *this == other;
}

BigInt add(const char * str1, size_t _len1, const char * str2, size_t _len2) {
    char * tmp = new char[_len1 + 2];
    int overflow = 0;
    size_t i = 0;
    for(; i<_len2; i++) {
        overflow = (str1[_len1 - 1 - i] - '0') + (str2[_len2 - 1 - i] - '0') + overflow;
        tmp[_len1 - i] = char(overflow % 10 + '0');
        overflow = overflow / 10;
    }
    for(; i<_len1; i++) {
        overflow = (str1[_len1 - 1 - i] - '0') + overflow;
        tmp[_len1 - i] = char(overflow % 10 + '0');
        overflow = overflow / 10;
    }
    tmp[0] = char(overflow + '0');
    tmp[_len1 + 1] = '\0';
    BigInt val(tmp);
    delete[] tmp;
    return val;
}

BigInt substract(const char * str1, size_t _len1, const char * str2, size_t _len2) {
    char * tmp = new char[_len1+2];
    bool borrow = false;
    size_t i = 0;
    for(; i<_len2; i++) {
        if((str1[_len1 - 1 - i] - '0') - borrow < (str2[_len2 - 1 - i] - '0')) {
            tmp[_len1 - 1 - i] = char(str1[_len1 - 1 - i] + 10 - borrow - str2[_len2 - 1 - i] + '0');
            borrow = 1;
        }
        else {
            tmp[_len1 - 1 - i] = char(str1[_len1 - 1 - i] - borrow - str2[_len2 - 1 - i] + '0');
            borrow = 0;
        }
    }
    for(; i<_len1; i++) {
        if(borrow and str1[_len1 - 1 - i] == '0') {
            tmp[_len1 - 1 - i] = '9';
            borrow = 1;
        }
        else {
            tmp[_len1 - 1 - i] = char(str1[_len1 - 1 - i] - borrow);
            borrow = 0;
        }
    }
    tmp[_len1+1] = '\0';
    BigInt val(tmp);
    delete[] tmp;
    return val;
}

BigInt BigInt::operator+(const BigInt &other) const {
    if(_digit[0] == '-')
        if(other._digit[0] == '-')
            if(-(*this) >= -other) return -add(_digit + 1, _len - 1, other._digit + 1, other._len - 1);
            else return -add(other._digit + 1, other._len - 1, _digit + 1, _len - 1);
        else
            if(-(*this) >= other) return -substract(_digit + 1, _len - 1, other._digit, other._len);
            else return substract(other._digit, other._len, _digit + 1, _len - 1);
    else
        if(other._digit[0] == '-')
            if(*this >= -other) return substract(_digit, _len, other._digit + 1, other._len - 1);
            else return -substract(other._digit + 1, other._len - 1, _digit, _len);
        else
            if(*this >= other) return add(_digit, _len, other._digit, other._len);
            else return add(other._digit, other._len, _digit, _len);
}

BigInt BigInt::operator-(const BigInt &other) const {
    return *this + (-other);
}

BigInt BigInt::operator*(const BigInt &other) const {
    bool minus1 = _digit[0] == '-';
    bool minus2 = other._digit[0] == '-';
    int overflow = 0;
    size_t base_length = _len - minus1 + 1;
    char ** tmp = new char*[other._len - minus2];
    for(size_t i=0; i<other._len - minus2; i++) tmp[i] = new char[base_length + i + 1];
    for(size_t i=0; i<other._len - minus2; i++) {
        for(size_t j = 0; j<i; j++) tmp[i][base_length + i - 1 - j] = '0';
        overflow = 0;
        for(size_t j=0; j<_len - minus1; j++) {
            overflow = (_digit[_len - 1 - j] - '0') * (other._digit[other._len - 1 - i] - '0') + overflow;
            tmp[i][base_length - 1 - j] = char(overflow % 10 + '0');
            overflow = overflow / 10;
        }
        tmp[i][0] = char(overflow + '0');
        tmp[i][base_length + i] = '\0';
    }
    BigInt mul(0);
    for(size_t i=0; i<other._len - minus2; i++) {
        mul = mul + BigInt(tmp[i]);
        delete[] tmp[i];
    }
    delete[] tmp;
    if(minus1 xor minus2) return -mul;
    else return mul;
}

BigInt::~BigInt() {
    delete[] _digit;
}

std::ostream& operator<<(std::ostream &out, const BigInt &num) {
    for(size_t i=0; i<num._len; i++) out<<(num._digit[i]);
    return out;
}