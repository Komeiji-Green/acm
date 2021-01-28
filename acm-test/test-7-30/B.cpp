#include<iostream>
#include<map>
#include<algorithm>
#include<string>
using namespace std;

typedef long long ll;

int daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

bool leap(int year) {
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

map<string, int> month = { 
    {"Jan", 1 }, { "Feb", 2 }, { "Mar", 3 }, { "Apr", 4 }, { "May", 5 }, { "Jun", 6 },
    {"Jul", 7 }, { "Aug", 8 }, { "Sep", 9 }, { "Oct", 10 }, { "Nov", 11 }, { "Dec", 12 } 
};

int Time(string mon, int date, int year, int hour) {
    int day = 0;
    int hours = 0;
    for(int i = 2000; i < year; i++) {
        bool lp = leap(i);
        day += (lp ? 366 : 365);
    }
    int m = month[mon];
    for(int i = 1; i < m; i++) {
        day += daytab[leap(year)][i];
    }
    day += date - 1;
    return hours = day * 24 + hour;
}

const int maxn = 100000 + 5;
const int maxN = 3000;


struct Order {
    Order() {}
    Order(int _time, int _value): time(_time), value(_value) {}
    int time;
    int value;
};
Order order[maxN];

int N, M, T, S, H;
ll R;

struct Cost {
    Cost() {}
    Cost(int _cost, int _time): time(_time), cost(_cost) {}
    int time;
    int cost;
};

struct cmp {
    bool operator() (const Cost& lhs, const Cost& rhs) {
        return lhs.cost < rhs.cost;
    }
};

int price[maxn];
ll std_cost[maxn];
Cost qcost[maxn + 100];

int head = 0;
int tail = 0;

void add(ll cost, int time) {
    Cost u(cost, time);
    int idx = upper_bound(qcost + head, qcost + tail, u, cmp()) - qcost;
    tail = idx;
    qcost[tail++] = u;
    if(time - qcost[head].time >= T)
        head++;
    std_cost[time] = qcost[head].cost;
    // cout << "test = " << std_cost[time] << endl;
}


void init() {
    head = 0;
    tail = 0;
}

int main()
{
    while(cin >> N >> M && N != 0)
    {
        init();
        string mon;
        int date, year, clock, od;
        for(int i = 0; i < N; i++) {
            cin >> mon >> date >> year >> clock >> od;
            order[i] = Order(Time(mon, date, year, clock), od);
        }

        cin >> T >> S;
        for(int i = 0; i < M; i++) {
            scanf("%d", &price[i]);
        }

        for(int i = 0; i < M; i++) {
            add((ll)price[i] - (ll)S * (ll)i, i);
        }

        ll sum = 0;
        ll cost;
        int t;
        for(int i = 0; i < N; i++) {
            t = order[i].time;
            cost = std_cost[t] + (ll)S * (ll)t;
            sum += cost * (ll)order[i].value;
        }

        cout << sum << endl;
    }
}