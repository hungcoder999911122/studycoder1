#pragma once
#include <string>
#include <vector>


using namespace std;

class determine {
private:
     // int countLeaf=0;
     // int countCenter=0;
public:
     string determineTopology(const vector<vector<int>>& A, int n );
     bool isRing(vector<int>&degree, int n) const;
     bool isStart(vector<int>&degree, int n);
     bool isMess(vector<int>&degree, int n) const;
};

