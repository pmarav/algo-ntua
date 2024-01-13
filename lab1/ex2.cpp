#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int64_t> parse()
{
    int N;
    cin >> N;
    vector<int64_t> H;
    H.reserve(N);
    for (int i = 0; i < N; i++)
    {
        int temp;
        cin >> temp;
        H.push_back(temp);
    }
    return H;
}

template <typename T>
vector<int64_t> findRunningSum(T begin, T end)
{
    vector<int64_t> left;
    left.reserve(distance(begin, end));
    left.push_back(*begin);

    stack<int64_t> s;
    s.push(0);

    for (auto iter = begin + 1; iter != end; iter++)
    {
        left.push_back(left.back() + *iter);
        int top;
        while (!s.empty() && *iter > *(begin + s.top()))
        {
            top = s.top();
            s.pop();
            if (!s.empty())
                left.back() += (top - s.top()) * (*iter - *(begin + top));
            else
                left.back() += (top + 1) * (*iter - *(begin + top));
        }
        s.push(left.size() - 1);
    }
    return left;
}

int64_t findMin(const vector<int64_t> &H, const vector<int64_t> &left, const vector<int64_t> &right)
{
    int64_t min = left[0] + right[H.size() - 1] - H[0];
    for (int i = 1; i < H.size(); i++)
    {
        int64_t sum = left[i] + right[H.size() - 1 - i] - H[i];
        if (min > sum)
            min = sum;
    }
    return min;
}

int main()
{
    vector<int64_t> H = parse();

    vector<int64_t> left = findRunningSum(H.begin(), H.end());

    vector<int64_t> right = findRunningSum(H.rbegin(), H.rend());

    cout << findMin(H, left, right) << endl;
}
