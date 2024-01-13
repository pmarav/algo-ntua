#include <iostream>
#include <vector>
#include <algorithm>

vector<int> findLIS(vector<int>::itterator* begin,vector<int>::itterator* end);
int neg(int i);
int max(vector<int> &left , vector<int> &right);




int main()
{
    uint32_t N,K;
    scanf("%d",&N);
    scanf("%d",&K);

    vector<int> credit(N);

    for(auto i;i<N;i++)
    {
        scanf("%d",&credit[i]);
    }


    vector<int> right = findLIS(credit.rbegin(),credit.rend());

    credit = findLIS(credit.begin(),credit.end());

    transform( credit.begin(),credit.end(),credit.begin() , neg );

    return max(credit,right);

}



vector<int> findLIS(vector<int>::itterator* begin,vector<int>::itterator* end)
{
    vector<int> remain(distance(begin,end)) ;
    vector<int> vect;
    for(auto it=begin;it!=end;it++)
    {
        if(vect.empty() || vect.back() < *it )
            vect.pushback(*it);

        *lower_bound(vect.begin(),vect.end(),*it)=*it;
        remain.push_back(vect.size());
    }

    return remain;

}

int neg(int i)
{
    return (-1) * i;
}


int max(vector<int> &left , vector<int> &right)
{
    int max = max(left.back(),right.back());

    for(int i=0 ; i<left.size();i++)
    {
        max = max(max,left[i]+right[right.size()-2-i]);
    }
    return max;
}