#include <iostream>
#include <exception>

using namespace std;

template <typename T>
class MyDeque
{
public:
    MyDeque(size_t _capacity):
        mCapacity(_capacity)
    {
        if (mCapacity < 2)
            mCapacity = 2;

        mArr = new T[mCapacity];
    }

    ~MyDeque()
    {
        delete[] mArr;
    }

    size_t size()
    {
        return mSize;
    }

    void push_front(T num)
    {
        if (isFull()) {
            // throw range_error("The input value exceeded the allowed capacity of the MyDeque object.");
            return;
        }

        ++mSize;

        if (mFirstIndex == 0) {
            mFirstIndex = mCapacity-1;
            mArr[mFirstIndex] = num;
        }
        else {
            mArr[--mFirstIndex] = num;
        }
    }

    void push_back(T num)
    {
        if (isFull()) {
            // throw range_error("The input value exceeded the allowed capacity of the MyDeque object.");
            return;
        }

        ++mSize;

        if (mLastIndex == mCapacity - 1) {
            mLastIndex = 0;
            mArr[0] = num;
        }
        else {
            mArr[++mLastIndex] = num;
        }
    }

    T pop_front()
    {
        if (empty()) {
            throw range_error("The MyDeque object is empty.");
        }

        --mSize;

        if (mFirstIndex == mCapacity - 1) {
            mFirstIndex = 0;
            return mArr[mCapacity - 1];
        }
        else {
            return mArr[mFirstIndex++];
        }
    }

    T pop_back()
    {
        if (empty()) {
            throw range_error("The MyDeque object is empty.");
        }

        --mSize;

        if (mLastIndex == 0) {
            mLastIndex = mCapacity-1;
            return mArr[0];
        }
        else {
            return mArr[mLastIndex--];
        }
    }

    T front()
    {
        if (empty()) {
            throw range_error("The MyDeque object is empty.");
        }
        return mArr[mFirstIndex];
    }

    T back()
    {
        if (empty()) {
            throw range_error("The MyDeque object is empty.");
        }
        return mArr[mLastIndex];
    }

    bool empty()
    {
        return mSize == 0;
    }

    bool isFull()
    {
        return mSize == mCapacity;
    }

private:
    size_t mCapacity = 0;
    size_t mSize = 0;
    size_t mFirstIndex = 1;
    size_t mLastIndex = 0;
    T* mArr = nullptr;
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N; cin >> N;
    MyDeque<int> deque((size_t)10000);

    for (int i = 0; i < N; ++i) {
        string str; cin >> str;
        if (str == "push_front") {
            int num; cin >> num;
            deque.push_front(num);
        }
        else if (str == "push_back") {
            int num; cin >> num;
            deque.push_back(num);
        }
        else if (str == "pop_front") {
            cout << (!deque.empty() ? deque.pop_front() : -1) << '\n';
        }
        else if (str == "pop_back") {
            cout << (!deque.empty() ? deque.pop_back() : -1) << '\n';
        }
        else if (str == "size") {
            cout << deque.size() << '\n';
        }
        else if (str == "empty") {
            cout << noboolalpha << deque.empty() << '\n';
        }
        else if (str == "front") {
            cout << (!deque.empty() ? deque.front() : -1) << '\n';
        }
        else if (str == "back") {
            cout << (!deque.empty() ? deque.back() : -1) << '\n';
        }
    }

    return 0;
}