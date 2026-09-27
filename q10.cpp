#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = NULL;
    }
};

class LinkedList
{
public:
    Node* head;

    LinkedList()
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

        Node* temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
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

    void reverseGroups(int k)
    {
        if (head == NULL || k <= 1)
            return;

        Node* current = head;
        Node* previousGroupEnd = NULL;

        while (current != NULL)
        {
            Node* check = current;
            int count = 0;

            while (check != NULL && count < k)
            {
                check = check->next;
                count++;
            }

            if (count < k)
                break;

            Node* previous = NULL;
            Node* next = NULL;
            Node* groupStart = current;

            for (int i = 0; i < k; i++)
            {
                next = current->next;
                current->next = previous;
                previous = current;
                current = next;
            }

            if (previousGroupEnd == NULL)
            {
                head = previous;
            }
            else
            {
                previousGroupEnd->next = previous;
            }

            previousGroupEnd = groupStart;
            previousGroupEnd->next = current;
        }
    }
};

int main()
{
    LinkedList list;

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

    cout << "Enter K: ";
    cin >> k;

    cout << "Original List: ";
    list.display();

    list.reverseGroups(k);

    cout << "After Reversing Groups: ";
    list.display();

    return 0;
}
