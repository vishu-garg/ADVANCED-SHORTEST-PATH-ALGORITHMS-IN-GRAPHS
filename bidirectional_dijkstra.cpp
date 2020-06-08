#include "bidirectional_dijkstra.hpp"
#define rep(i,s,e) for(ll i=s;i<e;i++)
#define ll long long

void bi_dijkstra::begin()
{
    input();
}

void bi_dijkstra::input()
{
    // cout<<"hello";
    cout<<"Enter number of Vertices"<<endl;
    cin>>n;
    cout<<"Enter number of edges"<<endl;
    cin>>m;
    G=G_r=vector<vector<pair<ll,ll>> >(n+1);
    cout<<"Input edges "<<endl;
    rep(i,0,m)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        G[u].push_back({v,w});
    }
    reverse_graph();
    cout<<"Number of Queries? ";
    cin>>q;
    rep(i,0,q)
    {
        cout<<i+1<<") "<<endl; 
        cout<<"Source = ";
        ll s,t;
        cin>>s;
        cout<<"Destination= ";
        cin>>t;
        // cout<<"hello"<<endl;
        perform_bidijksta(s,t);
    }
}

void bi_dijkstra::reverse_graph()
{
    rep(u,1,n+1)
    {
        for(auto it: G[u])
        {
            G_r[it.first].push_back({u,it.second});
        }
    }
}

void bi_dijkstra::perform_bidijksta(ll s , ll t)
{
    vector<ll>dist(n+1,LLONG_MAX),dist_r(n+1,LLONG_MAX);
    vector<ll>prev(n+1,-1),prev_r(n+1,-1);
    dist[s]=0;dist_r[t]=0;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>pq,pq_r;
    pq.push({0,s});
    pq_r.push({0,t});
    dist[s]=0;
    dist_r[t]=0;
    set<ll> main_set;
    vector<ll>vis(n+1,0),vis_r(n+1,0);
    // cout<<"here"<<endl;
    do
    {
        ll v=(pq.top()).second;
        vis[v]++;
        pq.pop();
        process(v,G,dist,prev,pq);
        if(vis_r[v])break;
        main_set.insert(v);

        v=(pq_r.top()).second;
        vis_r[v]++;
        pq_r.pop();
        process(v,G_r,dist_r,prev_r,pq_r);
        if(vis[v])break;
        main_set.insert(v);
    }
    while(!pq.empty() && !pq_r.empty());
    // cout<<"here"<<endl;
    auto ans=ShortestPath(s,t,dist,prev,dist_r,prev_r,main_set);
    if(ans.first==-1)
    {
        cout<<"No path Exist!"<<endl;
        return;
    }
    else 
    {
        cout<<"Path Exists :"<<endl;
        cout<<"Distance = "<<ans.first<<endl;
        cout<<"Route = ";
        for(ll i=0;i<ans.second.size()-1;i++)
        {
            cout<<ans.second[i]<<"--->";
        }
        cout<<ans.second.back()<<endl;
        return;
    }
    // cout<<"hello";
}

void bi_dijkstra::process(ll u,vector<vector<pair<ll,ll>>>&Gr,vector<ll>&dist,vector<ll>&prev,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&pq)
{
    for(auto it : Gr[u])
    {
        relax(u,it,dist,prev,pq);
    }
}

void bi_dijkstra::relax(ll u, pair<ll,ll>it,vector<ll>&dist,vector<ll>&prev,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&pq)
{
    ll v=it.first;
    ll w=it.second;
    if(dist[v]>dist[u]+w)
    {
        dist[v]=dist[u]+w;
        pq.push({dist[v],v});
        prev[v]=u;
    }
}

pair<ll,vector<ll>>bi_dijkstra::ShortestPath(ll s,ll t,vector<ll>&dist,vector<ll>&prev,vector<ll>&dist_r,vector<ll>&prev_r,set<ll>&main_set)
{
    ll result=LLONG_MAX;
    ll u_best=-1;
    for(auto u:main_set)
    {
        if(dist[u]==LLONG_MAX|| dist_r[u]==LLONG_MAX)
        continue;
        if(dist[u]+dist_r[u]<result)
        {
            u_best=u;
            result=dist[u]+dist_r[u];
        }
    }
    if(result==LLONG_MAX)
    {
        vector<ll>v;
        return (make_pair(-1,v));
    }
    else 
    {
        vector<ll>path;
        ll last=u_best;
        while(last!=s)
        {
            path.push_back(last);
            last=prev[last];
        }
        path.push_back(s);
        reverse(path.begin(),path.end());
        last=u_best;
        while(last!=t)
        {
            last=prev_r[last];
            path.push_back(last);
        }
        return(make_pair(result,path));
    }
}