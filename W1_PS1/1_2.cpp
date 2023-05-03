#include <iostream>
#include <string>
#include <stdexcept>

std::string changeBase(std::string n, int b1, int b2);

int main()
{
    std::string number = "2345Ac";

    std::cout << changeBase(number, 16, 10) << std::endl;
}

std::string changeBase(std::string n, int b1, int b2)
{
    if (b1 == b2)
        return n;

    if (b1 > 36 || b2 > 36)
        throw(std::invalid_argument("Bases cannot be greater than 36"));

    int n_int = 0;

    int place_val = 1;
    for (std::string::reverse_iterator i = n.rbegin(); i != n.rend(); i++)
    {
        int face_val = 0;

        if (*i >= '0' && *i <= '9')
        {
            face_val = *i - '0';
        }
        else if (*i >= 'A' && *i <= 'Z')
        {
            face_val = *i - 'A' + 10;
        }
        else if (*i >= 'a' && *i <= 'z')
        {
            face_val = *i - 'a' + 10;
        }
        else
        {
            throw(std::invalid_argument("Number contains non alpha-numericals"));
        }

        n_int += place_val * face_val;
        place_val *= b1;
    }

    std::string new_n;

    while (n_int)
    {
        int digit = n_int % b2;
        n_int /= b2;

        char digit_char;

        if (digit <= 9)
        {
            digit_char = '0' + digit;
        }
        else
        {
            digit_char = 'A' + digit_char - 10;
        }

        new_n = digit_char + new_n;
    }

    return new_n;
}
