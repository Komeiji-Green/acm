#include<bits/stdc++.h>
using namespace std;

// `���㼸��ģ��`
const double eps = 1e-14;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 1010;
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	else return x < 0 ? -1 : 1;
}
//square of a double
inline double sqr(double x){return x*x;}
struct Point{
	double x,y;
	Point(){}
	Point(double _x,double _y){
		x = _x;
		y = _y;
	}
	void input(){
		scanf("%lf%lf",&x,&y);
	}
	void output(){
		printf("%.2f %.2f\n",x,y);
	}
	bool operator == (Point b)const{
		return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
	}
	bool operator < (Point b)const{
		return sgn(x-b.x)== 0?sgn(y-b.y)<0:x<b.x;
	}
	Point operator -(const Point &b)const{
		return Point(x-b.x,y-b.y);
	}
	//���
	double operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
	//���
	double operator *(const Point &b)const{
		return x*b.x + y*b.y;
	}
	//���س���
	double len(){
		return hypot(x,y);//�⺯��
	}
	//���س��ȵ�ƽ��
	double len2(){
		return x*x + y*y;
	}
	//��������ľ���
	double distance(Point p){
		return hypot(x-p.x,y-p.y);
	}
	Point operator +(const Point &b)const{
		return Point(x+b.x,y+b.y);
	}
	Point operator *(const double &k)const{
		return Point(x*k,y*k);
	}
	Point operator /(const double &k)const{
		return Point(x/k,y/k);
	}
	//`����pa  ��  pb �ļн�`
	//`����������㿴a,b ���ɵļн�`
	//`���� LightOJ1203`
	double rad(Point a,Point b){
		Point p = *this;
		return fabs(atan2( fabs((a-p)^(b-p)),(a-p)*(b-p) ));
	}
	//`��Ϊ����Ϊr������`
	Point trunc(double r){
		double l = len();
		if(!sgn(l))return *this;
		r /= l;
		return Point(x*r,y*r);
	}
	//`��ʱ����ת90��`
	Point rotleft(){
		return Point(-y,x);
	}
	//`˳ʱ����ת90��`
	Point rotright(){
		return Point(y,-x);
	}
	//`����p����ʱ����תangle`
	Point rotate(Point p,double angle){
		Point v = (*this) - p;
		double c = cos(angle), s = sin(angle);
		return Point(p.x + v.x*c - v.y*s,p.y + v.x*s + v.y*c);
	}
};
struct Line{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e){
		s = _s;
		e = _e;
	}
	bool operator ==(Line v){
		return (s == v.s)&&(e == v.e);
	}
	//`����һ�������б��angleȷ��ֱ��,0<=angle<pi`
	Line(Point p,double angle){
		s = p;
		if(sgn(angle-pi/2) == 0){
			e = (s + Point(0,1));
		}
		else{
			e = (s + Point(1,tan(angle)));
		}
	}
	//ax+by+c=0
	Line(double a,double b,double c){
		if(sgn(a) == 0){
			s = Point(0,-c/b);
			e = Point(1,-c/b);
		}
		else if(sgn(b) == 0){
			s = Point(-c/a,0);
			e = Point(-c/a,1);
		}
		else{
			s = Point(0,-c/b);
			e = Point(1,(-c-a)/b);
		}
	}
	void input(){
		s.input();
		e.input();
	}
	void adjust(){
		if(e < s)swap(s,e);
	}
	//���߶γ���
	double length(){
		return s.distance(e);
	}
	//`����ֱ����б�� 0<=angle<pi`
	double angle(){
		double k = atan2(e.y-s.y,e.x-s.x);
		if(sgn(k) < 0)k += pi;
		if(sgn(k-pi) == 0)k -= pi;
		return k;
	}
	//`���ֱ�߹�ϵ`
	//`1  �����`
	//`2  ���Ҳ�`
	//`3  ��ֱ����`
	int relation(Point p){
		int c = sgn((p-s)^(e-s));
		if(c < 0)return 1;
		else if(c > 0)return 2;
		else return 3;
	}
	// �����߶��ϵ��ж�
	bool pointonseg(Point p){
		return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) <= 0;
	}
	//`������ƽ��(��Ӧֱ��ƽ�л��غ�)`
	bool parallel(Line v){
		return sgn((e-s)^(v.e-v.s)) == 0;
	}
	//`���߶��ཻ�ж�`
	//`2 �淶�ཻ`
	//`1 �ǹ淶�ཻ`
	//`0 ���ཻ`
	int segcrossseg(Line v) {
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		int d3 = sgn((v.e-v.s)^(s-v.s));
		int d4 = sgn((v.e-v.s)^(e-v.s));
		if( (d1^d2)==-2 && (d3^d4)==-2 )return 2;
		return (d1==0 && sgn((v.s-s)*(v.s-e))<=0) ||
			(d2==0 && sgn((v.e-s)*(v.e-e))<=0) ||
			(d3==0 && sgn((s-v.s)*(s-v.e))<=0) ||
			(d4==0 && sgn((e-v.s)*(e-v.e))<=0);
	}
	//`ֱ�ߺ��߶��ཻ�ж�`
	//`-*this line   -v seg`
	//`2 �淶�ཻ`
	//`1 �ǹ淶�ཻ`
	//`0 ���ཻ`
	int linecrossseg(Line v) {
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		if((d1^d2)==-2) return 2;
		return (d1==0||d2==0);
	}
	//`��ֱ�߹�ϵ`
	//`0 ƽ��`
	//`1 �غ�`
	//`2 �ཻ`
	int linecrossline(Line v){
		if((*this).parallel(v))
			return v.relation(s)==3;
		return 2;
	}
	//`����ֱ�ߵĽ���`
	//`Ҫ��֤��ֱ�߲�ƽ�л��غ�`
	Point crosspoint(Line v){
		double a1 = (v.e-v.s)^(s-v.s);
		double a2 = (v.e-v.s)^(e-v.s);
		return Point((s.x*a2-e.x*a1)/(a2-a1),(s.y*a2-e.y*a1)/(a2-a1));
	}
	//�㵽ֱ�ߵľ���
	double dispointtoline(Point p){
		return fabs((p-s)^(e-s))/length();
	}
	//�㵽�߶εľ���
	double dispointtoseg(Point p){
		if(sgn((p-s)*(e-s))<0 || sgn((p-e)*(s-e))<0)
			return min(p.distance(s),p.distance(e));
		return dispointtoline(p);
	}
	//`�����߶ε��߶εľ���`
	//`ǰ�������߶β��ཻ���ཻ�������0��`
	double dissegtoseg(Line v){
		return min(min(dispointtoseg(v.s),dispointtoseg(v.e)),min(v.dispointtoseg(s),v.dispointtoseg(e)));
	}
	//`���ص�p��ֱ���ϵ�ͶӰ`
	Point lineprog(Point p){
		Point v = e - s;
		return s + ( (v * (v*(p-s))) / (v.len2()) );
	}
	//`���ص�p����ֱ�ߵĶԳƵ�`
	Point symmetrypoint(Point p){
		Point q = lineprog(p);
		return Point(2*q.x-p.x,2*q.y-p.y);
	}
};

int main() {
	int T;
	cin >> T;
	Line w, b;
	int cas = 0;
	Line l1, l2, l3, l4;
	Point cp;
	int sg;
	double ans;
	while(T--) {
		++cas;
		w.input();
		b.input();
		if(w.s == w.e) {
			printf("Case %d: 0.000\n", cas);
		} else if(b.s == b.e) {
			printf("Case %d: inf\n", cas);
		} else {
			int crs = w.segcrossseg(b);
			if(crs == 2) {
				printf("Case %d: 0.000\n", cas);
			} else if(crs == 1) {
				if(w.relation(b.s) == 3 && w.relation(b.e) == 3) {
					printf("Case %d: 0.000\n", cas);
				} else if(w.pointonseg(b.s) || w.pointonseg(b.e)) {
					printf("Case %d: inf\n", cas);
				} else {
					printf("Case %d: 0.000\n", cas);
				}
			} else {
				if(sgn((w.e - w.s) ^ (b.e - w.s)) * sgn((w.e - w.s) ^ (b.s - w.s)) <= 0) {
					printf("Case %d: 0.000\n", cas);
				} else {
					sg = sgn((w.e - w.s) ^ (b.e - w.s));
					bool flag = false;
					l1 = Line(w.e, b.e);
					l2 = Line(w.s, b.s);
					l3 = Line(w.e, b.s);
					l4 = Line(w.s, b.e);
					if(!l1.parallel(l2)) {
						cp = l1.crosspoint(l2);
						if(sgn((w.e - w.s) ^ (cp - w.s)) != sg) {
							flag = true;
							ans = abs((w.e - w.s) ^ (cp - w.s)) / 2;
						}
					}
					if(!l3.parallel(l4)) {
						cp = l3.crosspoint(l4);
						if(sgn((w.e - w.s) ^ (cp - w.s)) != sg) {
							flag = true;
							ans = abs((w.e - w.s) ^ (cp - w.s)) / 2;
						}
					}
					if(!flag) {
						printf("Case %d: inf\n", cas);
					} else {
						printf("Case %d: %.10f\n", cas, ans);
					}
				}
			}
		}
	}
}
