#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>

using namespace std;

#define KEY 1000000103;

int n, m, k, x;

struct Cell
{
    bool S = false, E = false;
    pair<int, int> s;
    vector<int64_t> cnt;

    Cell()
    {
        cnt.assign(k + 1, 0);
    }
};

void paths(int i, int j, vector<vector<Cell>> &grid)
{
    int lim = k + 1;
    if (!grid[i + 1][j].S)
    {
        for (int it = 0; it < lim; it++)
        {
            grid[i][j].cnt[it] += grid[i + 1][j].cnt[it];
        }
    }
    if (!grid[i][j + 1].S)
    {
        for (int it = 0; it < lim; it++)
        {
            grid[i][j].cnt[it] += grid[i][j + 1].cnt[it];
        }
    }
    if (grid[i][j].E)
    {
        for (int it = 1; it < lim; it++)
        {
            grid[i][j].cnt[it] += grid[grid[i][j].s.first][grid[i][j].s.second].cnt[it - 1];
        }
    }
    for (int it = 0; it < lim; it++)
    {
        grid[i][j].cnt[it]%=KEY;
       
    }
    
}
int64_t Radar(vector<vector<Cell>> &grid)
{
    grid[n - 1][m - 1].cnt[0] = 1;
    for (int j = m - 1; j >= 0; j--)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            paths(i, j, grid);
        }
    }
    int64_t res = 0;
    for (int i = 0; i < x + 1; i++)
    {
        res += grid[0][0].cnt[i];
    }
    return res % KEY;
}

vector<vector<Cell>> parse()
{

    cin >> n >> m >> k >> x;
    vector<vector<Cell>> grid(n + 1, vector<Cell>(m + 1));
    int s, e;
    for (int i = 0; i < k; i++)
    {
        cin >> s >> e;
        grid[s / m][s % m].S = true;
        grid[e / m][e % m].E = true;
        grid[e / m][e % m].s = make_pair(s / m, s % m);
    }
    return grid;
}

int main(int argc, char **argv)
{
    vector<vector<Cell>> grid = parse();
    cout << Radar(grid) << endl;
    return 0;
}