#include<bits/stdc++.h>
#include "bidirectional_dijkstra.hpp"
#include "a_star.hpp"
using namespace std;

int main()
{
    // performing bi_directional_dijkstra's algortihm

    while(true)
    {

    cout<<"WHICH ALGORITHM TO PERFORM"<<endl;
    cout<<"1) Bi_Diectional dijkstra?"<<endl;
    cout<<"2) Bi_Directional A* Algorithm"<<endl;
    ll ch;
    cin>>ch;
    if(ch==1){
    cout<<"///////////////////////////////"<<endl;
    cout<<"//  BIDIRECTIONAL_DIJKSTRA  //"<<endl;
    cout<<"//////////////////////////////"<<endl<<endl;
    bi_dijkstra obj;
    obj.begin();}

    if(ch==2){
    cout<<"///////////////////////////////"<<endl;
    cout<<"//      A_STAR SEARCH       //"<<endl;
    cout<<"//////////////////////////////"<<endl<<endl;
    a_star obj;
    obj.begin();}


    char choice='Y';
    cout<<"Do Again?(Y/N)";
    cin>>choice;
    if(choice!='y' || choice!='Y')
    break;
    }
    
}

