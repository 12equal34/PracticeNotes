#include <iostream>
#include <tuple>
#include <vector>
#include <limits>

using namespace std;

int cnt = 0;
int res = -1;
int K;

void merge(vector<int> &A, int low, int mid, int high)
{
    int n_l = mid - low + 1;
    int n_r = high - mid;
    vector<int> L(n_l+1);
    vector<int> R(n_r+1);
    
    for (int i = 0; i<n_l; i++)
    {
        L[i] = A[low+i];
        R[i] = A[mid+1+i];
    }
    L[n_l] = R[n_r] = numeric_limits<int>::max();
    
    int i = 0, j = 0;
    for (int p = low; p<=high; p++)
    {
        if (L[i] > R[j]) {
            A[p] = R[j++];
        }
        else {
            A[p] = L[i++];
        }
        
        if (++cnt == K)
            res = A[p];
    }
}

void merge_sort(vector<int> &A, int low, int high)
{
    if (low == high)
        return;

    int mid = (low + high) / 2;
    merge_sort(A, low, mid);
    merge_sort(A, mid + 1, high);
    merge(A, low, mid, high);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N >> K;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> A[i];
    }

    merge_sort(A, 1, N);
    cout << res << '\n';
}