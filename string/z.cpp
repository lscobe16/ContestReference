vz Z(const string& s) {
    z n = s.size();
    vz z(n);
    for (z i = 1, x = 0; i < n; i++) {
        z[i] = max(0, min(z[i - x], x + z[x] - i));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            x = i, z[i]++;
    }}
    return z;
}
