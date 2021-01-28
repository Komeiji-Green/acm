#include<iostream>
#include<set>
#include<string>
#include<queue>
#include<map>
#include<cstring>
using namespace std;

map<string, int> dir;

bool vis[100][100][4];
int block[100][100];

int m, n;

int vec[4][2] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };
struct state {
    state() {}
    state(int _d, int _i, int _j, int _t): d(_d), i(_i), j(_j), time(_t) {}
    int d;
    int i;
    int j;
    int time;
    state move(int op, int type) {
        state nex = *this;
        if(type == 0) { // 移动
            for(int dd = 1; dd <= op; dd++) {
                nex.i += vec[d][0];
                nex.j += vec[d][1];
                if(!nex.in()) {
                    nex.i = i;
                    nex.j = j;
                    break;
                }
            }
        } else {
            nex.d += op;    // 1 左旋 -1 右旋
            nex.d %= 4;
            if(nex.d < 0) nex.d += 4;
        }
        nex.time++;
        return nex;
    }
    bool in() {
        return (i > 0 && i < m && j > 0 && j < n) && (!block[i][j]);
    }
};

int x, y, xx, yy;
int d;

int bfs()
{
    queue<state> q;
    state u(d, x, y, 0);
    q.push(u);
    state cur, nex;
    while(!q.empty()) {
        cur = q.front(); q.pop();
        if(cur.in() && cur.i == xx && cur.j == yy) return cur.time;
        if(vis[cur.i][cur.j][cur.d]) continue;
        vis[cur.i][cur.j][cur.d] = true;
        for(int i = 1; i <= 3; i++) {
            nex = cur.move(i, 0);
            if(nex.in())
                q.push(nex);
        }
        nex = cur.move(1, 1);
        if(nex.in()) q.push(nex);
        nex = cur.move(-1, 1);
        if(nex.in()) q.push(nex);
    }
    return -1;
}

void init()
{
    memset(vis, 0, sizeof(vis));
    memset(block, 0, sizeof(block));
}
int main()
{
    dir["east"] = 0;
    dir["north"] = 1;
    dir["west"] = 2;
    dir["south"] = 3;

    while(cin >> m >> n && m != 0 || n != 0) {
        init();
        int item;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                cin >> item;
                if(item == 1) {
                    block[i][j] = block[i + 1][j] = block[i][j + 1] = block[i + 1][j + 1] = 1;
                }
            }
        }

        cin >> x >> y >> xx >> yy;
        string dstr;
        cin >> dstr;
        d = dir[dstr];

        cout << bfs() << endl;
    }
}