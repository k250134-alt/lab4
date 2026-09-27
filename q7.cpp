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
        next = this;
        prev = this;
    }
};

class Train
{
public:
    Node* head;

    Train()
    {
        head = NULL;
    }

    void insert(int value)
    {
        Node* newNode = new Node(value);

        if (head == NULL)
        {
            head = newNode;
            return;
        }

        Node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;
    }

    Node* find(int value)
    {
        if (head == NULL)
            return NULL;

        Node* temp = head;

        do
        {
            if (temp->data == value)
                return temp;

            temp = temp->next;

        } while (temp != head);

        return NULL;
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "Train is empty." << endl;
            return;
        }

        Node* temp = head;

        do
        {
            cout << temp->data << " ";
            temp = temp->next;

        } while (temp != head);

        cout << endl;
    }

    void moveRight(int value)
    {
        Node* node = find(value);

        if (node == NULL || node == head)
            return;

        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void moveLeft(int value)
    {
        Node* node = find(value);

        if (node == NULL || node == head)
            return;

        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->prev = head->prev;
        node->next = head;

        head->prev->next = node;
        head->prev = node;
    }

    void setHead(int value)
    {
        Node* node = find(value);

        if (node != NULL)
            head = node;
    }

    void deleteNode(int value)
    {
        Node* node = find(value);

        if (node == NULL)
            return;

        if (node->next == node)
        {
            delete node;
            head = NULL;
            return;
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;

        if (node == head)
            head = node->next;

        delete node;
    }

    void searchShorter(int value)
    {
        Node* node = find(value);

        if (node == NULL)
        {
            cout << "Coach not found." << endl;
            return;
        }

        int nextSteps = 0;
        int prevSteps = 0;

        Node* temp = head;

        while (temp != node)
        {
            temp = temp->next;
            nextSteps++;
        }

        temp = head;

        while (temp != node)
        {
            temp = temp->prev;
            prevSteps++;
        }

        if (nextSteps <= prevSteps)
        {
            cout << "Direction: NEXT" << endl;
            cout << "Steps: " << nextSteps << endl;
        }
        else
        {
            cout << "Direction: PREV" << endl;
            cout << "Steps: " << prevSteps << endl;
        }
    }
};

int main()
{
    Train train;

    int n;

    cout << "Enter number of coaches: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        train.insert(value);
    }

    int commands;

    cout << "Enter number of commands: ";
    cin >> commands;

    for (int i = 0; i < commands; i++)
    {
        char command;
        int value;

        cin >> command >> value;

        if (command == 'R')
        {
            train.moveRight(value);

            cout << "After R " << value << ": ";
            train.display();
        }
        else if (command == 'L')
        {
            train.moveLeft(value);

            cout << "After L " << value << ": ";
            train.display();
        }
        else if (command == 'S')
        {
            train.setHead(value);

            cout << "After S " << value << ": ";
            train.display();
        }
        else if (command == 'D')
        {
            train.deleteNode(value);

            cout << "After D " << value << ": ";
            train.display();
        }
        else if (command == 'F')
        {
            cout << "F " << value << ":" << endl;
            train.searchShorter(value);
        }
    }

    return 0;
}
