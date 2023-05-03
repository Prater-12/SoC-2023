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

    void add(Complex z)
    {
        x += z.x;
        y += z.y;
    }

    void multiply(Complex z)
    {
        int real = x * z.x - y * z.y;
        int imaginary = x * z.y + y * z.x;

        x = real;
        y = imaginary;
    }

    void scale(int scalar)
    {
        x *= scalar;
        y *= scalar;
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
}