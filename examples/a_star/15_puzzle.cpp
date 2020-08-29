/*


In this code I have used a_star search with manhattan heuristic 
to find the most optimal way to solve a 15 puzzle board.


*/

#include<bits/stdc++.h>
#include<conio.h>
#include<chrono>
using namespace std;
using namespace std::chrono;
const int N=4;

struct node
{   
    vector<vector<int>>grid;
    int g,h;
    char move; // type of move to rach this state  // -1=up, +1 down ,-2 left, +2 right, 0 initial
    int b_i,b_j;  // position of blank tile
    node *par;
    
    node(){
        move='N';
        g=0;
        h=0;
        grid=vector<vector<int>>(N,vector<int>(N));
        par=NULL;
    }
};


vector<vector<int>>board(N,vector<int>(N));
vector<vector<int>>final_board(N,vector<int>(N));
int n_i,n_j;
bool ok=true;

void generate_board()
{
    vector<int>arr(15);
    cout<<"Mode"<<endl;
    cout<<"1)Manual "<<endl<<"2)Automatic"<<endl;
    char ch;
    cin>>ch;
    if(ch=='1')
    {
        cout<<"Blank Position: ";
        cin>>n_i>>n_j;
        cout<<"Enter Board"<<endl;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(i==n_i && j==n_j)continue;
                cout<<i<<","<<j<<" - ";
                cin>>board[i][j];
            }
        }
        cout<<endl<<"=========================================="<<endl;
        cout<<endl<<"INITIAL BOARD : "<<endl<<endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(i==n_i && j==n_j)
                cout<<"_    ";
                else 
                {
                    cout<<board[i][j]<<"   ";
                }
                
            }
            cout<<endl<<endl;
        }
        cout<<"=========================================="<<endl;
        board[n_i][n_j]=0;
    }
    else 
    {
        cout<<"=========================================="<<endl;
        cout<<"Note that most of the boards ar INSOLVABLE."<<endl<<"So random board may not be solvable generally!"<<endl;
        cout<<"=========================================="<<endl;
        cout<<"Suggested to try Manual Boards."<<endl;
        cout<<"=========================================="<<endl;
        cout<<"INITIAL BOARD : "<<endl<<endl;
        for(int i=1;i<16;i++)
        arr[i-1]=i;

        srand(time(0));

        random_shuffle(arr.begin(),arr.end());   // generating random permutation of 15 numbers;

        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(i==3 && j==3)
                cout<<"_";
                else 
                {
                    board[i][j]=arr[i*4+j];
                    cout<<board[i][j]<<"   ";
                }

                
            }
            cout<<endl<<endl;
        }
        cout<<endl<<"=========================================="<<endl;
        board[3][3]=0;
    }

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            final_board[i][j]=(i*4)+(j+1);
        }
    }
    final_board[3][3]=0;


    int inv_count = 0; 
    for (int i = 0; i < N * N - 1; i++) 
    { 
        for (int j = i + 1; j < N * N; j++) 
        { 
            // count pairs(i, j) such that i appears 
            // before j, but i > j. 
            if (arr[j] && arr[i] && arr[i] > arr[j]) 
                inv_count++; 
        } 
    } 

    if(inv_count%2!=0)
    ok=false;


    if(!ok)
    {
        cout<<"Grid is not solvable."<<endl;
        getch();
        return;
    }

}


bool check_final(vector<vector<int>>&grid)
{

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(grid[i][j]!=final_board[i][j])
            return false;
        }
    }
    return true;

}



int calc_heuristic(vector<vector<int>>&grid)
{
    int h=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            int val=grid[i][j];
            if(val==0)continue;
            int c_i=val/N,c_j=(val%N)-1;
            if(c_j<0)
            c_j+=4;
            h+=abs(c_i-i)+abs(c_j-j);
        }
    }
    return h;
}

void find_optimal_moves()
{
    node *ini=new node();
    ini->b_i=n_i;
    ini->b_j=n_j;
    ini->grid=board;
    ini->h=calc_heuristic(ini->grid);
    priority_queue<pair<int,node*>,vector<pair<int,node*>>,greater<pair<int,node*>>>pq;

    pq.push({0,ini});
    map<node*,int>vis;
    map<vector<vector<int>>,node*>mp;
    mp[ini->grid]=ini;

    node *ans=NULL;
    auto start = high_resolution_clock::now();
    while(!pq.empty())
    {

        auto cur_time = high_resolution_clock::now();
        auto duration_count=duration_cast<microseconds>(cur_time - start);
        if(duration_count.count()>5000000)
        {
            break;
        }
        
        auto cur_state=pq.top();
        pq.pop();
        node*cur_node=cur_state.second;
        if(vis.find(cur_node)!=vis.end())
            continue;
        vis[cur_node]=1;
        int g=cur_node->g;

        if(check_final(cur_node->grid))
        {
            ans=cur_node;
            break;
        }

        int i=cur_node->b_i,j=cur_node->b_j;


        vector<pair<pair<int,int>,char>>moves;
        moves.push_back(make_pair(make_pair(-1,0),'U'));
        moves.push_back(make_pair(make_pair(1,0),'D'));
        moves.push_back(make_pair(make_pair(0,-1),'L'));
        moves.push_back(make_pair(make_pair(0,1),'R'));

        for(auto it:moves)
        {
            int i2=i+it.first.first;
            int j2=j+it.first.second;
            char mve=it.second;
            if(i2>=N || j2>=N || i2<0 || j2<0)continue;

            vector<vector<int>>new_grid=cur_node->grid;
            swap(new_grid[i2][j2],new_grid[i][j]);

            node *new_node=new node();
            if(mp.find(new_grid)!=mp.end())
            {
                
                new_node=mp[new_grid];
                if(vis.find(new_node)!=vis.end())continue;
                else 
                {
                    int old_cst=new_node->g+new_node->h;
                    int new_cst=cur_node->g+1+new_node->h;
                    if(old_cst>new_cst)
                    {
                        new_node->g=cur_node->g+1;
                        new_node->par=cur_node;
                        new_node->move=mve;
                        pq.push({new_node->g+new_node->h,new_node});
                    }
                }
            }
            else 
            {
                new_node->g=cur_node->g+1;
                new_node->h=calc_heuristic(new_grid);
                mp[new_grid]=new_node;
                new_node->move=mve;
                new_node->par=cur_node;
                new_node->b_i=i2;
                new_node->b_j=j2;
                new_node->grid=new_grid;
                pq.push({new_node->g+new_node->h,new_node});
            } 
        }
    }
    
    if(!ans)
    {
        auto cur_time = high_resolution_clock::now();
        auto duration_count=duration_cast<microseconds>(cur_time - start);
        // if(duration_count>std::chrono::microseconds(5000))
        // {
        //     break;
        // }
        cout<<"Time Taken -> "<<duration_count.count()/(1e6)<<" seconds."<<endl; 
        cout<<"Grid is not solvable."<<endl;
        getch();    
        return;
    }

    vector<char>ans_set;

    while(ans->par!=NULL)
    {
        ans_set.push_back(ans->move);
        ans=ans->par;
    }
    reverse(ans_set.begin(),ans_set.end());
    auto cur_time = high_resolution_clock::now();
    auto duration_count=duration_cast<microseconds>(cur_time - start);
    // if(duration_count>std::chrono::microseconds(5000))
    // {
    //     break;
    // }
    cout<<"Time Taken -> "<<fixed<<setprecision(8)<<(double)(duration_count.count())/(1e6)<<" seconds."<<endl; 
    cout<<"Found solution in "<<ans_set.size()<<" moves:"<<endl;
    cout<<"Moves :"<<endl;
    for(int i=0;i<ans_set.size();i++)
    {
        cout<<ans_set[i];
    }
    cout<<endl;
    getch();
    return;

}


int main()
{
    generate_board();
    if(ok)
    find_optimal_moves();

}





