// Upper Envelope, dynamisch.
struct Line {
	ll m, b;
	mutable function<const Line*()> succ;
	bool operator<(const Line& rhs) const {
		if (rhs.b != LLONG_MIN) return m < rhs.m;
		const Line* s = succ();
		if (!s) return 0;
		ll x = rhs.m;
		return b - s->b < (s->m - m) * x;
	}
};

struct HullDynamic : public multiset<Line> {
	bool bad(iterator y) {
		auto z = next(y);
		if (y == begin()) {
			if (z == end()) return 0;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if (z == end()) return y->m == x->m && y->b <= x->b;
		return (x->b - y->b)*(z->m - y->m) >=
		       (y->b - z->b)*(y->m - x->m);
	}

	// Variant 1: niklasb (2015)
	void insert_line(ll m, ll b) { // Laufzeit: O(log(n))
		auto y = insert({m, b});
		y->succ = [=] {return next(y) == end() ? 0 : &*next(y);};
		if (bad(y)) {erase(y); return;}
		while (next(y) != end() && bad(next(y))) erase(next(y));
		while (y != begin() && bad(prev(y))) erase(prev(y));
	}

	// Variant 2: barni120400 (2019)
	void insert_line(ll m, ll b) {
		auto y = insert({ m, b });
		if (bad(y)) {erase(y); return;}
		while (next(y) != end() && bad(next(y))) erase(next(y));
		y->succ = [=] {return next(y) == end() ? 0 : &*next(y);};
		while (y != begin() && bad(prev(y))) erase(prev(y));
		if (y != begin()) prev(y)->succ = [=] {return &*y;};
	}

	ll query(ll x) { // Laufzeit: O(log(n)) 
		auto l = *lower_bound((Line) {x, LLONG_MIN});
		return l.m * x + l.b;
	}
};
