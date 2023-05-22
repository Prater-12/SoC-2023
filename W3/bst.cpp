#include <iostream>
#include <stack>
#include <vector>

template <typename T>
struct Node
{
    T data;
    Node<T> *left;
    Node<T> *right;

    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree
{
    Node<T> *root;

public:
    BinarySearchTree() : root(nullptr){};

    void add(T data)
    {

        Node<T> *parent = nullptr;
        Node<T> *child = root;

        while (child != nullptr)
        {
            parent = child;

            if (parent->data > data)
            {
                child = parent->left;
            }
            else
            {
                child = parent->right;
            }
        }

        child = new Node<T>(data);

        if (parent == nullptr)
        {
            root = child;
        }
        else
        {
            if (parent->data > data)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
    }

    void find(T data)
    {
        return;
    };

    void inorder()
    {
        Node<T> *temp = root;
        std::stack<Node<T> *> nodeStack;

        while (temp != nullptr || !nodeStack.empty())
        {
            if (temp != nullptr)
            {
                nodeStack.push(temp);
                temp = temp->left;
            }
            else
            {
                temp = nodeStack.top();
                nodeStack.pop();
                std::cout << temp->data << " ";
                temp = temp->right;
            }
        }

        std::cout << '\n';
    };

    static std::vector<T> sortVector(std::vector<T> vec)
    {
        BinarySearchTree<T> bst;

        for (auto i = vec.begin(); i != vec.end(); ++i)
            bst.add(*i);

        std::vector<T> sortedVec;

        Node<T> *temp = bst.root;
        std::stack<Node<T> *> nodeStack;

        while (temp != nullptr || !nodeStack.empty())
        {
            if (temp != nullptr)
            {
                nodeStack.push(temp);
                temp = temp->left;
            }
            else
            {
                temp = nodeStack.top();
                nodeStack.pop();
                sortedVec.push_back(temp->data);
                temp = temp->right;
            }
        }

        return sortedVec;
    };
};

int main()
{
    BinarySearchTree<int> bst;

    for (int i = 0; i < 10; i++)
    {
        bst.add(10 - i);

        if (i)
            bst.add(10 + i);

        bst.inorder();
    }

    std::vector<int> vec{7, 6, 5, 4, 3, 2, 1};

    vec = BinarySearchTree<int>::sortVector(vec);

    for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << *i << ' ';
}