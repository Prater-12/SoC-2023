class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> leftBrackets;

        for (char b : s)
        {
            if (b == '{' || b == '(' || b == '[')
            {
                leftBrackets.push(b);
            }
            else
            {
                if (leftBrackets.empty())
                    return false;
                if (b != getRightBracket(leftBrackets.top()))
                    return false;
                leftBrackets.pop();
            }
        }
        return leftBrackets.empty();
    }

private:
    char getRightBracket(char b)
    {
        switch (b)
        {
        case '{':
            return '}';
        case '[':
            return ']';
        case '(':
            return ')';
        default:
            throw("Error");
        }
    }
};