#include <iostream>
#include <cmath>
#include <stdexcept>

#define MAX_ITER 100000000

int8_t isPrime(unsigned long n);
unsigned long leastPrime_gt(unsigned long n);
unsigned long nthPrimeBasic(unsigned int n);
const char *ordinalSuffix(unsigned int n);

int main()
{
    int possiblyPrime = 65;
    int possiblyComposite = 541;
    std::cout << possiblyPrime << " is a " << (isPrime(possiblyPrime) ? "prime" : "composite") << " number." << std::endl;
    std::cout << possiblyComposite << " is a " << (isPrime(possiblyComposite) ? "prime" : "composite") << " number." << std::endl;

    int n = 120;
    std::cout << "The " << n << ordinalSuffix(n) << " prime is " << nthPrimeBasic(n) << "." << std::endl;

    int m = 5000;
    std::cout << "The smallest prime greater than " << m << " is " << leastPrime_gt(m) << "." << std::endl;
}

int8_t isPrime(unsigned long n)
{
    if (n <= 1)
        return 0;

    if (n != 2 && n % 2 == 0)
        return 0;

    int max = sqrt(n);
    for (int i = 3; i <= max; i += 2)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

unsigned long leastPrime_gt(unsigned long n)
{
    for (unsigned int x = n + 1; x < n + MAX_ITER; x++)
    {
        if (isPrime(x))
        {
            return x;
        }
    }

    throw(std::runtime_error("Too many iterations, process aborted."));
}

unsigned long nthPrimeBasic(unsigned int n)
{
    int i = 0;
    unsigned long ithPrime = 1;

    for (unsigned long x = 1; x < MAX_ITER; x++)
    {
        if (isPrime(x))
        {
            i++;
            ithPrime = x;

            if (i == n)
            {
                return ithPrime;
            }
        }
    }

    throw(std::runtime_error("Too many iterations, process aborted."));
}

const char *ordinalSuffix(unsigned int n)
{
    static const char suffixes[][3] = {"th", "st", "nd", "rd"};
    auto ord = n % 100;
    if (ord / 10 == 1)
    {
        ord = 0;
    }
    ord = ord % 10;
    if (ord > 3)
    {
        ord = 0;
    }
    return suffixes[ord];
}