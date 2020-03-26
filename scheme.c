int* vv_add(int x[n], int y[n]) {
    static int z[n];
    for(int i = 0; i < n; i++) {
        z[i] = x[i] + y[i];
    }
    return z;
}

int* mv_mult(int A[n][n], int x[n]) {
    static int y[n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    return y;
}

keys Setup() {



}

CT_tuple Enc(pub_key_tuple PK, int M) {



}

int Dec(int* SK, CT_tuple CT) {



}
