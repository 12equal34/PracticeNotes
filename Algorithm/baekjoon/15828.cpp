#include <iostream>
#include <exception>

using namespace std;

template <typename T>
class MyQueue
{
public:
    MyQueue(size_t _capacity) :
        mCapacity(_capacity)
    {
        if (mCapacity < 2)
            mCapacity = 2;

        mArr = new T[mCapacity];
    }

    ~MyQueue()
    {
        delete[] mArr;
    }

    size_t GetSize()
    {
        return mSize;
    }

    void Push(T num)
    {
        if (++mSize > mCapacity) {
            // throw range_error("The input value exceeded the allowed capacity of the MyQueue object.");
            --mSize;
            return;
        }

        if (mLastIndex == mCapacity - 1){
            mLastIndex = 0;
            mArr[0] = num;
        }
        else {
            mArr[++mLastIndex] = num;
        }
    }

    T Pop()
    {
        if (--mSize < 0) {
            throw range_error("The MyQueue object is empty.");
        }

        if (mFirstIndex == mCapacity - 1) {
            mFirstIndex = 0;
            return mArr[mCapacity - 1];
        }
        else {
            return mArr[mFirstIndex++];
        }
    }

    bool Empty()
    {
        return mSize == 0;
    }

private:
    size_t mCapacity = 0;
    size_t mSize = 0;
    size_t mFirstIndex = 1;
    size_t mLastIndex = 0;
    T* mArr = nullptr;
};

template <typename T>
ostream& operator << (ostream& os, MyQueue<T>& q)
{
    while (!q.Empty())
    {
        cout << q.Pop() << ' ';
    }

    return os;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N; cin >> N;
    MyQueue<int> q(N);

    if (int num; N == 1) {
        cin >> num;
        cout << num;
        while (num != -1)
            cin >> num;
        return 0;
    }

    while (true)
    {
        int num; cin >> num;
        if (num == -1) 
            break;

        if (num == 0)
            q.Pop();
        else
            q.Push(num);
    }

    cout << q;

    return 0;
}