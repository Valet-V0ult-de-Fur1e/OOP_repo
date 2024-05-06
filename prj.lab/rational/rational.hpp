#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstddef>
#include <iostream>

class Rational {
public:
	[[nodiscard]] Rational() = default;
	[[nodiscard]] Rational(const Rational&) = default;
	Rational(Rational&& rational) noexcept = default;
	[[nodiscard]] explicit Rational(const std::int64_t num) noexcept : numerator(num) {}
	[[nodiscard]] Rational(const std::int64_t num, const std::int64_t den);
	~Rational() = default;
	[[nodiscard]] Rational& operator=(const Rational&) = default;
	Rational& operator=(Rational&& rhs) noexcept = default;

	[[nodiscard]] std::int64_t num() const noexcept;
	[[nodiscard]] std::int64_t den() const noexcept;

	[[nodiscard]] bool operator==(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator!=(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator<(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator<=(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator>(const Rational& rhs) const noexcept;
	[[nodiscard]] bool operator>=(const Rational& rhs) const noexcept;

	[[nodiscard]] Rational operator-() const noexcept;

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

[[nodiscard]] Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator/(const Rational& lhs, const Rational& rhs);

[[nodiscard]] Rational operator+(const Rational& lhs, const int64_t rhs) noexcept;
[[nodiscard]] Rational operator-(const Rational& lhs, const int64_t rhs) noexcept;
[[nodiscard]] Rational operator*(const Rational& lhs, const int64_t rhs) noexcept;
[[nodiscard]] Rational operator/(const Rational& lhs, const int64_t rhs);

[[nodiscard]] Rational operator+(const int64_t lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator-(const int64_t lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator*(const int64_t lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator/(const int64_t lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept;

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept;

#endif