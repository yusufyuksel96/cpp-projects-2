#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;


vector<vector<int>> height;
vector<vector<int>> disttomain;
vector<vector<int>> visited;

struct CompareDistance{
    bool operator() (pair<pair<int,int>,int> a ,pair<pair<int,int>,int> b ) {
        return a.second > b.second ;

    }

};


priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,CompareDistance> pq;


int main(int argc, char * argv[]) {


    ifstream infile(argv[1]);
    if(!infile.is_open()){
        cout << "input problem";
        return 0;
    }
    int N,M;
    infile >> N >> M;


    height.resize(N);
    visited.resize(N);
    disttomain.resize(N);
    int h;


    for(int i=0;i<N;i++){

        height[i].resize(M);
        visited[i].resize(M,0);
        disttomain[i].resize(M,-1);

        for(int j=0;j<M;j++){
            infile >> h;

            height[i][j]=h;

        }

    }

    int blank;
    infile >> blank;
    int x1,y1,x2,y2;
    infile >>x1 >> y1 >> x2 >>y2;

    x1=x1-1;
    y1=y1-1;
    x2=x2-1;
    y2=y2-1;
    disttomain[x1][y1]=0;

    pair<int, int> c = make_pair(x1,y1);
    pair<pair<int, int>, int> cc = make_pair(c, disttomain[x1][y1]);
    pq.push(cc);

    ofstream output;
    output.open(argv[2]);


    while(!pq.empty()){

        pair<int, int> curr=pq.top().first;
        pq.pop();
        int x=curr.first;
        int y=curr.second;

        if(x==x2 && y==y2){
            output << disttomain[x][y];

            break;
        }

        if(visited[x][y]==0){
            visited[x][y]=1;

            vector<pair<int,int>> neigh;
            if(x+1<=M-1 && visited[x+1][y]==0){

                pair<int, int> k = make_pair(x+1,y);

                neigh.push_back(k);

            }
            if(x-1>=0 && visited[x-1][y]==0){
                pair<int, int> l = make_pair(x-1,y);
                neigh.push_back(l);

            }
            if(y+1<=N-1 && visited[x][y+1]==0){

                pair<int, int> m = make_pair(x,y+1);
                neigh.push_back(m);

            }
            if(y-1>=0 && visited[x][y-1]==0){
                pair<int, int> n = make_pair(x,y-1);
                neigh.push_back(n);

            }
            for(int z=0;z<neigh.size();z++){
                int x0=neigh[z].first;
                int y0=neigh[z].second;

                if(disttomain[x0][y0]==-1){

                    disttomain[x0][y0]=max(abs(height[x][y]-height[x0][y0]),disttomain[x][y]);

                }else{

                    disttomain[x0][y0]=min(disttomain[x0][y0],max(abs(height[x][y]-height[x0][y0]),disttomain[x][y]));
                }
                pair<int, int> t = make_pair(x0,y0);
                pair<pair<int, int>, int> tt = make_pair(t, disttomain[x0][y0]);
                pq.push(tt);

            }

        }

    }
    output.close();

    return 0;
}