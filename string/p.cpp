vz P(const string& s) {
    z n = s.size();
    vz p(n);
    for (z i = 1; i < n; i++) {
        z j = p[i-1];
        while (j > 0 && s[i] != s[j]) j = p[j-1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}
