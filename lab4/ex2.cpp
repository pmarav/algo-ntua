#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Problem -> Galaxy with K planets,each planet is a binary tree,each node is a city,the binary trees is given
// as an parrent array.The root of each binary node is connected with
// the other binary trees in a circle so the first planet connects
// with the last one.Find biggest path that doesnt pass from the same town more than once.
// Solution -> Find the height of each binary tree and the length of the biggest path in a binary tree.
// the result is max[ height(i)+distance(i,j)+height(j) ] or the biggest path within a tree.


int maxChildPath = 0;
//Binary tree node
struct Node
{
    Node *left, *right;
    Node()
    {
        this->left = this->right = nullptr;
    }
};

//Takes a parent array and creates a binary tree from it using a dictionary
Node *createTree(int parent[], int n)
{
    unordered_map<int, Node*> map;
    for (int i = 1; i < n+2; i++)
        map[i] = new Node();

    Node *root = map[1];
    for (int i = 0; i < n; i++)
    {
        Node *ptr = map[parent[i]];
        if (ptr->left)
            ptr->right = map[i+2];
        else
            ptr->left = map[i+2];
    }
    return root;
}

//Calculates a binary tree's depth and the longest current tree path
int treeDepth(Node *node)
{
    if(node->right==nullptr && node->left == nullptr) return 0;
    else
    {
        int depthLeft=0,depthRight=0;
        if( node->left != nullptr )
            depthLeft = treeDepth(node->left) + 1;
        if( node->right != nullptr )
            depthRight = treeDepth(node->right) + 1;
        
        maxChildPath = max( depthRight+depthLeft , maxChildPath );
        return max(depthLeft,depthRight);
    }
}

//For each planet,read it's parent array and create a binary tree from it
Node** createPlanets(int K)
{
    Node **planets = (Node**) malloc(sizeof(Node*)*K);    
    for(int i=0;i<K;i++)
    {
        int countries;
        scanf("%d",&countries);
        if( countries == 1 )
        {
            planets[i] = new Node();
            int tmp;
            scanf("%d",&tmp);
        }
        else
        {
            int parentArray[countries-1];
            for(int j=0;j<countries-1;j++)
                scanf("%d",&parentArray[j]);
            planets[i] = createTree(parentArray,countries-1);
        }
    }
    return planets;
}

int freePlanets(Node **planets,int K)
{
    for(int i=0;i<K;i++)
        free(planets[i]);
    free(planets);
}

int main()
{
    int K;
    scanf("%d",&K);
    Node **planets = createPlanets(K);
    int planetHeight[K];

    for(int i=0;i<K;i++)
        planetHeight[i]=treeDepth(planets[i]);

    int maxPath=0;
    for(int i=0;i<K;i++)
        for(int j=i+1;j<K;j++)
            maxPath = max(maxPath ,  planetHeight[i] + max(j-i , K-j+i) + planetHeight[j]);


    cout << max(maxPath,maxChildPath) << endl;
    
    //freePlanets(planets,K);

    return 0;
}
