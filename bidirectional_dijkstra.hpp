#include<bits/stdc++.h>
using namespace std;
#define ll long long
class bi_dijkstra
{
    private:
    ll n,m,q,s,t;
    vector<vector<pair<ll,ll> > >G,G_r;
    public:
    void begin();
    void perform_bidijksta(ll,ll);
    void input();
    void reverse_graph();
    void process(ll,vector<vector<pair<ll,ll>>>&,vector<ll>&,vector<ll>&,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&);
    void relax(ll,pair<ll,ll>,vector<ll>&,vector<ll>&,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&);
    pair<ll,vector<ll> >ShortestPath(ll,ll,vector<ll>&,vector<ll>&,vector<ll>&,vector<ll>&,set<ll>&);
    void show_data(ll,vector<ll>);
};