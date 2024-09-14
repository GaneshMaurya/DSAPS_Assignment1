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

    int n, k;
    cin >> n >> k;

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    priority_queue_min minHeap1;
    priority_queue_max maxHeap1;
    double runningMedian[n];
    int st = 0;
    for (int i = 0; i < n; i++)
    {
        double median1;

        maxHeap1.push(arr[i]);
        if (maxHeap1.size() - minHeap1.size() > 1)
        {
            int temp = maxHeap1.top();
            maxHeap1.pop();
            minHeap1.push(temp);
        }

        if (maxHeap1.size() > 0 && minHeap1.size() > 0 && maxHeap1.top() > minHeap1.top())
        {
            int a = maxHeap1.top();
            int b = minHeap1.top();
            maxHeap1.pop();
            minHeap1.pop();
            maxHeap1.push(b);
            minHeap1.push(a);
        }

        if (maxHeap1.size() == minHeap1.size())
        {
            double a = maxHeap1.top();
            double b = minHeap1.top();

            median1 = (a + b) / 2.0;
        }
        else
        {
            median1 = (double)maxHeap1.top();
        }

        runningMedian[st] = median1;
        st++;
    }

    int it = 0;
    double lastKmedian[n - k + 1];
    st = 0;
    while (it < n - k + 1)
    {
        priority_queue_min minHeap2;
        priority_queue_max maxHeap2;
        double median2;

        int j = it;
        while (j < n && j < it + k)
        {
            maxHeap2.push(arr[j]);
            if (maxHeap2.size() - minHeap2.size() > 1)
            {
                int temp = maxHeap2.top();
                maxHeap2.pop();
                minHeap2.push(temp);
            }

            if (maxHeap2.size() > 0 && minHeap2.size() > 0 && maxHeap2.top() > minHeap2.top())
            {
                int a = maxHeap2.top();
                int b = minHeap2.top();
                maxHeap2.pop();
                minHeap2.pop();
                maxHeap2.push(b);
                minHeap2.push(a);
            }

            if (maxHeap2.size() == minHeap2.size())
            {
                double a = maxHeap2.top();
                double b = minHeap2.top();

                median2 = (a + b) / 2.0;
            }
            else
            {
                median2 = (double)maxHeap2.top();
            }

            j++;
        }
        // cout << "- " << median2 << endl;
        lastKmedian[st] = median2;
        st++;
        it++;
    }

    int count = 0;
    for (int i = k; i < n; i++)
    {
        double temp = runningMedian[i] + lastKmedian[i - k];
        if (temp <= arr[i])
        {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}