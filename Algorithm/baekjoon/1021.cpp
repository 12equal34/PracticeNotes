#include <iostream>
#include <exception>
#include <vector>
using namespace std;

template <typename T>
class MyCircularQueue
{
public:
    MyCircularQueue(size_t _capacity):
        mCapacity(_capacity)
    {
        if (mCapacity < 2)
            mCapacity = 2;

        mArr = new T[mCapacity];
    }

    ~MyCircularQueue()
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
            // throw range_error("The input value exceeded the allowed capacity of the MyCircularQueue object.");
            return;
        }

        ++mSize;

        if (mFirstIndex == 0) {
            mFirstIndex = mCapacity - 1;
            mArr[mFirstIndex] = num;
        }
        else {
            mArr[--mFirstIndex] = num;
        }
    }

    void push_back(T num)
    {
        if (isFull()) {
            // throw range_error("The input value exceeded the allowed capacity of the MyCircularQueue object.");
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
            throw range_error("The MyCircularQueue object is empty.");
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
            throw range_error("The MyCircularQueue object is empty.");
        }

        --mSize;

        if (mLastIndex == 0) {
            mLastIndex = mCapacity - 1;
            return mArr[0];
        }
        else {
            return mArr[mLastIndex--];
        }
    }

    T front()
    {
        if (empty()) {
            throw range_error("The MyCircularQueue object is empty.");
        }
        return mArr[mFirstIndex];
    }

    T back()
    {
        if (empty()) {
            throw range_error("The MyCircularQueue object is empty.");
        }
        return mArr[mLastIndex];
    }

    void permuteLeft()
    {
        push_back(pop_front());
    }

    void permuteRight()
    {
        push_front(pop_back());
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
    int M; cin >> M;
    MyCircularQueue<int> q(N);
    for (int i = 1;i <= N;++i) {
        q.push_back(i);
    }

    int res = 0;
    for (int i = 0; i < M; ++i) {
        int n; cin >> n;
        int cnt = 0;
        while (n != q.front()) {
            q.permuteLeft();
            ++cnt;
        }
        res += min(cnt, static_cast<int>(q.size()) - cnt);
        q.pop_front();
    }

    cout << res;
    return 0;
}