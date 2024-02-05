#include "rational.hpp"
#include <iostream>
#include <cmath>
#include <exception>

Rational::Rational(int64_t number) noexcept {
    numerator = number;
}

Rational::Rational(int64_t numerator, int64_t denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("null in denominator");
    }
    else {
        this->denominator = denominator;
        this->numerator = numerator;
        Formatting();
        Reduce();
    }
}

bool Rational::operator==(const Rational& rhs) const noexcept {
    return numerator * rhs.denominator == rhs.numerator * denominator;
}

bool Rational::operator!=(const Rational& rhs) const noexcept {
    return !(rhs == (*this));
}

bool Rational::operator<(const Rational& rhs) const noexcept {
    return ((*this) - rhs).numerator < 0;
}

bool Rational::operator<=(const Rational& rhs) const noexcept {
    return !((*this) > rhs);
}

bool Rational::operator>(const Rational& rhs) const noexcept {
    return ((*this) - rhs).numerator > 0;
}

bool Rational::operator>=(const Rational& rhs) const noexcept {
    return !((*this) < rhs);
}

Rational Rational::operator-() const noexcept {
    return Rational() - (*this);
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
    if (rhs.denominator != denominator) {
        int64_t a = rhs.numerator * denominator;
        denominator *= rhs.denominator;
        numerator *= rhs.denominator;
        numerator += a;
    }
    else {
        numerator += rhs.numerator;
    }
    Reduce();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
    if (rhs.denominator != denominator) {
        int64_t a = rhs.numerator * denominator;
        denominator *= rhs.denominator;
        numerator *= rhs.denominator;
        numerator -= a;
    }
    else {
        numerator -= rhs.numerator;
    }
    Reduce();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    denominator *= rhs.denominator;
    numerator *= rhs.numerator;
    Reduce();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    denominator *= rhs.numerator;
    numerator *= rhs.denominator;
    if (denominator == 0) {
        throw std::runtime_error("Division by zero");
    }
    Reduce();
    return *this;
}

Rational& Rational::operator+=(const int64_t rhs) noexcept {
    (*this) += Rational(rhs);
    return *this;
}

Rational& Rational::operator-=(const int64_t rhs) noexcept {
    (*this) -= Rational(rhs);
    return *this;
}

Rational& Rational::operator*=(const int64_t rhs) noexcept {
    (*this) *= Rational(rhs);
    return *this;
}

Rational& Rational::operator/=(const int64_t rhs) {
    (*this) /= Rational(rhs);
    return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) noexcept {
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) noexcept {
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) noexcept {
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result /= rhs;
    return result;
}

Rational operator+(const Rational& lhs, const int64_t rhs) noexcept {
    return lhs + Rational(rhs);
}

Rational operator-(const Rational& lhs, const int64_t rhs) noexcept {
    return lhs - Rational(rhs);
}

Rational operator*(const Rational& lhs, const int64_t rhs) noexcept {
    return lhs * Rational(rhs);
}

Rational operator/(const Rational& lhs, const int64_t rhs) {
    return lhs / Rational(rhs);
}

Rational operator+(const int64_t lhs, const Rational& rhs) noexcept {
    return Rational(lhs) + rhs;
}

Rational operator-(const int64_t lhs, const Rational& rhs) noexcept {
    return Rational(lhs) - rhs;
}

Rational operator*(const int64_t lhs, const Rational& rhs) noexcept {
    return Rational(lhs) * rhs;
}

Rational operator/(const int64_t lhs, const Rational& rhs) {
    return Rational(lhs) / rhs;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
    return rhs.WriteTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
    return rhs.ReadFrom(istrm);
}

void Rational::Formatting() {
    if (!(numerator < 0 && denominator > 0)) {
        if (numerator < 0 && denominator < 0) {
                numerator *= -1;
                denominator *= -1;
            }
        else if (numerator > 0 && denominator < 0) {
            denominator *= -1;
            numerator *= -1;
        }
    }
    
}

void Rational::Reduce() {
    int64_t lsh = std::abs(numerator);
    int64_t rsh = denominator;
    int64_t gsd = 1;
    while (lsh > 0 && rsh > 0) {
        if (std::max(lsh, rsh) % std::min(lsh, rsh) == 0) {
            gsd = std::min(lsh, rsh);
            break;
        }
        if (lsh > rsh) {
            lsh %= rsh;
        }
        else {
            rsh %= lsh;
        }
    }
    numerator /= gsd;
    denominator /= gsd;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept {
    ostrm << numerator << separator << denominator;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm)noexcept {
    int64_t numerator = 0;
    int64_t denominator = 0;
    char separator = 0;
    istrm >> numerator >> separator >> denominator;
    if (istrm.good() && separator == this->separator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }
    else {
        istrm.setstate(std::ios_base::failbit);
    }
    return istrm;
}

int64_t Rational::num() const noexcept {
    return numerator;
}

int64_t Rational::den() const noexcept {
    return denominator;
}
