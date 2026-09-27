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

    LinkedList()
    {
        head = NULL;
        tail = NULL;
        type = 1;
    }

    void insert(int value)
    {
        Node* newNode = new Node(value);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;

            if (type == 3 || type == 4)
            {
                head->next = head;

                if (type == 4)
                {
                    head->prev = head;
                }
            }

            return;
        }

        tail->next = newNode;

        if (type == 2 || type == 4)
        {
            newNode->prev = tail;
        }

        tail = newNode;

        if (type == 3)
        {
            tail->next = head;
        }

        if (type == 4)
        {
            tail->next = head;
            head->prev = tail;
        }
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "Empty";
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
    }

    int countNodes()
    {
        if (head == NULL)
            return 0;

        int count = 0;
        Node* temp = head;

        if (type == 1 || type == 2)
        {
            while (temp != NULL)
            {
                count++;
                temp = temp->next;
            }
        }
        else
        {
            do
            {
                count++;
                temp = temp->next;

            } while (temp != head);
        }

        return count;
    }

    void radixSort()
    {
        int n = countNodes();

        if (n <= 1)
            return;

        int* arr = new int[n];

        Node* temp = head;

        for (int i = 0; i < n; i++)
        {
            arr[i] = temp->data;
            temp = temp->next;

            if ((type == 3 || type == 4) && temp == head)
                break;
        }

        int maximum = arr[0];

        for (int i = 1; i < n; i++)
        {
            if (arr[i] > maximum)
                maximum = arr[i];
        }

        for (int place = 1; maximum / place > 0; place *= 10)
        {
            int output[100];
            int count[10] = {0};

            for (int i = 0; i < n; i++)
                count[(arr[i] / place) % 10]++;

            for (int i = 1; i < 10; i++)
                count[i] += count[i - 1];

            for (int i = n - 1; i >= 0; i--)
            {
                output[count[(arr[i] / place) % 10] - 1] = arr[i];
                count[(arr[i] / place) % 10]--;
            }

            for (int i = 0; i < n; i++)
                arr[i] = output[i];
        }

        temp = head;

        for (int i = 0; i < n; i++)
        {
            temp->data = arr[i];
            temp = temp->next;
        }

        delete[] arr;
    }

    bool isCycle()
    {
        if (head == NULL)
            return false;

        if (type == 3 || type == 4)
            return true;

        return false;
    }
};

int main()
{
    int n;

    cout << "Enter number of linked lists: ";
    cin >> n;

    LinkedList* lists = new LinkedList[n];

    int previousType = -1;

    for (int i = 0; i < n; i++)
    {
        int type;

        cout << endl;
        cout << "List " << i + 1 << endl;

        cout << "1. Singly" << endl;
        cout << "2. Doubly" << endl;
        cout << "3. Circular" << endl;
        cout << "4. Doubly Circular" << endl;

        cout << "Enter type: ";
        cin >> type;

        while (type == previousType)
        {
            cout << "Same type cannot be consecutive. Enter again: ";
            cin >> type;
        }

        lists[i].type = type;
        previousType = type;

        int m;

        cout << "Enter number of elements: ";
        cin >> m;

        cout << "Enter elements: ";

        for (int j = 0; j < m; j++)
        {
            int value;
            cin >> value;
            lists[i].insert(value);
        }
    }

    int cycles = 0;

    cout << endl;
    cout << "After Radix Sort:" << endl;

    for (int i = 0; i < n; i++)
    {
        lists[i].radixSort();

        cout << "List " << i + 1 << ": ";
        lists[i].display();

        if (lists[i].isCycle())
            cycles++;

        cout << endl;
    }

    cout << endl;
    cout << "Number of cycles: " << cycles << endl;

    delete[] lists;

    return 0;
}
