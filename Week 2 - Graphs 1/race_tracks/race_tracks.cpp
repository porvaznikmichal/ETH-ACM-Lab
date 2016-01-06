#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <queue>
using namespace std;

typedef struct {
    int x;
    int y;
    int vx;
    int vy;
    int hops;
} node;

int main()
{

    int test; cin >> test;
    
    for (int N = 0; N < test; N++){
        int width, height; cin >> width >> height;
        
        node start, end;start.vx = 0; start.vy = 0;
        cin >> start.x >> start.y >> end.x >> end.y; start.hops = 0;
        
        
        int P; cin >> P;
        
        vector<vector<int> > obst;
        
        for (int i = 0; i < width; i++){
            vector<int> v;
            obst.push_back(v);
            for (int j = 0; j < height; j++){
                obst[i].push_back(0);
            }
        }
        
        for (int i = 0; i < P; i++){
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            
            for (int j = x1; j <= x2; j++){
                for (int k = y1; k <= y2; k++){
                    obst[j][k] = 1;
                }
            }
        }
        
        if (start.x == end.x && start.y == end.y){
            cout << "Optimal solution takes " << 0 << " hops." << endl;
            continue;
        }
        
        set< array<int, 4> > visited;
        visited.insert({start.x, start.y, 0, 0});
        
        bool found = 0;
        
        queue<node> q;
        q.push(start);
        
        while (!q.empty()){
            node vert = q.front();
            q.pop();
            
            for (int i = -1; i < 2; i++){
                if (vert.vx + i < -3 || vert.vx + i > 3){continue;}
                for (int j = -1; j < 2; j++){
                    if (vert.vy + j < -3 || vert.vy + j > 3){continue;}
                    pair<int,int> pos, vel;
                    vel = make_pair(vert.vx + i, vert.vy + j);
                    pos = make_pair(vert.x + vel.first, vert.y + vel.second);
                    
                    if (pos.first < 0 || pos.first >= width || pos.second < 0 || pos.second >= height){
                        continue;
                    }
                    else if (obst[pos.first][pos.second] == 1) {continue;}
                    else if (visited.count({pos.first, pos.second, vel.first, vel.second}) == 1) {continue;}
                    else if (pos.first == end.x && pos.second == end.y){
                        cout << "Optimal solution takes " << vert.hops + 1 << " hops." << endl;
                        found = 1;
                        break;
                    }
                    else {
                        visited.insert({pos.first, pos.second, vel.first, vel.second});
                        node nbr; nbr.x = pos.first; nbr.y = pos.second;
                        nbr.vx = vel.first; nbr.vy = vel.second; nbr.hops = vert.hops + 1;
                        q.push(nbr);
                    }
                }
                if (found == 1) {break;}
            }
            if (found == 1) {break;}
        }
        if (not found) {cout << "No solution." << endl;}
    }
    return 0;
}

