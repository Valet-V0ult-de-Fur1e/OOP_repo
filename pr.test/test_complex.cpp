#include "complex/complex.hpp"

void testParse(const std::string &str) {
    std::istringstream istrm(str);
    Complex z;
    istrm >> z;
    if (istrm.good()) {
        std::cout << "Read success: " << str << " -> " << z << std::endl;
    }
    else {
        std::cout << "Read error : " << str << " -> " << z << std::endl;
    }
}

void testBaseArimetic(const Complex &lhs, const Complex &rhs, const char &operation_type){
    std::cout<<lhs<<" "<<operation_type<<" "<<rhs<<" = ";
    switch (operation_type) {
        case '+':
            std::cout<<lhs + rhs;
            break;
        case '-':
            std::cout<<lhs - rhs;
            break;
        case '*':
            std::cout<<lhs * rhs;
            break;
        case '/':
            try {
                std::cout<<lhs / rhs;
            }
            catch(const std::exception& e) {
                std::cout<<"error ";
                std::cerr << e.what();
            }
            break;
    }
    std::cout<<std::endl;
}

int main(){
    Complex a(13., 4.);
    Complex b(2.3, 4.7);
    Complex c(6.1, 3.9);
    Complex d(8.2, 0.9);
    Complex e(12.3, 2.3);
    Complex f(0);
    Complex g(6.1, -3.9);
    double first_number = 2;
    double second_number = 0.5;
    double third_number = 3.5;
    double fourth_number = 5;
    std::cout<<"Тестирование конвертации из строки в тип и вывода в консоль:"<<std::endl;
    testParse("{13, 6}");
    testParse("{13 , 6}");
    testParse("{13,6}");
    testParse("{13 ,6}");
    testParse("{13, 6");
    testParse("13, 6}");
    std::cout<<"Тестирование суммы"<<std::endl;
    testBaseArimetic(a, b, '+');
    std::cout<<"Тестирование вычитания"<<std::endl;
    testBaseArimetic(c, d, '-');
    std::cout<<"Тестирование умножения"<<std::endl;
    testBaseArimetic(a, b, '*');
    testBaseArimetic(c, g, '*');
    std::cout<<"Тестирование деления"<<std::endl;
    testBaseArimetic(e, d, '/');
    testBaseArimetic(e, f, '/');
}