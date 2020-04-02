#include "scheme.h"
int* r;
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

    //int* r = malloc(m * sizeof(int));
    for(int i = 0 ; i < m; i++) {
        //*(r + i) = modq((long long int) rand());
    }
    mv_mult(PK.A, r, CT.CT1);
    printf("HUHL %d\n", modq((long long int) vv_mult_m(PK.b, r)));
    CT.CT2 = modq((long long int) vv_mult_m(PK.b, r) + M * (int) (q / 2));
    //free(r);

    return CT;
}

int Dec(int* SK, CT_tuple CT) {
    printf("BRUHL %d\n", vv_mult_n(SK, CT.CT1));
    int w = modq((long long int) CT.CT2 - vv_mult_n(SK, CT.CT1));
    if(w < (int) (q / 4)) {
        //printf("w: %d\n", w);
        return 0;
    }
    //printf("w: %d\n", w);
    return 1;
}

int main() {
    r = malloc(m * sizeof(int));

    int* temp1 = malloc(m * sizeof(int));
    int* temp2 = malloc(n * sizeof(int));

    for(int i = 0 ; i < m; i++) {
        *(r + i) = modq((long long int) rand());
    }

    
    keys PS_keys = Setup();

    vm_mult(PS_keys.SK, PS_keys.PK.A, temp1);
    int first = vv_mult_m(temp1, r);
    printf("%d\n", first);
    mv_mult(PS_keys.PK.A, r, temp2);
    int second = vv_mult_n(PS_keys.SK, temp2);
    printf("%d\n", second);
    printf("\n");

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