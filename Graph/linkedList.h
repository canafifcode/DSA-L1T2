#ifndef lINKEDLIST_H
#define lINKEDLIST_H

#include <iostream>

struct Node
{
    int element;
    Node *next;
    Node *prev;
};

class linkedList
{
private:
    Node *head;
    Node *tail;
    Node *cur;
    int _size;

    void print() const
    {
        if (_size == 0)
        {
            std::cout << "[.]\n";
            return;
        }
        std::cout << "[";
        Node *tmp = head;
        while (tmp != nullptr)
        {
            std::cout << tmp->element << " ";
            if (tmp == cur)
                std::cout << "\b| ";
            tmp = tmp->next;
        }
        std::cout << "\b]\n";
    }

    void copyList(const Node *otherHead)
    {
        clear();
        if (!otherHead)
            return;
        head = new Node{otherHead->element, nullptr, nullptr};
        Node *current = head;
        otherHead = otherHead->next;
        while (otherHead)
        {
            current->next = new Node{otherHead->element, nullptr, current};
            current = current->next;
            otherHead = otherHead->next;
        }
        tail = current;
        cur = head;
    }

public:
    linkedList() : head(nullptr), tail(nullptr), cur(nullptr), _size(0) {}

    linkedList(const linkedList &other) : head(nullptr)
    {
        copyList(other.head);
    }

    
    linkedList &operator=(const linkedList &other)
    {
        if (this != &other)
        {
            copyList(other.head);
        }
        return *this;
    }
    ~linkedList()
    {
        clear();
    }

    void append(int item)
    {
        Node *newNode = new Node{item, nullptr, nullptr};
        if (head == nullptr)
        {
            head = tail = cur = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        _size++;
        // print();
    }

    void insert(int item)
    {
        Node *newNode = new Node{item, nullptr, nullptr};
        if (head == nullptr)
        {
            head = tail = cur = newNode;
        }
        else
        {
            newNode->prev = cur;
            newNode->next = cur->next;
            if (cur->next != nullptr)
                cur->next->prev = newNode;
            else
                tail = newNode;
            cur->next = newNode;
            cur = newNode;
        }
        _size++;
        
    }

    int deleteCur()
    {
        if (_size == 0)
        {
            std::cout << "not valid operation\n";
            return -1;
        }
        Node *tmp = cur;
        int deletedItem = tmp->element;

        if (cur == head)
        {
            head = cur->next;
            if (head != nullptr)
                head->prev = nullptr;
        }
        if (cur == tail)
        {
            tail = tmp->prev;
            if (tail != nullptr)
                tail->next = nullptr;
        }
        else
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
        }

        cur = (tmp->next == nullptr) ? tmp->prev : tmp->next;
        _size--;
        delete tmp;
        
        return deletedItem;
    }

    int size() const
    {
        return _size;
    }

    void movePrev(int n)
    {
        for (int i = 0; i < n && cur != nullptr && cur->prev != nullptr; i++)
            cur = cur->prev;
        
    }

    void moveNext(int n)
    {
        for (int i = 0; i < n && cur != nullptr && cur->next != nullptr; i++)
            cur = cur->next;
    }

    bool isPresent(int n) const
    {
        Node *tmp = head;
        while (tmp != nullptr)
        {
            if (tmp->element == n)
                return true;
            tmp = tmp->next;
        }
        return false;
    }

    void clear()
    {
        Node *tmp = head;
        while (tmp != nullptr)
        {
            Node *next = tmp->next;
            delete tmp;
            tmp = next;
        }
        head = tail = cur = nullptr;
        _size = 0;
        // print();
    }

    void deleteItem(int item)
    {
        Node *tmp = head;
        while (tmp != nullptr)
        {
            if (tmp->element == item)
            {
                Node *prevCur = cur;
                cur = tmp;
                deleteCur();
                if (prevCur != tmp)
                    cur = prevCur;
                return;
            }
            tmp = tmp->next;
        }
        //std::cout << item << " not found\n";
    }

    void swapIndices(int ind1, int ind2)
    {
        Node *temp1 = head;
        Node *temp2 = head;
        int i = 0;
        while (i < ind1 && temp1 != nullptr)
        {
            temp1 = temp1->next;
            i++;
        }
        i = 0;
        while (i < ind2 && temp2 != nullptr)
        {
            temp2 = temp2->next;
            i++;
        }
        if (temp1 && temp2)
        {
            std::swap(temp1->element, temp2->element);
            
        }
    }
    Node *getHead() const
    {
        return head;
    }
};

#endif // lINKEDLIST_H
