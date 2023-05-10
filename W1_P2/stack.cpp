#include <iostream>
#include <cstdlib>

#define MAX_SIZE_DEFAULT 256

// THIS STRUCTURE IS JUST A GUIDELINE
// FEEL FREE TO CHANGE WHATEVER YOU WANT

class Stack
{
private:
    int *s;
    int top;
    int capacity;
    int MAX_SIZE;

public:
    // Default Constructor
    Stack()
    {
        try
        {
            this->s = new int[1];
        }
        catch (std::bad_alloc)
        {
            exit(1);
        }

        this->capacity = 1;
        this->top = -1;

        this->MAX_SIZE = MAX_SIZE_DEFAULT;
    }

    // Additional Constructor
    Stack(int MAX_SIZE)
    {
        try
        {
            this->s = new int[1];
        }
        catch (std::bad_alloc)
        {
            exit(1);
        }

        // Initialize top, size
        this->capacity = 1;
        this->top = -1;

        // setting MAX_SIZE according to the parameter
        this->MAX_SIZE = MAX_SIZE;
    }

    bool push(int elem)
    {
        if (this->get_size() >= this->capacity && !memAllocate(true))
        {
            return false;
        }

        this->s[++this->top] = elem;

        return true;
    }

    int pop()
    {
        if (this->top == -1)
            return -1;

        int topVal = this->s[this->top--];

        if (this->get_size() && this->get_size() * 2 <= this->capacity)
        {
            memAllocate(false);
        }

        return topVal;
    }

    int peek()
    {
        return this->s[this->top];
    }

    int get_size()
    {
        return this->top + 1;
    }

    int get_capacity()
    {
        return this->capacity;
    }

    int get_max_size()
    {
        return this->MAX_SIZE;
    }

    void printState()
    {
        for (int i = 0; i <= this->top; i++)
        {
            std::cout << this->s[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Size: " << this->get_size() << " Capacity: " << this->capacity << std::endl;
    }

private:
    bool memAllocate(bool increase)
    {
        int newSize = 1;

        if (!increase)
        {
            /* if (this->capacity >= this->MAX_SIZE)
            {
                while (newSize <= this->MAX_SIZE)
                {
                    newSize *= 2;
                }
                newSize /= 2;
            }
            else */
            newSize = this->capacity / 2;
        }
        else if (this->capacity < MAX_SIZE)
        {
            newSize = this->capacity * 2;
            if (newSize > this->MAX_SIZE)
                newSize = this->MAX_SIZE;
        }
        else // if (this->capacity >= this->MAX_SIZE)
        {
            return false;
        }

        int *temp;
        try
        {
            temp = new int[newSize];
        }
        catch (std::bad_alloc)
        {
            exit(1);
        }

        for (int i = 0; i < newSize; i++)
        {
            temp[i] = this->s[i];
        }

        delete[] this->s;

        this->s = temp;
        this->capacity = newSize;

        return true;
    }
};

int main() // Test for stack
{
    Stack stack(32);
    srand(0);

    int n;
    for (int i = 0; i < 101; i++)
    {
        std::cout << i + 1 << ". ";

        if (i < 50 ? rand() % 6 : (rand() % 5 == 0))
        {
            n = rand() % 20 + 1;

            std::cout << (stack.push(n) ? "Pushed " : "Failed to push ") << n << std::endl;

            stack.printState();
        }
        else
        {
            n = stack.pop();
            if (n == -1)
            {
                std::cout << "Popped nothing" << std::endl;
            }
            else
            {
                std::cout << "Popped " << n << std::endl;
            }
            stack.printState();
        }
        std::cout << std::endl;
    }
}