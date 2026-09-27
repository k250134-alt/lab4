#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value)
    {
        data = value;
        next = NULL;
        prev = NULL;
    }
};

class LinkedList
{
public:
    Node* head;
    Node* tail;
    int type;
    int size;

    LinkedList()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    void insert(int value)
    {
        Node* newNode = new Node(value);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
            size++;

            if (type == 3 || type == 4)
            {
                head->next = head;

                if (type == 4)
                    head->prev = head;
            }

            return;
        }

        if (type == 1)
        {
            tail->next = newNode;
            tail = newNode;
        }

        else if (type == 2)
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        else if (type == 3)
        {
            newNode->next = head;
            tail->next = newNode;
            tail = newNode;
        }

        else if (type == 4)
        {
            newNode->next = head;
            newNode->prev = tail;

            tail->next = newNode;
            head->prev = newNode;

            tail = newNode;
        }

        size++;
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "Empty" << endl;
            return;
        }

        Node* temp = head;

        if (type == 1 || type == 2)
        {
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
        else
        {
            do
            {
                cout << temp->data << " ";
                temp = temp->next;

            } while (temp != head);
        }

        cout << endl;
    }

    void rotateRight(int k)
    {
        if (size == 0)
            return;

        k = k % size;

        for (int i = 0; i < k; i++)
        {
            if (type == 1)
            {
                Node* newTail = head;

                while (newTail->next != tail)
                    newTail = newTail->next;

                tail->next = head;
                head = tail;
                tail = newTail;
                tail->next = NULL;
            }

            else if (type == 2)
            {
                Node* newTail = tail->prev;

                tail->next = head;
                head->prev = tail;

                head = tail;
                tail = newTail;

                tail->next = NULL;
                head->prev = NULL;
            }

            else
            {
                head = tail;
                tail = head->prev;
            }
        }
    }

    void rotateLeft(int k)
    {
        if (size == 0)
            return;

        k = k % size;

        for (int i = 0; i < k; i++)
        {
            if (type == 1)
            {
                tail->next = head;
                head = head->next;
                tail->next = NULL;
            }

            else if (type == 2)
            {
                Node* oldHead = head;

                head = head->next;
                head->prev = NULL;

                tail->next = oldHead;
                oldHead->prev = tail;

                tail = oldHead;
                tail->next = NULL;
            }

            else
            {
                head = head->next;
                tail = tail->next;
            }
        }
    }
};

int main()
{
    LinkedList list;

    cout << "Select List Type:" << endl;
    cout << "1. Singly Linked List" << endl;
    cout << "2. Doubly Linked List" << endl;
    cout << "3. Circular Linked List" << endl;
    cout << "4. Doubly Circular Linked List" << endl;

    cout << "Enter choice: ";
    cin >> list.type;

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;

        list.insert(value);
    }

    int k;
    char direction;

    cout << "Enter K: ";
    cin >> k;

    cout << "Enter direction (L/R): ";
    cin >> direction;

    if (direction == 'R' || direction == 'r')
        list.rotateRight(k);
    else
        list.rotateLeft(k);

    cout << "After Rotation: ";
    list.display();

    return 0;
}
