#include <iostream>
#include <stdexcept>
#include <cstdlib>

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;

    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList
{
    Node<T> *head;
    Node<T> *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr){};

    void printAll()
    {
        Node<T> *i = head;

        while (i != nullptr)
        {
            std::cout << i->data << " ";
            i = i->next;
        }

        std::cout << '\n';
    }

    void prepend(T data)
    {
        Node<T> *newHead = new Node<T>(data);

        if (head == nullptr)
        {
            tail = newHead;
        }
        else
        {
            newHead->next = head;
            head->prev = newHead;
        }

        head = newHead;
    }

    void append(T data)
    {
        Node<T> *newTail = new Node<T>(data);

        if (tail == nullptr)
        {
            head = newTail;
        }
        else
        {
            newTail->prev = head;
            tail->next = newTail;
        }

        tail = newTail;
    }

    int insertAfter(T key, T data)
    {
        Node<T> *newNode = new Node<T>(data);

        Node<T> *prevNode = head;

        while (prevNode != nullptr)
        {
            if (prevNode->data == key)
            {
                newNode->next = prevNode->next;
                prevNode->next = newNode;
                return 1;
            }

            prevNode = prevNode->next;
        }

        return 0;
    }

    T removeHead()
    {
        if (head == nullptr)
            throw std::range_error("List is empty.");

        Node<T> *oldHead = head;
        head = oldHead->next;

        if (head == nullptr)
            tail = nullptr;
        else
            head->prev = nullptr;

        T data = oldHead->data;
        delete oldHead;
        return data;
    }

    T removeTail()
    {
        if (tail == nullptr)
            throw std::range_error("List is empty.");

        Node<T> *oldTail = tail;
        tail = oldTail->prev;

        if (tail == nullptr)
            head = nullptr;
        else
            tail->next = nullptr;

        T data = oldTail->data;
        delete oldTail;
        return data;
    }

    T removeAt(size_t index)
    {
        if (head == nullptr)
            throw std::range_error("List is empty.");

        Node<T> *nodeToRemove = head;
        size_t currentIndex = 0;

        while (currentIndex < index)
        {
            nodeToRemove = nodeToRemove->next;

            if (nodeToRemove == nullptr)
            {
                throw std::range_error("List does not contain given index");
            }

            ++currentIndex;
        }

        if (nodeToRemove->prev != nullptr)
            nodeToRemove->prev->next = nodeToRemove->next;

        if (nodeToRemove->next != nullptr)
            nodeToRemove->next->prev = nodeToRemove->prev;

        T data = nodeToRemove->data;
        delete nodeToRemove;
        return data;
    }

    size_t indexOf(T elem)
    {

        Node<T> *nodePtr = head;
        size_t index = -1;

        while (nodePtr != nullptr)
        {
            ++index;

            if (elem == nodePtr->data)
                return index;

            nodePtr = nodePtr->next;
        }

        return -1;
    }

    static DoublyLinkedList *mergeSorted(DoublyLinkedList *list1, DoublyLinkedList *list2)
    {
        DoublyLinkedList<T> *newList = new DoublyLinkedList<T>;

        Node<T> *ptr1 = list1->head;
        Node<T> *ptr2 = list2->head;
        Node<T> *ptrNew = newList->head; // nullptr
        Node<T> *ptrNew2;

        while (ptr1 != nullptr && ptr2 != nullptr)
        {

            if (ptr1->data > ptr2->data)
            {
                ptrNew2 = new Node<T>(ptr2->data);
                ptr2 = ptr2->next;
            }
            else
            {
                ptrNew2 = new Node<T>(ptr1->data);
                ptr1 = ptr1->next;
            }

            if (ptrNew == nullptr)
            {
                newList->head = ptrNew2;
                newList->tail = ptrNew2;
            }
            else
            {
                ptrNew->next = ptrNew2;
                ptrNew2->prev = ptrNew;
            }

            ptrNew = ptrNew2;
        }

        while (ptr1 != nullptr)
        {
            ptrNew2 = new Node<T>(ptr1->data);
            ptr1 = ptr1->next;

            if (ptrNew == nullptr)
            {
                newList->head = ptrNew2;
                newList->tail = ptrNew2;
            }
            else
            {
                ptrNew->next = ptrNew2;
                ptrNew2->prev = ptrNew;
            }

            ptrNew = ptrNew2;
        }

        while (ptr2 != nullptr)
        {
            ptrNew2 = new Node<T>(ptr2->data);
            ptr2 = ptr2->next;

            if (ptrNew == nullptr)
            {
                newList->head = ptrNew2;
                newList->tail = ptrNew2;
            }
            else
            {
                ptrNew->next = ptrNew2;
                ptrNew2->prev = ptrNew;
            }

            ptrNew = ptrNew2;
        }

        return newList;
    }
};

int main(void)
{

    std::cout << "Merging sorted lists\n";
    // Test merging sorted lists
    int constexpr listSize = 20;

    DoublyLinkedList<int> list;
    DoublyLinkedList<int> alsoList;

    for (int i = listSize - 1; i >= 0; --i)
    {
        list.prepend(2 * i + 1);
        alsoList.prepend(2 * i);
    }

    list.printAll();
    alsoList.printAll();

    DoublyLinkedList<int> *mergedList = DoublyLinkedList<int>::mergeSorted(&list, &alsoList);

    mergedList->printAll();

    std::cout << "Inserting 10 after 8: ";
    mergedList->insertAfter(8, 10);
    mergedList->printAll();
}