int* vv_add(int* x, int* y) {
    static int z[n];
    for(int i = 0; i < n; i++) {
        z[i] = x[i] + y[i];
    }
    return z;
}

int* mv_mult(int* A, int* x) {
    static int y[m];
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    return y;
}

int* vm_mult(int* x, int* A) {
    static int y[n];
    
}

keys Setup() {



}

CT_tuple Enc(pub_key_tuple PK, int M) {



}

int Dec(int* SK, CT_tuple CT) {



}
