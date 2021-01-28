#include<bits/stdc++.h>
#include<map>
using namespace std;

const int maxn = 100050;
struct Suffix_Automata {
	int maxlen[maxn<<1], trans[maxn<<1][26], link[maxn<<1], Size, Last;
	Suffix_Automata() { Size = Last = 1; }

	inline void Extend(int id) {
		int cur = (++Size), p;
		maxlen[cur] = maxlen[Last] + 1;
		for (p = Last; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
		if (!p) link[cur] = 1;
		else {
			int q = trans[p][id];
			if (maxlen[q] == maxlen[p] + 1) link[cur] = q;
			else {
				int clone = (++ Size);
				maxlen[clone] = maxlen[p] + 1;
				Cpy(trans[clone], trans[q]);
				link[clone] = link[q];
				for (; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
				link[cur] = link[q] = clone;
			}
		} 
		Last = cur;
	}
} T;