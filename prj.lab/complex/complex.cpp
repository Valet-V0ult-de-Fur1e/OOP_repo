#include <complex/complex.hpp>

Complex Complex::operator-() const noexcept { return Complex(-re, -im); }

bool Complex::operator==(const Complex& rhs) const noexcept {
	return re == rhs.re && im == rhs.im; 
}
bool Complex::operator!=(const Complex& rhs) const noexcept { 
	return !(*this == rhs); 
}

Complex& Complex::operator+=(const Complex& rhs) noexcept { 
	re += rhs.re;
	im += rhs.im;
	return *this; 
}
Complex& Complex::operator+=(const double rhs) noexcept { return operator+=(Complex(rhs)); }

Complex& Complex::operator-=(const Complex& rhs) noexcept { 
	re -= rhs.re;
	im -= rhs.im;
	return *this; 
}
Complex& Complex::operator-=(const double rhs) noexcept { return operator-=(Complex(rhs)); }

Complex& Complex::operator*=(const Complex& rhs) noexcept { 
	if (re == rhs.re && im == -1 * rhs.im) {
		re = pow(re, 2) + pow(im, 2);
		im = 0.0;
	}
	else {
		re = re * rhs.re - im * rhs.im;
		im = im * rhs.re + re * rhs.im;
	}
	return *this; 
}
Complex& Complex::operator*=(const double rhs) noexcept { return operator*=(Complex(rhs)); }

Complex& Complex::operator/=(const Complex& rhs) { 
	if (rhs.re == 0 && rhs.im == 0) {
		throw std::runtime_error("Division by zero!");
	}
	re = (re * rhs.re + im * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
	im = (re * rhs.im - im * rhs.re) / (rhs.re * rhs.re + rhs.im * rhs.im);
	return *this; 
}
Complex& Complex::operator/=(const double rhs) { return operator/=(Complex(rhs)); }

std::ostream& Complex::WriteTo(std::ostream& ostrm) const noexcept { 
	ostrm << leftBrace << re << separator << im << rightBrace;
	return ostrm; 
}
std::istream& Complex::ReadFrom(std::istream& istrm) noexcept { 
	char leftBrace(0);
	double real(0.0);
	char comma(0);
	double imaganary(0.0);
	char rightBrace(0);
	istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
	if (istrm.good()) {
		if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) && (Complex::rightBrace == rightBrace)) {
			re = real;
			im = imaganary;
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm; 
}

Complex pow(const Complex& lhs, const double rhs) {
	Complex product(lhs);
	double hypotenuse = pow((pow(lhs.re, 2) + pow(lhs.im, 2)), 0.5);
	double corner = abs(acos(lhs.im / pow(hypotenuse, 0.5)));
	hypotenuse = pow(hypotenuse, rhs);
	product.re = hypotenuse * cos(rhs * corner);
	product.im = hypotenuse * sin(rhs * corner);
	return product;
}

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }
Complex operator+(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) += rhs; }
Complex operator+(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }
Complex operator-(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) -= rhs; }
Complex operator-(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }
Complex operator*(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) *= rhs; }
Complex operator*(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }

Complex operator/(const Complex& lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }
Complex operator/(const Complex& lhs, const double rhs) { return Complex(lhs) /= rhs; }
Complex operator/(const double lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }