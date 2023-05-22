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
class SinglyLinkedList
{
    Node<T> *head;

    Node<T> *tail()
    {
        Node<T> *i = head;

        if (i == nullptr)
            return i;

        while (i->next != nullptr)
        {
            i = i->next;
        }

        return i;
    }

    Node<T> *_mergeSort(Node<T> *head)
    {

        if (head == nullptr || head->next == nullptr)
            return head;

        Node<T> *toTail = head->next;
        Node<T> *middle = head;

        while (toTail != nullptr && toTail->next != nullptr)
        {
            toTail = toTail->next->next;
            middle = middle->next;
        }

        Node<T> *ptr2 = _mergeSort(middle->next);
        middle->next = nullptr;
        Node<T> *ptr1 = _mergeSort(head);

        Node<T> *newHead;
        Node<T> *ptrNew = nullptr; // nullptr
        Node<T> *ptrNew2;

        while (ptr1 != nullptr && ptr2 != nullptr)
        {

            if (ptr1->data < ptr2->data)
            {
                ptrNew2 = ptr1;
                ptr1 = ptr1->next;
            }
            else
            {
                ptrNew2 = ptr2;
                ptr2 = ptr2->next;
            }

            if (ptrNew == nullptr)
                newHead = ptrNew2;
            else
                ptrNew->next = ptrNew2;

            ptrNew = ptrNew2;
        }

        if (ptr1 != nullptr)
        {
            if (ptrNew == nullptr)
                newHead = ptr1;
            else
                ptrNew->next = ptr1;
        }
        else if (ptr2 != nullptr)
        {
            if (ptrNew == nullptr)
                newHead = ptr2;
            else
                ptrNew->next = ptr2;
        }

        return newHead;
    }

public:
    SinglyLinkedList() : head(nullptr){};

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

        newHead->next = head;
        head = newHead;
    }

    void append(T data)
    {
        Node<T> *newTail = new Node<T>(data);

        newTail->next = nullptr;

        if (head == nullptr)
        {
            head = newTail;
        }
        else
        {
            tail()->next = newTail;
        }
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

        T data = oldHead->data;

        delete oldHead;
        return data;
    }

    T removeTail()
    {
        if (head == nullptr)
            throw std::range_error("List is empty.");

        Node<T> *newTail = nullptr;
        Node<T> *oldTail = head;

        while (oldTail->next != nullptr)
        {
            newTail = oldTail;
            oldTail = oldTail->next;
        }

        if (newTail != nullptr)
        {
            newTail->next = nullptr;
        }

        T data = oldTail->data;
        delete oldTail;
        return data;
    }

    T removeAt(size_t index)
    {
        if (head == nullptr)
            throw std::range_error("List is empty.");

        Node<T> *prevNode = nullptr;
        Node<T> *nodeToRemove = head;
        size_t currentIndex = 0;

        while (currentIndex < index)
        {
            prevNode = nodeToRemove;
            nodeToRemove = nodeToRemove->next;

            if (nodeToRemove == nullptr)
            {
                throw std::range_error("List does not contain given index");
            }

            ++currentIndex;
        }

        if (prevNode != nullptr)
        {
            prevNode->next = nodeToRemove->next;
        }

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

    void mergeSort()
    {
        Node<T> *newHead = _mergeSort(head);
        head = newHead;

        return;
    }

    static SinglyLinkedList *mergeSorted(SinglyLinkedList *list1, SinglyLinkedList *list2)
    {
        SinglyLinkedList<T> *newList = new SinglyLinkedList<T>;

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
                newList->head = ptrNew2;
            else
                ptrNew->next = ptrNew2;

            ptrNew = ptrNew2;
        }

        while (ptr1 != nullptr)
        {
            ptrNew2 = new Node<T>(ptr1->data);
            ptr1 = ptr1->next;

            if (ptrNew == nullptr)
                newList->head = ptrNew2;
            else
                ptrNew->next = ptrNew2;

            ptrNew = ptrNew2;
        }

        while (ptr2 != nullptr)
        {
            ptrNew2 = new Node<T>(ptr2->data);
            ptr2 = ptr2->next;

            if (ptrNew == nullptr)
                newList->head = ptrNew2;
            else
                ptrNew->next = ptrNew2;

            ptrNew = ptrNew2;
        }

        return newList;
    }
};

int main(void)
{

    std::cout << "Merging sorted lists\n";
    // Test merging sorted lists
    int constexpr listSize = 5;

    SinglyLinkedList<int> list;
    SinglyLinkedList<int> alsoList;

    for (int i = listSize - 1; i >= 0; --i)
    {
        list.prepend(2 * i + 1);
        alsoList.prepend(2 * i);
    }

    list.printAll();
    alsoList.printAll();

    SinglyLinkedList<int> *mergedList = SinglyLinkedList<int>::mergeSorted(&list, &alsoList);

    mergedList->printAll();
    mergedList->insertAfter(8, 10);
    mergedList->printAll();

    std::cout << "\nSorting list using merge-sort\n";
    // Test merge-sort
    SinglyLinkedList<int> unsortedList;

    for (int i = 0; i < listSize; ++i)
    {
        unsortedList.prepend(rand() % 1000 + 1);
    }

    unsortedList.printAll();
    unsortedList.mergeSort();
    unsortedList.printAll();
}