#include <iostream>

using namespace std;

int a[10],n, W,maxV;
int v[10],w[10];
int result[10];
void init ()
{
    maxV=0;
    cout<<"Nhap so luong do vat:";
    cin >> n; //nhap n;
    cout<<"Nhap trong luong toi da:";
    cin>>W;
}

void output()
{
    for(int i=0;i<n;i++)
        cout << a[i];
    cout << endl;
}
void input(){
     for(int i=0;i<n;i++){
         cout <<"v["<<i<<"]=";
         cin>>v[i];
         cout <<"w["<<i<<"]=";
         cin>>w[i];
         cout << endl;

     }

}
int SumV(){
    int s=0;
     for(int i=0;i<n;i++)
       if(a[i]==1)
         s+=v[i];
    return s;
}
int SumW(){
    int s=0;
     for(int i=0;i<n;i++)
        if(a[i]==1)
         s+=w[i];
    return s;
}
void CopyArray(int b[]){

    for(int i=0;i<n;i++)
        b[i]=a[i];

}
void Try(int i)
{
    int sw=0;
    for(int v=0;v<=1;v++)
    {
        a[i]=v;
        for(int k=0;k<=i;k++)
              sw+=w[k];
       // if(sw<W)
        if(i==n-1){
            if(SumW()<=W&&SumV()>maxV){

            CopyArray(result);
            maxV=SumV();
           //continue
            }
        }

        else
            Try(i+1); //
    }
}
void GreadyAlgorithm(){

}
void PrintResult(){

   for(int i=0;i<n;i++)
   {
     if(result[i]==1)
    cout<<"Do vat:"<<i+1<<"\n";}
   cout<<"Gia tri cac do vat dc chon: "<<maxV;
}
int main()
{
    init();  //
    input();
    Try(0);
    PrintResult();
}