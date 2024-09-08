#include <iostream>
using namespace std;

template <typename T>
class deque
{
private:
    long long int totalLength = 5;
    long long int length = 0;
    long long int head = -1;
    long long int tail = -1;
    T *arr;

public:
    deque()
    {
        arr = new T[totalLength];
    }
    deque(long long int s)
    {
        totalLength = s;
        arr = new T[totalLength];
    }
    deque(long long int s, T x)
    {
        totalLength = s;
        arr = new T[totalLength];
        for (long long int i = 0; i < totalLength; i++)
        {
            tail = (tail + 1) % totalLength;
            arr[i] = x;
        }
    }

    void push_back(T x)
    {
        if (length + 1 < totalLength)
        {
            if (head == -1)
            {
                head = 0;
            }

            tail = (tail + 1) % totalLength;
            arr[tail] = x;
            length++;
        }
        else
        {
            T *arrNew = new T[2 * length];
            long long int i = 0;
            long long int j = head;
            while (true)
            {
                arrNew[i] = arr[j];
                if (j == tail)
                {
                    break;
                }
                i++;
                j = (j + 1) % totalLength;
            }

            delete[] arr;
            arr = arrNew;

            totalLength = 2 * length;
            head = 0;
            arr[i + 1] = x;
            tail = i + 1;
            length++;
        }
    }

    void pop_back()
    {
        if (!empty())
        {
            tail = (totalLength + tail - 1) % totalLength;
            length--;
        }
    }

    void push_front(T x)
    {
        if (length + 1 < totalLength)
        {
            if (tail == -1)
            {
                tail = 0;
            }

            head = (totalLength + head - 1) % totalLength;
            arr[head] = x;
            length++;
        }
        else
        {
            T *arrNew = new T[2 * length];
            arrNew[0] = x;
            long long int i = 1;
            long long int j = head;
            while (true)
            {
                arrNew[i] = arr[j];
                if (j == tail)
                {
                    break;
                }
                i++;
                j = (j + 1) % totalLength;
            }

            delete[] arr;
            arr = arrNew;

            totalLength = 2 * length;
            head = 0;
            tail = i;
            length++;
        }
    }

    void pop_front()
    {
        if (!empty())
        {
            head = (head + 1) % totalLength;
            length--;
        }
    }

    T front()
    {
        return arr[head];
    }

    T back()
    {
        return arr[tail];
    }

    T operator[](long long int n)
    {
        if (n < 0)
        {
            long long int temp = (tail + 1 + n) % totalLength;
            if (temp < 0)
            {
                temp += totalLength;
            }
            return arr[temp];
        }
        else if (n > length)
        {
            return arr[head];
        }
        else
        {
            long long int temp = (head + n) % totalLength;
            return arr[temp];
        }
    }

    bool empty()
    {
        if (abs(head - tail) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    long long int size()
    {
        return length;
    }

    void clear()
    {
        head = -1;
        tail = -1;
    }

    long long int capacity()
    {
        return totalLength;
    }

    void resize(long long int n)
    {
        if (totalLength < n)
        {
            T *arrNew = new T[n];
            long long int i = 0;
            long long int j = head;
            while (true)
            {
                arrNew[i] = arr[j];
                if (j == tail)
                {
                    break;
                }
                i++;
                j = (j + 1) % totalLength;
            }

            delete[] arr;
            arr = arrNew;

            totalLength = n;
            head = 0;
            tail = i;
        }
    }

    void resize(long long int n, T d)
    {
        if (totalLength < n)
        {
            T *arrNew = new T[n];
            long long int i = 0;
            long long int j = head;
            while (true)
            {
                arrNew[i] = arr[j];
                if (j == tail)
                {
                    break;
                }
                i++;
                j = (j + 1) % totalLength;
            }

            delete[] arr;
            arr = arrNew;

            totalLength = n;
            head = 0;
            arr[i + 1] = d;
            tail = i + 1;
        }
    }

    void reserve(long long int n)
    {
        if (n > totalLength)
        {
            totalLength = n;
        }
    }

    void shrink_to_fit()
    {
        // if (length == 0)
        // {
        //     delete[] arr;
        //     arr = NULL;
        //     head = -1;
        //     tail = -1;
        //     totalLength = 0;
        //     return;
        // }

        T *arrNew = new T[length];
        long long int i = 0;
        long long int j = head;
        while (i < length)
        {
            arrNew[i] = arr[j];
            i++;
            j = (j + 1) % totalLength;
        }

        delete[] arr;
        arr = arrNew;

        head = 0;
        tail = length - 1;
        totalLength = length;
    }

    void printAll()
    {
        cout << "Head: " << head << endl;
        cout << "Tail: " << tail << endl;

        long long int i = head;
        while (true)
        {
            cout << arr[i] << " ";
            if (i == tail)
            {
                break;
            }
            i = (i + 1) % totalLength;
        }
        cout << endl;
    }
};

int main()
{
    deque<string> dq(5);

    dq.push_back("4");
    dq.push_back("5");
    dq.push_front("1");
    dq.push_front("2");
    dq.push_front("3");

    dq.printAll();
    // dq.push_back(7);
    // dq.printAll();

    // cout << dq.empty() << endl;
    // cout << dq.size() << endl;

    // dq.resize(10, "11");
    // cout << dq.capacity() << endl;

    // for (long long int i = 0; i < dq.capacity(); i++)
    // {
    //     cout << dq[i] << ", ";
    // }
    // cout << endl;

    dq.push_back("6");
    dq.push_front("7");

    dq.printAll();
    cout << dq[-1] << endl;
    dq.shrink_to_fit();
    dq.printAll();
    cout << dq.capacity() << endl;

    return 0;
}
