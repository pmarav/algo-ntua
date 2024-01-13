#include <iostream>
#include <algorithm>
#include <queue> 
#include <utility>
#include <vector>
using namespace std;

int MAX = 2147483647;
typedef pair<int, int> pairs; 
int N,M,K,L,B;

// Problem -> race car has to pass through towns T and only through them,it has to charge L times,charging person can bring fuel from
// charging town C to racing town T.Given a undirected graph with weights,towns T and charging towns C.Find the fastest time that the
// racer can achieve while charging L times.
// Solution -> Add a node and connect it with all the charging stations with edges of weight 0.
// By applying dijkstras SPT algorithm with the added node as the starting node we will find the closest charging station to each racing town
// afterwards we will sort the racing towns to find the ones that are closest to a charging station and pick L of them.
// The fastest time will be the time it needs to go from T0->Tk plus the time it will wait at each town to charge.

void dijkstra(vector<vector<int>> roads , int *distance )
{
    for(int i=0;i<N+1;i++)
        distance[i]=MAX;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,0});
    while( !pq.empty() )
    {
        pair<int,int> p = pq.top();
        pq.pop();
        int currentNode = p.second;
        int d = p.first;
        if(d>distance[currentNode])
            continue;
        for(int i=1;i<N+1;i++)
        {
            if(i==currentNode || roads[currentNode][i]==MAX)
                continue;
            if( d + roads[currentNode][i ]< distance[i] )
            {
                distance[i] = d + roads[currentNode][i];
                pq.push({distance[i] , i});
            }
        }
    }
}

//Gets edges from the standard input, towns that the race passes through and the the charging stations.Graph has 1 extra node that connects
//to all the charging stations with 0 weight edges
//By using dijkstra's SPT algorithm on this we will find the smallest path to a charging station from every town that the race passes through
vector<vector<int>> getEdges( int T[])
{
    vector<vector<int>> roads(N+1,vector<int>(N+1)); 
    for(int i=0;i<N+1;i++)
        for(int j=0;j<N+1;j++)
            roads[i][j]=MAX;

    for(int i=0;i<M;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        scanf("%d",&roads[u][v]);
        roads[v][u] = roads[u][v];

    }
    for(int i=0;i<K;i++)
        scanf("%d",&T[i]);
    for(int i=0;i<B;i++)
    {
        int c;
        scanf("%d" , &c);
        roads[0][c] = 0;
        roads[c][0] = 0;
    }

    return roads;
}

//Find the minimum time that anakin need to finish the race while charging L times
int findMinimumTime(vector<vector<int>> roads , int distance[] , int T[])
{
    int closestChargingStation[K-2];

    for(int i=0;i<K-2;i++)
        closestChargingStation[i] = distance[T[i+1]];

    sort(closestChargingStation,closestChargingStation+K-2);

    int totalTime = 0;
    for(int i=0;i<K-1;i++)
        totalTime += roads[T[i]][T[i+1]];

    for(int i=0;i<L;i++)
        totalTime += closestChargingStation[i];

    return totalTime;
}

int main()
{
    scanf("%d %d %d %d %d",&N,&M,&K,&L,&B);
    int T[K];
    int distance[N+1];

    vector<vector<int>> roads = getEdges(T);

    dijkstra(roads,distance);

    cout << findMinimumTime(roads,distance,T) << endl;

}




