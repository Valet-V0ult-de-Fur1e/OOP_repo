#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstddef>
#include <iostream>

class Rational {
public:
	Rational() = default;
	Rational(const Rational&) = default;
	explicit Rational(const std::int64_t num) noexcept;
	Rational(const std::int64_t num, const std::int64_t den);
	~Rational() = default;
	Rational& operator=(const Rational&) = default;

	std::int64_t num() const noexcept;
	std::int64_t den() const noexcept;

	bool operator==(const Rational& rhs) const noexcept;
	bool operator!=(const Rational& rhs) const noexcept;
	bool operator<(const Rational& rhs) const noexcept;
	bool operator<=(const Rational& rhs) const noexcept;
	bool operator>(const Rational& rhs) const noexcept;
	bool operator>=(const Rational& rhs) const noexcept;

	Rational operator-() const noexcept;

	Rational& operator+=(const Rational& rhs) noexcept;
	Rational& operator-=(const Rational& rhs) noexcept;
	Rational& operator*=(const Rational& rhs) noexcept;
	Rational& operator/=(const Rational& rhs);

	Rational& operator+=(const int64_t rhs) noexcept;
	Rational& operator-=(const int64_t rhs) noexcept;
	Rational& operator*=(const int64_t rhs) noexcept;
	Rational& operator/=(const int64_t rhs);

	std::ostream& WriteTo(std::ostream& ostrm) const noexcept;

	std::istream& ReadFrom(std::istream& istrm) noexcept;

private:
	std::int64_t numerator = 0;
	std::int64_t denominator = 1;
	static const char separator = '/';
	void Reduce();
	void Formatting();
};

Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator-(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator*(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator/(const Rational& lhs, const int64_t rhs);

Rational operator+(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator-(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator*(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator/(const int64_t lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept;

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept;

#endif