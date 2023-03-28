#pragma once
#include <iostream>


class BigInt {
    size_t _len;
    char * _digit;
    
public:
    // Конструкторы 
    BigInt();
    BigInt(const std::string &str);
    BigInt(int64_t value);
    BigInt(const BigInt &other);
    BigInt(BigInt &&other);
    // Перемещение , копирование 
    BigInt& operator=(const BigInt &other);
    BigInt& operator=(BigInt &&other);
    // Арифметика
    BigInt operator-() const;
    bool operator>(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    
    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;

    ~BigInt();
    
    friend std::ostream& operator<<(std::ostream &out, const BigInt &num);
};

