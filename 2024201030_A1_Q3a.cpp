#include <iostream>
using namespace std;

class priority_queue_min
{
private:
    int arr[200000];
    int length = 0;

public:
    priority_queue_min()
    {
    }

    void push(int el)
    {
        arr[length] = el;
        int i = length;

        while (i > 0)
        {
            int par = (i - 1) / 2;

            if (arr[i] < arr[par])
            {
                swap(arr[i], arr[par]);
                i = par;
            }
            else
            {
                break;
            }
        }

        length++;
    }

    int top()
    {
        if (!empty())
        {
            return arr[0];
        }
        else
        {
            cout << "Error. The priority queue is empty\n";
            return 0;
        }
    }

    void pop()
    {
        if (!empty())
        {
            swap(arr[0], arr[length - 1]);
            length--;
            int i = 0;
            while (2 * i + 1 < length)
            {
                int c1 = 2 * i + 1;
                int c2 = 2 * i + 2;

                int temp = c1;
                if (c2 < length)
                {
                    temp = arr[c1] < arr[c2] ? c1 : c2;
                }
                if (arr[i] > arr[temp])
                {
                    swap(arr[i], arr[temp]);
                    i = temp;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            cout << "Error. The priority queue is empty\n";
        }
    }

    int size()
    {
        return length;
    }

    bool empty()
    {
        return length == 0;
    }

    void printAll()
    {
        for (int i = 0; i < size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

class priority_queue_max
{
private:
    int arr[200000];
    int length = 0;

public:
    priority_queue_max()
    {
    }

    void push(int el)
    {
        arr[length] = el;
        int i = length;

        while (i > 0)
        {
            int par = (i - 1) / 2;

            if (arr[i] > arr[par])
            {
                swap(arr[i], arr[par]);
                i = par;
            }
            else
            {
                break;
            }
        }

        length++;
    }

    int top()
    {
        if (!empty())
        {
            return arr[0];
        }
        else
        {
            cout << "Error. The priority queue is empty\n";
            return 0;
        }
    }

    void pop()
    {
        if (!empty())
        {
            swap(arr[0], arr[length - 1]);
            length--;
            int i = 0;
            while (2 * i + 1 < length)
            {
                int c1 = 2 * i + 1;
                int c2 = 2 * i + 2;

                int temp = c1;
                if (c2 < length)
                {
                    temp = arr[c1] > arr[c2] ? c1 : c2;
                }
                if (arr[i] < arr[temp])
                {
                    swap(arr[i], arr[temp]);
                    i = temp;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            cout << "Error. The priority queue is empty\n";
        }
    }

    int size()
    {
        return length;
    }

    bool empty()
    {
        return length == 0;
    }

    void printAll()
    {
        for (int i = 0; i < size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    // Enter choice - 0 = Min Heap, 1 = Max Heap
    int choice;
    cin >> choice;

    priority_queue_min minHeap;
    priority_queue_max maxHeap;

    if (choice != 0 && choice != 1)
    {
        cout << "Wrong choice entered.\n";
        return 1;
    }

    while (true)
    {
        // Operation
        int operation;
        cin >> operation;

        switch (operation)
        {
        case 1: // Size
        {
            if (choice == 0)
            {
                cout << minHeap.size() << endl;
            }
            else
            {
                cout << maxHeap.size() << endl;
            }
        }
        break;
        case 2: // Push
        {
            int el;
            cin >> el;
            if (choice == 0)
            {
                minHeap.push(el);
            }
            else
            {
                maxHeap.push(el);
            }
        }
        break;
        case 3: // Top
        {
            if (choice == 0)
            {
                cout << minHeap.top() << endl;
            }
            else
            {
                cout << maxHeap.top() << endl;
            }
        }
        break;
        case 4: // Pop
        {
            if (choice == 0)
            {
                minHeap.pop();
            }
            else
            {
                maxHeap.pop();
            }
        }
        break;
        case 5: // Empty
        {
            if (choice == 0)
                cout << (minHeap.empty() ? "Min Heap is empty" : "Min Heap is not empty") << endl;
            else
                cout << (maxHeap.empty() ? "Max Heap is empty" : "Max Heap is not empty") << endl;
        }
        break;
        default: // Exit
        {
            cout << "Exit\n";
            return 0;
        }
        }
    }

    return 0;
}