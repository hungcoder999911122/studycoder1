#include "determine.h"

string determine::determineTopology(const vector<vector<int>> &A, int n)
{
    vector<int> degree(n,0);

    for(int i=0; i<n; ++i){

        for(int j=0; j<n; ++j){

            if (A[i][j]){

                degree[i]++;
            }
        }
    }
    if(isRing(degree,n)) return "Ring!!!";
    if(isStart(degree, n)) return "Start!!!";
    if(isMess(degree, n)) return "Fully connected mess!!!";
    return "None of these!!!";
}

bool determine::isRing(vector<int>& degree, int n) const
{
    bool isRing = true;

    for (int i = 0; i < n; ++i){
        
        if(degree[i]!=2){

            isRing= false;
            break;
        }
    }
    return isRing;
}


bool determine::isStart(vector<int>& degree, int n) 
{
    int countLeaf=0;
    int countCenter=0;

    bool isStart= false;
    for(int i = 0; i < n; ++i){
        if(degree[i] == 1) countLeaf++;
        if(degree[i] == n-1) countCenter++;
    }
    if(countLeaf == n-1 && countCenter == 1) isStart = true;
    return isStart;
}


bool determine::isMess(vector<int>& degree, int n) const
{
    bool isMess= true;
    for (int i = 0; i < n; ++i){
        if (degree[i] != n-1) isMess= false;
    }
    return isMess;
}
