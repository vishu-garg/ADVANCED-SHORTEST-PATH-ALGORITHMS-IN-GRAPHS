#include<bits/stdc++.h>
using namespace std;
#define ll long long
class a_star
{
    private:
    ll n,m,q,s,t;
    vector<vector<pair<ll,ll> > >G1,G,G_r;
    vector<pair<ll,ll> >coord;
    public:
    void begin();
    void perform_astar();
    int calc_h(ll v);
    void input();
    void reverse_graph();
    void process(ll,vector<vector<pair<ll,ll>>>&,vector<ll>&,vector<ll>&,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&);
    void relax(ll,pair<ll,ll>,vector<ll>&,vector<ll>&,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&);
    pair<ll,vector<ll> >ShortestPath(ll,ll,vector<ll>&,vector<ll>&,vector<ll>&,vector<ll>&,set<ll>&);
    void show_data(ll,vector<ll>);
};