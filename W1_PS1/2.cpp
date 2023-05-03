#include <iostream>

class Complex
{
private:
    int x;
    int y;

public:
    Complex(int x, int y) : x(x), y(y){};
    Complex()
    {
        x = 0;
        y = 0;
    }

    Complex &add(Complex z)
    {
        x += z.x;
        y += z.y;

        return *this;
    }

    Complex &multiply(Complex z)
    {
        int real = x * z.x - y * z.y;
        int imaginary = x * z.y + y * z.x;

        x = real;
        y = imaginary;

        return *this;
    }

    Complex &scale(int scalar)
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    void print()
    {
        std::cout << x << "+i" << y << std::endl;
    }

    static Complex add(Complex z1, Complex z2)
    {
        return Complex(z1.x + z2.x, z1.y + z2.y);
    }

    static Complex multiply(Complex z1, Complex z2)
    {
        return Complex(z1.x * z2.x - z1.y * z2.y, z1.x * z2.y + z1.y * z2.x);
    }

    static Complex scale(int scalar, Complex z)
    {
        return Complex(scalar * z.x, scalar * z.y);
    }
};

int main()
{
    Complex z1(3, 4);
    Complex z2(1, 1);

    Complex::add(z1, z2).print();
    Complex::multiply(z1, z2).print();
    z2.scale(2).print();
}