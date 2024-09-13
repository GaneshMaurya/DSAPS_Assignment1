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
    priority_queue_min minHeap1;
    priority_queue_max maxHeap1;

    int n, k;
    cin >> n >> k;

    int count = 0;

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (maxHeap1.empty() || maxHeap1.top() >= arr[i])
        {
            maxHeap1.push(arr[i]);
        }
        else
        {
            minHeap1.push(arr[i]);
        }

        if (maxHeap1.size() > minHeap1.size() + 1)
        {
            int temp = maxHeap1.top();
            maxHeap1.pop();
            minHeap1.push(temp);
        }
        else if (maxHeap1.size() < minHeap1.size())
        {
            int temp = minHeap1.top();
            minHeap1.pop();
            maxHeap1.push(temp);
        }

        double median1;
        if (maxHeap1.size() == minHeap1.size())
        {
            double a = maxHeap1.top();
            double b = minHeap1.top();

            median1 = (a + b) / 2.0;
        }
        else
        {
            median1 = maxHeap1.top();
        }
    }

    priority_queue_min minHeap2;
    priority_queue_max maxHeap2;
    for (int i = 0; i < n; i++)
    {
    }

    cout << count << endl;

    return 0;
}