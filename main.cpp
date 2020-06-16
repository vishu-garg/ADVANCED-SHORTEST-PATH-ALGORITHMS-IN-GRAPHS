#include<bits/stdc++.h>
#include "bidirectional_dijkstra.hpp"
#include "contraction_hierarchies.hpp"
#include "a_star.hpp"
using namespace std;

int main()
{
    // performing bi_directional_dijkstra's algortihm

    while(true)
    {

    cout<<"WHICH ALGORITHM TO PERFORM"<<endl;
    cout<<"1) Bi_Diectional dijkstra?"<<endl;
    cout<<"2) A* Algorithm + Bi Directional"<<endl;
    cout<<"3) Node Based Contraction Hirarachies"<<endl;
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

    if(ch==3){
    cout<<"///////////////////////////////"<<endl;
    cout<<"//  CONTRACTION HIERARCHIES  //"<<endl;
    cout<<"//////////////////////////////"<<endl<<endl;
    begin_contraction_hierarchies();
    }

    

    char choice='Y';
    cout<<"Do Again?(Y/N)";
    cin>>choice;
    if(choice!='y' || choice!='Y')
    break;
    }
    
}

