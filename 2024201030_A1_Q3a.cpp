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
        int length = 0;
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
            }

            i = par;
        }

        length++;
    }

    int top()
    {
        if (!empty())
        {
            return arr[0];
        }
    }

    void pop()
    {
        if (!empty())
        {
            swap(arr[0], arr[length - 1]);
            length--;
            int i = 0;
            while (i < (length - 1) / 2)
            {
                int c1 = 2 * i + 1;
                int c2 = 2 * i + 2;
                if (arr[c1] < arr[c2])
                {
                    swap(arr[i], arr[c1]);
                    i = c1;
                }
                else
                {
                    swap(arr[i], arr[c2]);
                    i = c2;
                }
            }
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
        int length = 0;
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
            }

            i = par;
        }

        length++;
    }

    int top()
    {
        if (!empty())
        {
            return arr[0];
        }
    }

    void pop()
    {
        if (!empty())
        {
            swap(arr[0], arr[length - 1]);
            length--;
            int i = 0;
            while (i < (length - 1) / 2)
            {
                int c1 = 2 * i + 1;
                int c2 = 2 * i + 2;
                if (arr[c1] > arr[c2])
                {
                    swap(arr[i], arr[c1]);
                    i = c1;
                }
                else
                {
                    swap(arr[i], arr[c2]);
                    i = c2;
                }
            }
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
    priority_queue_max pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(0);
    pq.push(-1);

    pq.printAll();
    pq.pop();
    pq.printAll();
    pq.pop();
    pq.printAll();
    pq.pop();
    pq.printAll();
    pq.pop();
    pq.printAll();
    pq.push(5);
    pq.printAll();
    pq.pop();
    pq.printAll();
    pq.pop();
    pq.printAll();

    cout << pq.size() << endl;
    cout << pq.top() << endl;

    return 0;
}