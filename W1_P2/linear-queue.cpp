#include <iostream>
#include <cstdlib>

#define MAX_SIZE_DEFAULT 256

// THIS STRUCTURE IS JUST A GUIDELINE
// FEEL FREE TO CHANGE WHATEVER YOU WANT

class LinearQueue
{
private:
    int *q;
    int start;
    int end;
    int size;
    int MAX_SIZE;

public:
    // Default Constructor
    LinearQueue()
    {
        try
        {
            q = new int[MAX_SIZE_DEFAULT];
        }
        catch (std::bad_alloc)
        {
            exit(1);
        }

        size = 0;
        start = -1;
        end = -1;

        // setting MAX_SIZE according to the parameter
        this->MAX_SIZE = MAX_SIZE_DEFAULT;
    }

    // Additional Constructor
    LinearQueue(int MAX_SIZE)
    {
        try
        {
            q = new int[MAX_SIZE];
        }
        catch (std::bad_alloc)
        {
            exit(1);
        }

        size = 0;
        start = -1;
        end = -1;

        // setting MAX_SIZE according to the parameter
        this->MAX_SIZE = MAX_SIZE;
    }

    bool insert(int elem)
    {

        if (size >= MAX_SIZE)
            return false;

        if (end == MAX_SIZE - 1)
            clean();

        q[++end] = elem;

        if (!size)
            start = 0;

        size++;
        return true;
    }

    int remove()
    {
        if (!size)
            return -1;

        int startVal = q[start++];

        size--;

        if (!size)
        {
            start = -1;
            end = -1;
        }

        return startVal;
    }

    int get_size()
    {
        return size;
    }

    int get_max_size()
    {
        return MAX_SIZE;
    }

    void printState()
    {
        if (size)
        {
            for (int i = start; i <= end; i++)
            {
                std::cout << q[i] << " ";
            }
        }
        std::cout << std::endl;

        std::cout << "Start: " << start << " End: " << end << " Size: " << size << std::endl;
    }

private:
    void clean()
    {
        int *temp = q;

        try
        {
            q = new int[MAX_SIZE];
        }
        catch (std::bad_alloc)
        {
            exit(1);
        }

        for (int i = 0; i < size; i++)
        {
            q[i] = temp[start + i];
        }

        start = size ? 0 : -1;
        end = size - 1;

        delete[] temp;
    }
};

int main()
{
    LinearQueue queue(32);
    srand(0);

    int n;
    for (int i = 0; i < 101; i++)
    {
        std::cout << i + 1 << ". ";

        if (rand() % 2)
        {
            n = rand() % 20 + 1;

            std::cout << (queue.insert(n) ? "Inserted " : "Failed to insert ") << n << std::endl;

            queue.printState();
        }
        else
        {
            n = queue.remove();
            if (n == -1)
            {
                std::cout << "Removed nothing" << std::endl;
            }
            else
            {
                std::cout << "Removed " << n << std::endl;
            }
            queue.printState();
        }
        std::cout << std::endl;
    }
}