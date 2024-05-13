#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "rational\rational.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>

TEST_CASE("initializator test") {
	Rational a;
	CHECK(a.num() == 0);
	CHECK(a.den() == 1);

	a = Rational(2);
	CHECK(a.num() == 2);
	CHECK(a.den() == 1);

	a = Rational(1, 2);
	CHECK(a.num() == 1);
	CHECK(a.den() == 2);

	a = Rational(2, 4);
	CHECK(a.num() == 1);
	CHECK(a.den() == 2);

	a = Rational(4, 2);
	CHECK(a.num() == 2);
	CHECK(a.den() == 1);

	a = Rational(4, -2);
	CHECK(a.num() == -2);
	CHECK(a.den() == 1);

	CHECK_THROWS_AS(Rational(1, 0), std::invalid_argument);
}

TEST_CASE("is Equals test") {
	Rational a = Rational();
	Rational b = Rational();
	CHECK(a == b);

	a = Rational(1, 2);
	b = Rational(1, 2);
	CHECK(a == b);

	a = Rational(1, 2);
	b = Rational(2, 4);
	CHECK(a == b);

	a = Rational(1, 2);
	b = Rational(1);
	CHECK_FALSE(a == b);
}

TEST_CASE("not Equals test") {
	Rational a = Rational(1);
	Rational b = Rational();
	CHECK(a != b);

	a = Rational(1, 2);
	b = Rational(2, 3);
	CHECK(a != b);

	a = Rational(1, 2);
	b = Rational(4, 2);
	CHECK(a != b);

	a = Rational(1);
	b = Rational(1);
	CHECK_FALSE(a != b);
}

TEST_CASE("comparison operations test") {
	Rational a = Rational(1);
	Rational b = Rational(0);
	CHECK(a > b);
	CHECK(a >= b);
	CHECK_FALSE(a < b);
	CHECK_FALSE(a <= b);

	a = Rational(1, 2);
	b = Rational(1, 3);
	CHECK(a > b);
	CHECK(a >= b);
	CHECK_FALSE(a < b);
	CHECK_FALSE(a <= b);
}

TEST_CASE("Sum test") {
	Rational a = Rational(1);
	Rational b = Rational(0);
	Rational c = a + b;
	CHECK(c == Rational(1));

	a = Rational(1, 2);
	b = Rational(1, 3);
	c = a + b;
	CHECK(c == Rational(5, 6));

	a = Rational(1);
	b = Rational(0);
	a += b;
	CHECK(a == Rational(1));

	a = Rational(1, 2);
	b = Rational(1, 3);
	a += b;
	CHECK(a == Rational(5, 6));
}

TEST_CASE("Sub test") {
	Rational a = Rational(1);
	Rational b = Rational(0);
	Rational c = a - b;
	CHECK(c == Rational(1));

	a = Rational(1, 2);
	b = Rational(1, 3);
	c = a - b;
	CHECK(c == Rational(1, 6));

	a = Rational(1);
	b = Rational(0);
	a -= b;
	CHECK(a == Rational(1));

	a = Rational(1, 2);
	b = Rational(1, 3);
	a -= b;
	CHECK(a == Rational(1, 6));
}

TEST_CASE("Mul test") {
	Rational a = Rational(1);
	Rational b = Rational(0);
	Rational c = a * b;
	CHECK(c == Rational());

	a = Rational(1, 2);
	b = Rational(1, 3);
	c = a * b;
	CHECK(c == Rational(1, 6));

	a = Rational(1);
	b = Rational(0);
	a *= b;
	CHECK(a == Rational());

	a = Rational(1, 2);
	b = Rational(1, 3);
	a *= b;
	CHECK(a == Rational(1, 6));
}

TEST_CASE("Div test") {
	Rational a = Rational(1);
	Rational b = Rational(2);
	Rational c = a / b;
	CHECK(c == Rational(1, 2));

	a = Rational(1, 2);
	b = Rational(1, 3);
	c = a / b;
	CHECK(c == Rational(3, 2));

	a = Rational(1);
	b = Rational(2);
	a /= b;
	CHECK(a == Rational(1, 2));

	a = Rational(1, 2);
	b = Rational(1, 3);
	a /= b;
	CHECK(a == Rational(3, 2));

	a = Rational(1, 1);
	b = Rational(0, 1);
	CHECK_THROWS_AS(a / b, std::runtime_error);
}

TEST_CASE("Input test") {
	std::istringstream strm("1/2 2/3 3/4 12+3");
	Rational a = Rational();
	strm >> a;
	CHECK(a == Rational(1, 2));

	strm >> a;
	CHECK(a == Rational(2, 3));

	strm >> a;
	CHECK(a == Rational(3, 4));

	strm >> a;
	CHECK_FALSE(strm.good());
}


TEST_CASE("Nwgative numbers test") {
	Rational a(1, -3);
	CHECK(a == Rational(-1, 3));
	Rational b(1, 3);
	b += a;
	CHECK(b == Rational());
	b = Rational(1);
	b *= a;
	CHECK(b == Rational(-1, 3));
	b /= a;
	CHECK(b == Rational(1));
}