#include "scheme.h"

int* vv_add(int* x, int* y, int* z) {
    for(int i = 0; i < m; i++) {
        *(z + i) = modq((long long int) *(x + i) + *(y + i));
    }
    return z;
}

int vv_mult_m(int* x, int* y) {
    int z = 0;
    for(int i = 0; i < m; i++) {
        z = modq((long long int) z + modq((long long int) *(x + i) * *(y + i)));
    }
    return modq((long long int) z);
}

int vv_mult_n(int* x, int* y) {
    int z = 0;
    for(int i = 0; i < n; i++) {
        z = modq((long long int) z + modq((long long int) *(x + i) * *(y + i)));
    }
    return z;
}

int* mv_mult(int* A, int* x, int* y) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            *(y + i) = modq((long long int) *(y + i) + modq((long long int) *(A + i * m + j) * *(x + j)));
        }
    }
    return y;
}

int* vm_mult(int* x, int* A, int* y) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            *(y + i) = modq((long long int) *(y + i) + modq((long long int) *(A + j * m + i) * *(x + j)));
        }
    }
    return y;
}

keys Setup() {
    keys PS_keys;
    PS_keys.PK.A = malloc(n * m * sizeof(int));
    PS_keys.PK.b = malloc(m * sizeof(int));
    PS_keys.SK = malloc(n * sizeof(int));
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            *(PS_keys.PK.A + i * m + j) = modq((long long int) rand());
        }
    }
    for(int i = 0; i < n; i++) {
        *(PS_keys.SK + i) = modq((long long int) rand());
    }

    //IP
    int* e = malloc(m * sizeof(int));
    for(int i = 0 ; i < m; i++) {
        *(e + i) = 0;
    }

    int* SK_A = malloc(m * sizeof(int));
    vm_mult(PS_keys.SK, PS_keys.PK.A, SK_A);
    vv_add(SK_A, e, PS_keys.PK.b);
    //free(SK_A);
    
    return PS_keys;
}

CT_tuple Enc(pub_key_tuple PK, int M) {
    CT_tuple CT;
    CT.CT1 = malloc(n * sizeof(int));

    int* r = malloc(m * sizeof(int));
    for(int i = 0 ; i < m; i++) {
        *(r + i) = modq((long long int) rand());
    }
    mv_mult(PK.A, r, CT.CT1);
    CT.CT2 = modq((long long int) vv_mult_m(PK.b, r) + M * (int) (q / 2));
    //free(r);

    return CT;
}

int Dec(int* SK, CT_tuple CT) {
    int w = modq((long long int) CT.CT2 - vv_mult_n(SK, CT.CT1));
    if(w < (int) (q / 4)) {
        return 0;
    }
    return 1;
}

int main() {
    keys PS_keys = Setup();

    CT_tuple CT = Enc(PS_keys.PK, 1);
    int M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);

    CT = Enc(PS_keys.PK, 0);
    M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);

    CT = Enc(PS_keys.PK, 1);
    M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);

    CT = Enc(PS_keys.PK, 0);
    M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);

    CT = Enc(PS_keys.PK, 1);
    M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);
    
    CT = Enc(PS_keys.PK, 0);
    M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);

    CT = Enc(PS_keys.PK, 1);
    M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);

    CT = Enc(PS_keys.PK, 0);
    M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);
}