#include <iostream>
#include <vector>
#include <string>
using namespace std;



string determineTopology(const  vector<vector<int>>& A, int n ){


    vector<int> degree(n,0);

    for(int i = 0; i<n; ++i){

        for(int j= 0; j<n; ++j){

            if (A[i][j]){

                degree[i]++;
            }
        }
    }
    // Tinh bac(degree) cua moi dinh

    bool isMess = true;

    for (int i = 0; i<n; ++i){

        if(degree[i] != n-1){
            isMess= false;
            break;
        }
    }
    if(isMess) return "Fully connected mess!!!";
    // TH: 1

    bool isRing = true;

    for (int i=0; i<n; ++i){
        
        if(degree[i]!=2){

            isRing= false;
            break;
        }
    }
    if(isRing) return "Ring!!!";
    //TH: 2

    
    int countCenter= 0;
    int countLeaf= 0;

    for (int i=0; i<n;++i){
        
        if(degree[i]==1 ) countLeaf++;
        else if(degree[i]==n-1) countCenter++;

        if (countCenter == 1 && countLeaf == n-1 ){
           return "Start!!!";
        }
        //TH: 3

    }
    return "None of these!!!";
}

int main (){
    int n;
    // determine d;
    cout<<"Nhap so luong nut: ";
    cin>>n;

    if (n<=3){
        cout<<"Nhap n > 3!!!"<<endl;
        return 0;
    }
    
    vector<vector<int>> A(n, vector<int>(n));
    // Tao ma tran ke nxn

    cout<<"Nhap ma tran ke(Nhap 0 hoac 1)"<<endl;
    
    for (int i=0; i<n; i++){
        cout<<"Hang "<<i<<": ";
        for (int j=0; j<n; j++){
            cin>> A[i][j];
        }
    }

    cout << "\nKet qua: " << determineTopology(A, n) << endl;
    

    return 0;
}
