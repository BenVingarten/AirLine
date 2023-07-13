#include <iostream>

template<typename T>
class LinkedList
{

public:

    struct Node
    {
        T value;
        Node* next;

        Node(const T& val) : value(val), next(nullptr) {}
    };

    LinkedList() : head(nullptr) {}

    ~LinkedList() { clear(); }


    void add(const T& value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void remove(const T& value)
    {
        if (head == nullptr)
        {
            return;
        }

        if (head->value == value)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next != nullptr)
        {
            if (current->next->value == value)
            {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    void print(ostream& out)const
    {
        Node* current = head;
        int i = 0;
        while (current != nullptr)
        {
            out << (i + 1) << ") " << *(current->value) << endl;
            current = current->next;
            i++;
        }
        out << endl;
    }

    T getData(int index) const
    {
        Node* current = head;
        int currentIndex = 0;

        while (current != nullptr && currentIndex < index)
        {
            current = current->next;
            currentIndex++;
        }

        if (current != nullptr)
        {
            return current->value;
        }

        return nullptr;
    }

    Node* getHead() const
    {
        return head;
    }

    bool isInList(const T& element) const
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->value == element)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* nextNode = current->next;
            delete current->value;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    int getSize()const
    {
        int size = 0;
        Node* current = head;
        while (current != nullptr)
        {
            size++;
            current = current->next;
        }
        return size;

    }
private:
    
    Node* head;
    
};






