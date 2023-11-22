vz Z(string s) {
    z n = s.size();
    vz Z(n, n);
    for (z i = 1, x = 0; i < n; i++) {
        Z[i] = max(0, min(Z[i - x], x + Z[x] - i));
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            x = i, Z[i]++;
    }}
    return Z;
}
