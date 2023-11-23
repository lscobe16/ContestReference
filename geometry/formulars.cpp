// Komplexe Zahlen als Punkte. Wenn immer möglich complex<ll>
// verwenden. Funktionen wie abs() geben dann aber ll zurück.
using pt = complex<double>;
using vpt = vector<pt>;

bool compY(pt a, pt b) {
	return pair{imag(a), real(a)} < pair{imag(b), real(b)};
}
bool compX(pt a, pt b) {
	return pair{real(a), imag(a)} < pair{real(b), imag(b)};
}

double PIU = acos(-1.0l); // PIL < PI < PIU
double PIL = PIU-2e-19l;
double EPS = 1e-8; // for example

// Winkel zwischen Punkt und x-Achse in [-PI, PI].
double angle(pt a) {return arg(a);}

// rotiert Punkt im Uhrzeigersinn um den Ursprung.
pt rotate(pt a, double theta) {return a * polar(1.0, theta);}

// Skalarprodukt.
double dot(pt a, pt b) {return real(conj(a) * b);}

// faster norm, (euclidean norm)^2
double norm(pt a) {return dot(a, a);}

// Kreuzprodukt, aufgespannte Fläche mit Vorzeichen 
double cross(pt a, pt b) {return imag(conj(a) * b);}
double cross(pt p, pt a, pt b) {return cross(a - p, b - p);}
// integer: counter-clockwise ; use >= for true on colinear
bool ccw(pt a, pt b, pt c) {return cross(a, b, c) > 0;}

//  1 => c links von a->b
//  0 => a, b und c kollinear
// -1 => c rechts von a->b
int orientation(pt a, pt b, pt c) {
	double orien = cross(b - a, c - a);
	return (orien > EPS) - (orien < -EPS);
}

// Liegt d in der gleichen Ebene wie a, b, und c?
bool isCoplanar(pt a, pt b, pt c, pt d) {
	return abs((b - a) * (c - a) * (d - a)) < EPS;
}

// charakterisiert Winkel zwischen Vektoren u und v
pt uniqueAngle(pt u, pt v) { // O(log)
	pt tmp = v * conj(u);
	ll g = abs(gcd(real(tmp), imag(tmp)));
	return tmp / g;
}

void sortAround(pt p, vpt& ps) {
	sort(ps.begin(), ps.end(), [&](au a, au b){
		if (compX(a, p) != compX(b, p)) 
			return compX(a, p) > compX(b, p);
		return cross(p, a, b) > 0;
	});
}
