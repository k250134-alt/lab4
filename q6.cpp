#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;
    Node* child;

    Node(int value)
    {
        data = value;
        next = NULL;
        child = NULL;
    }
};

class List
{
public:
    Node* head;

    List()
    {
        head = NULL;
    }

    Node* findNode(int value)
    {
        Node* temp = head;

        while (temp != NULL)
        {
            if (temp->data == value)
                return temp;

            temp = temp->next;
        }

        return NULL;
    }

    void addNode(int value)
    {
        Node* newNode = new Node(value);

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            Node* temp = head;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
        }
    }

    void makeChild(int parent, int childHead)
    {
        Node* p = findNode(parent);
        Node* c = findNode(childHead);

        if (p != NULL)
            p->child = c;
    }

    void flatten(Node* cur)
    {
        if (cur == NULL)
            return;

        Node* nextNode = cur->next;

        if (cur->child != NULL)
        {
            Node* childHead = cur->child;

            flatten(childHead);

            Node* childTail = childHead;

            while (childTail->next != NULL)
                childTail = childTail->next;

            cur->next = childHead;
            childTail->next = nextNode;

            cur->child = NULL;
        }

        flatten(nextNode);
    }

    void display()
    {
        Node* temp = head;

        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }
};

int main()
{
    List list;

    int n;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter node values:" << endl;

    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        list.addNode(value);
    }

    int c;

    cout << "Enter number of child links: ";
    cin >> c;

    for (int i = 0; i < c; i++)
    {
        int parent, child;

        cout << "Enter parent and child: ";
        cin >> parent >> child;

        list.makeChild(parent, child);
    }

    list.flatten(list.head);

    cout << "Restructured List: ";
    list.display();

    return 0;
}
