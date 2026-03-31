#include <iostream>
using namespace std;

int a[100],n;

void init ()
{
    cin >> n; //nhap n;
}

void output()
{
    for(int i=0;i<n;i++)
        cout << a[i];
    cout << endl;
}

void Try(int i)
{
    for(int v=0;v<=1;v++)
    {
        a[i]=v;
        if(i==n-1)   //
            output();
        else
            Try(i+1); //
    }
}

int main()
{
    init();  //
    Try(0);
}