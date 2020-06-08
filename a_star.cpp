#include "a_star.hpp"
#define rep(i,s,e) for(ll i=s;i<e;i++)
#define ll long long

void a_star::begin()
{
    input();
}

void a_star::input()
{
    // cout<<"hello";
    cout<<"Enter number of Vertices"<<endl;
    cin>>n;
    G1=G=G_r=vector<vector<pair<ll,ll>> >(n+1);
    coord=vector<pair<ll,ll>>(n+1);
    cout<<"Enter number of edges"<<endl;
    cin>>m;

    cout<<"Enter Coordinates of vertices"<<endl;

    rep(i,1,n+1)
    {
        cin>>coord[i].first>>coord[i].second;
    }
    
    cout<<"Input edges "<<endl;
    rep(i,0,m)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        G1[u].push_back({v,w});
    }
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
        pre_process_graph(s,t);
        reverse_graph();
        // cout<<"hello"<<endl;
        perform_astar(s,t);
        G.clear();
        G_r.clear();
        G=G_r=vector<vector<pair<ll,ll>> >(n+1);
    }
}

void a_star::pre_process_graph(ll s, ll t)
{
    vector<ll>dist_s(n+1),dist_t(n+1);
    vector<ll>h(n+1);
    rep(i,1,n+1)
    {
        dist_s[i]=(ll)sqrt(((coord[i].first-coord[s].first)*(coord[i].first-coord[s].first))+((coord[i].second-coord[s].second)*(coord[i].second-coord[s].second)));
        dist_t[i]=(ll)sqrt(((coord[i].first-coord[t].first)*(coord[i].first-coord[t].first))+((coord[i].second-coord[t].second)*(coord[i].second-coord[t].second)));
    }
    rep(i,1,n+1)
    {
        h[i]=(dist_t[i]-dist_s[i])/2;
    }

    for(ll i=1;i<=n;i++)
    {
        for(auto it:G1[i])
        {
            ll u=i;
            ll v=it.first;
            ll w=it.second;
            ll w_2=(w+h[v]-h[u]);
            G[u].push_back({v,w_2});
        }
    }

}

void a_star::reverse_graph()
{
    rep(u,1,n+1)
    {
        for(auto it: G[u])
        {
            G_r[it.first].push_back({u,it.second});
        }
    }
}

void a_star::perform_astar(ll s , ll t)
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
        // cout<<"Distance = "<<ans.first<<endl;
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

void a_star::process(ll u,vector<vector<pair<ll,ll>>>&Gr,vector<ll>&dist,vector<ll>&prev,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&pq)
{
    for(auto it : Gr[u])
    {
        relax(u,it,dist,prev,pq);
    }
}

void a_star::relax(ll u, pair<ll,ll>it,vector<ll>&dist,vector<ll>&prev,priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll>>>&pq)
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

pair<ll,vector<ll>>a_star::ShortestPath(ll s,ll t,vector<ll>&dist,vector<ll>&prev,vector<ll>&dist_r,vector<ll>&prev_r,set<ll>&main_set)
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