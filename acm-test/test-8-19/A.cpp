#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 1e3;
const double EPS = 1e-5;
int T, n;
typedef struct Grid
{
    double x, y;
    Grid(double a = 0, double b = 0) { x = a, y = b; }
} Point, Vector;
Vector operator-(Point a, Point b) { return Vector(b.x - a.x, b.y - a.y); }
double operator^(Vector a, Vector b) { return a.x * b.y - a.y * b.x; } //叉乘
struct Line
{
    Point s, e;
    Line() {}
    Line(Point a, Point b) { s = a, e = b; }
};
Point p[maxn];
Line L[maxn], que[maxn];

//得到极角角度
double getAngle(Vector a)
{
    return atan2(a.y, a.x);
}

//得到极角角度
double getAngle(Line a)
{
    return atan2(a.e.y - a.s.y, a.e.x - a.s.x);
}

//排序：极角小的排前面，极角相同时，最左边的排在最后面，以便去重
bool cmp(Line a, Line b)
{
    Vector va = a.e - a.s, vb = b.e - b.s;
    double A = getAngle(va), B = getAngle(vb);
    if (fabs(A - B) < EPS)
        return ((va) ^ (b.e - a.s)) >= 0;
    return A < B;
}

//得到两直线相交的交点
Point getIntersectPoint(Line a, Line b)
{
    double a1 = a.s.y - a.e.y, b1 = a.e.x - a.s.x, c1 = a.s.x * a.e.y - a.e.x * a.s.y;
    double a2 = b.s.y - b.e.y, b2 = b.e.x - b.s.x, c2 = b.s.x * b.e.y - b.e.x * b.s.y;
    return Point((c1 * b2 - c2 * b1) / (a2 * b1 - a1 * b2), (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1));
}

//判断 b,c 的交点是否在 a 的右边
bool onRight(Line a, Line b, Line c)
{
    Point o = getIntersectPoint(b, c);
    if (((a.e - a.s) ^ (o - a.s)) < 0)
        return true;
    return false;
}

bool HalfPlaneIntersection()
{
    sort(L, L + n, cmp);             //排序
    int head = 0, tail = 0, cnt = 0; //模拟双端队列
    //去重，极角相同时取最后一个。
    for (int i = 0; i < n - 1; i++)
    {
        if (fabs(getAngle(L[i]) - getAngle(L[i + 1])) < EPS)
        {
            continue;
        }
        L[cnt++] = L[i];
    }
    L[cnt++] = L[n - 1];

    for (int i = 0; i < cnt; i++)
    {
        //判断新加入直线产生的影响
        while (tail - head > 1 && onRight(L[i], que[tail - 1], que[tail - 2]))
            tail--;
        while (tail - head > 1 && onRight(L[i], que[head], que[head + 1]))
            head++;
        que[tail++] = L[i];
    }
    //最后判断最先加入的直线和最后的直线的影响
    while (tail - head > 1 && onRight(que[head], que[tail - 1], que[tail - 2]))
        tail--;
    while (tail - head > 1 && onRight(que[tail - 1], que[head], que[head + 1]))
        head++;
    if (tail - head < 3)
        return false;
    return true;
}

//判断输入点的顺序，如果面积 < 0，说明输入的点为顺时针，否则为逆时针
bool judge()
{
    double ans = 0;
    for (int i = 1; i < n - 1; i++)
    {
        ans += ((p[i] - p[0]) ^ (p[i + 1] - p[0]));
    }
    return ans < 0;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = n - 1; i >= 0; i--)
        {
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }

        if (judge())
        { //判断输入顺序，保证逆时针连边。
            for (int i = 0; i < n; i++)
            {
                L[i] = Line(p[(i + 1) % n], p[i]);
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                L[i] = Line(p[i], p[(i + 1) % n]);
            }
        }

        if (HalfPlaneIntersection())
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}