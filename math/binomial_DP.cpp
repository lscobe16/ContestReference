const z N = 1000+1;
z B[N][N];

B[0][0] = 1;
for (z n = 1; n < N; ++n) {
    B[n][0] = B[n][n] = 1;
    for (z k = 1; k < n; ++k)
        B[n][k] = B[n-1][k-1] + B[n-1][k];
}
