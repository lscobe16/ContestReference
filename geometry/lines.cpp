// Entfernung von Punkt p zur Geraden durch a-b. 2d und 3d
double distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

// Projiziert p auf die Gerade a-b
pt projectToLine(pt a, pt b, pt p) {
	return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}

// Liegt p auf der Geraden a-b? 2d und 3d
bool pointOnLine(pt a, pt b, pt p) {
	return cross(a, b, p) == 0;
}

// Test auf Schnitt der Geraden a-b und c-d <=> nicht parallel
bool lineIntersection(pt a, pt b, pt c, pt d) {
	return abs(cross(a - b, c - d)) < EPS;
}

// Berechnet den Schnittpunkt der Geraden p0-p1 und p2-p3.
// die Geraden dürfen nicht parallel sein!
pt lineIntersection(pt p0, pt p1, pt p2, pt p3) {
	double a = cross(p1 - p0, p3 - p2);
	double b = cross(p2 - p0, p3 - p2);
	return {p0 + b/a*(p1 - p0)};
}
