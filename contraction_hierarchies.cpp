#include<bits/stdc++.h>
#include "contraction_hierarchies.hpp"
#include<algorithm>
using namespace std;
 
#define ll long long
#define ld long double
 
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define repb(i,a,b) for(ll i=a;i>=b;i--)
 
#define err() cout<<"=================================="<<endl;
#define errA(A) for(auto i:A)   cout<<i<<" ";cout<<endl;
#define err1(a) cout<<#a<<" "<<a<<endl
#define err2(a,b) cout<<#a<<" "<<a<<" "<<#b<<" "<<b<<endl
#define err3(a,b,c) cout<<#a<<" "<<a<<" "<<#b<<" "<<b<<" "<<#c<<" "<<c<<endl
#define err4(a,b,c,d) cout<<#a<<" "<<a<<" "<<#b<<" "<<b<<" "<<#c<<" "<<c<<" "<<#d<<" "<<d<<endl
 
#define pb push_back
#define all(A)  A.begin(),A.end()
#define allr(A)    A.rbegin(),A.rend()
#define ft first
#define sd second
 
#define pll pair<ll,ll>
#define V vector<ll>
#define S set<ll>
#define VV vector<V>
#define Vpll vector<pll>
 
#define endl "\n"
 
const ll logN = 20;
const ll N=500010;
const ll M = 1000000007;
const ll INF = 1e12;
#define PI 3.14159265
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
int pow1(int a,int b){
    int res=1;
    while(b>0){
        if(b&1){
        	res=res*a;
		}
        a=a*a;
        b>>=1;
    }
    return res;
}

// struct segtree{
//     ll x,y;
//     ll tree[4*N];

//     void build_tree(vector<ll>&v , ll ind,ll l, ll r)
//     {
//         if(l==r)
//         {
//             tree[ind]=v[l];
//             return;
//         }
//         ll mid=(l+r)/2;
//         build_tree(v,2*ind,l,mid);
//         build_tree(v,2*ind+1,mid+1,r);
//         tree[ind]=max(tree[2*ind],tree[2*ind+1]);
//     }

//     ll query(ll ind, ll l, ll r)
//     {
//         // cout<<l<<" "<<r<<" "<<endl;
//         if(x>r || y<l)return -LLONG_MAX;
//         if(l>=x && r<=y)return tree[ind];
//         ll mid=(l+r)/2;
//         return max(query(2*ind,l,mid),query(2*ind+1,mid+1,r));
//     }
// }obj;
ll n,m,s,t;
bool contrcated[N];
ll delNeighbors[N],orderPos[N],d_dist[N],hops[N];
vector<pair<ll,ll>>adj[N],adj_r[N];
priority_queue<pll,vector<pll>,greater<pll>>d_pq,imp_pq;

void dijkstra(ll src, ll Max)
{
    memset(d_dist,-1,sizeof(d_dist));
    memset(hops,0,sizeof(hops));
    d_dist[src]=0;
    while(!d_pq.empty())d_pq.pop();
    d_pq.push(make_pair(0,src));
    ll u,w;
    while(!d_pq.empty())
    {
        u=d_pq.top().second;
        w=d_pq.top().first;
        d_pq.pop();
        if(w>d_dist[u])continue;
        if(hops[u]>3)continue;
        if(d_dist[u]>Max)return;
        for(auto it:adj[u])
        {
            if(contrcated[it.first])continue;
            if((d_dist[it.first]>d_dist[u]+it.second)|| d_dist[it.first]==-1){
                d_dist[it.first]=d_dist[u]+it.second;
                hops[it.first]=hops[u]+1;
                d_pq.push(make_pair(d_dist[it.first],it.first));
            }
        }
    }
}

void contractNode(ll u)
{
    contrcated[u]=1;
    for(auto it:adj[u])
    delNeighbors[it.first]++;
    for(auto it:adj_r[u])
    delNeighbors[it.second]++;
    ll in_max=0,out_max=0;
    for(auto it:adj[u])
    out_max=max(out_max,it.second);
    for(auto it:adj_r[u])
    in_max=max(in_max,it.second);
    ll Max=in_max+out_max;
    ll totcost;
    for(auto it:adj_r[u])
    {
        if(contrcated[it.first])continue;
        dijkstra(it.first,Max);
        for(auto it2:adj[u])
        {
            if(contrcated[it2.first])continue;
            totcost=it.second+it2.second;
            if(d_dist[it2.first]>totcost || d_dist[it2.first]==-1)
            adj[it.first].pb(make_pair(it2.first,totcost));
            adj_r[it2.first].pb(make_pair(it.first,totcost));
        } 
    }
}

ll bidijkstra_algo(){
    priority_queue<pll,vector<pll>,greater<pll>>pq,pq_r;
    V dist(n+1,INF),dist_r(n+1,INF);
    ll estimate=INF;
    dist[s]=0;dist_r[t]=0;
    pq.push(make_pair(0,s));
    pq_r.push(make_pair(0,t));
    ll u,w;
    while(!pq.empty() || !pq_r.empty())
    {
        if(!pq.empty()){
            u=pq.top().second;w=pq.top().first;pq.pop();
            if(w>dist[u])continue;
            if(dist[u]<=estimate){
                for(auto it:adj[u])
                {
                    if((dist[it.first]>dist[u]+it.second) && (orderPos[it.first]>orderPos[u]))
                    {
                        dist[it.first]=dist[u]+it.second;pq.push(make_pair(dist[it.first],it.first));
                    }
                }
                estimate=min(estimate,dist[u]+dist_r[u]);
            }
        }
        if(!pq_r.empty())
        {
            u=pq_r.top().second;w=pq_r.top().first;pq_r.pop();
            if(w>dist_r[u])continue;
            if(dist_r[u]<=estimate)
            {
                for(auto it:adj_r[u])
                {
                    if((dist_r[it.first]>dist_r[u]+it.second)&&(orderPos[it.first]>orderPos[u])){
                        dist_r[it.first]=dist_r[u]+it.second;pq_r.push(make_pair(dist_r[it.first],it.first));
                    }
                }
            }
            estimate=min(estimate,dist[u]+dist_r[u]);
        }
    }
    return estimate;
}

ll recompute(ll i){
    return (14*((adj[i].size()*adj_r[i].size())-adj[i].size()-adj_r[i].size()) + 25*(adj[i].size()+adj_r[i].size()) + 10*delNeighbors[i]);
}

void preprocess()
{
    ll imp;
    rep(i,1,n+1)
    {
        imp=14*((adj[i].size()*adj_r[i].size())-adj[i].size()-adj_r[i].size());
        imp_pq.push({imp,i});
    }
    ll u,u_imp,t_imp,cnt=0;
    while(!imp_pq.empty())
    {
        u_imp=imp_pq.top().first;
        u=imp_pq.top().second;
        imp_pq.pop();
        t_imp=recompute(u);
        if(imp_pq.size()!=0 && t_imp>imp_pq.top().first){
            imp_pq.push({t_imp,u});continue;
        }
        orderPos[u]=cnt;
        contractNode(u);
        cnt++;
    }
}

void init_graph()
{
    ll a,b,w;
    cout<<"Enter Edges..."<<endl;
    rep(i,0,m)
    {
        cin>>a>>b>>w;
        adj[a].pb(make_pair(b,w));
        adj_r[b].pb(make_pair(a,w));
    }
    preprocess();
}

void begin_contraction_hierarchies()
{
    // fast;
    
    cout<<"No of Nodes (n) and Edges(m) ?"<<endl;
    cin>>n>>m;
    init_graph();
    cout<<"Begin: "<<endl<<endl;
    cout<<"No of Queries?"<<endl;
    ll q;
    cin>>q;

    rep(i,0,q)
    {
        cout<<"Enter Source(s) and Destination(t)- ";
        cin>>s>>t;
        if(s==t)
        {
            cout<<"0"<<endl;continue;
        }
        ll ans=bidijkstra_algo();
        if(ans<INF)cout<<ans<<endl;
        else cout<<"No path Exist"<<endl;
    }
}
