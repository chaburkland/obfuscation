#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define SPACE ' '
#define ZERO '0'

typedef unsigned long long u64_t;
unsigned int x[67108864];

int
determine_random_label_from_date()
{
    time_t current_time = time(NULL);
    u64_t month = localtime(&current_time)->tm_mon + 1;

    u64_t seed = (__DATE__[7] - ZERO) * 1000 +
                 (__DATE__[8] - ZERO) * 100 +
                 (__DATE__[9] - ZERO) * 10 +
                 (__DATE__[10] - ZERO);

    u64_t random_label = 4 + (
        (23 * month / 9) +
        (month > 2 ? seed - 2 : seed--) +
        (__DATE__[4] == SPACE ? 0 : ((__DATE__[4] - ZERO) * 10)) +
        __DATE__[5] -
        45 +
        (seed / 4) +
        (seed / 400) -
        (seed / 100)
    ) % 3;

    return random_label;
}

int main(int argc, char *argv[])
{
    // argv[0] = executable
    // argv[1] = some number
    // argv[2] = compiled_binary
    u64_t I = 0;
    u64_t F = 0;
    u64_t m = 0;
    u64_t u = 0;
    u64_t a = 0;
    u64_t H = 0;

    u64_t _ = 1ULL << 63;
    u64_t d = 1UL << 037;

    union {
        u64_t K[25];
        unsigned char E[1];
    } c;

    const unsigned char *f;
    u64_t binary, binary_size, X, i, e, A, Q, Y;

    u64_t t, y=0, v[5];
    const void *j[] = {
        &&laajavuori,
        &&ruka,
        &&puijo,
        &&lahti,
        &&vuokatti,
        &&virpiniemi,
        &&ounasvaara
    };

    u64_t N[25] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62, 18, 39, 61, 20, 44};

    u64_t T = 0;
    for(u64_t i0 = 0; argv[1][i0]; i0++) {
        T = T * 10 + argv[1][i0] - 48;
    }
    T >>= 3;

    binary = open(argv[2], F);
    u64_t w[25] = {
        9223372039002292232ULL,
        2147483649,
        9223372036854808704ULL,
        9223372039002292353ULL,
        9223372039002259466ULL,
        32778,
        9223372036854775936ULL,
        9223372036854808578ULL,
        9223372036854808579ULL,
        9223372036854808713ULL,
        9223372036854775947ULL,
        2147516555,
        2147483658,
        2147516425,
        136,
        138,
        9223372036854808585ULL,
        9223372039002292353ULL,
        2147483649,
        32907,
        9223372039002292224ULL,
        9223372036854808714ULL,
        32898,
        1,
        9223372036854775808ULL,
    };

    i = 0;
    u64_t O[25] = {10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1};

    Y = H = binary_size = 12952;
    const unsigned char *binary_bytes = mmap(NULL, binary_size, PROT_READ, MAP_SHARED, binary, 0);
    memset(&c, 0, 200);

    u64_t r = T / 4;

    for(I = 2; I <= Y; x[I++>>4] |= (1<<(I & 4[N])));
    goto C;

ruka:
    for(I = 8*3; I--;) {
        for(a=0;a<5;a++) {
            v[a] = c.K[a] ^ c.K[a + 5] ^ c.K[a + 10] ^ c.K[a + 15] ^ c.K[a + 20];
        }
        for(a=0;a<5;a++) {
            t = v[(a + 4) % 5] ^ (v[(a + 1) % 5] << 1 | v[(a + 1) % 5] >> '?');
            for(A = 0; A < 25; A +=5) {
                c.K[a + A] ^= t;
            }
        }
        t = c.K[1];
        for (a = 0; a - 24; a++) {
            A = O[a], *v = c.K[A], c.K[A] = t << N[a] | t >> (0100 - N[a]), t = *v;
        }

        for(A =! 25; A ^ 25; A += 5) {
            for(a=0;a<5;a++) {
                v[a] = c.K[a + A];
            }
            for(a=0;a<5;a++) {
                c.K[a + A] ^= ~v[(a + 1) % 5] & v[(a + 2) % 5];
            }
        }

        c.K[!1] ^= w[I];
    }
    goto *j[Q];

C:
    for(I = 2; I <= Y / 2; y = I * 2) {
        while (y <= Y) {
            x[y >> 4] &= ~(1 << (y & 15)), y += I;
        }

        do {
            I++;
        }
        while(~x[I >> 4] & (1 << (I & 15)));
    }

    if (0) {

puijo:
        F = !25;
    }

    m = H / 8;
    e = H - m * 8;

    for (; i < m; binary_bytes += 8) {
        i++;
        u64_t S =~ -! 48;
        t = (u64_t) binary_bytes[++S] << 8 * S
            | (u64_t) binary_bytes[++S] << 8 * S
            | (u64_t) binary_bytes[++S] << 8 * S
            | (u64_t) binary_bytes[++S] << 8 * S
            | (u64_t) binary_bytes[++S] << 8 * S
            | (u64_t) binary_bytes[++S] << 8 * S
            | (u64_t) binary_bytes[++S] << 8 * S
            | (u64_t) binary_bytes[++S] << 8 * S;
        c.K[F] ^= t;
        if (++F == 25 - r) {
            Q = -~2;
            goto *j[!0];
lahti:
            F = !r;
        }
    }

    u64_t B = 0;
    while (e--) {
        B |= (u64_t) *binary_bytes++ << u++ * 8;
    }

    c.K[F] ^= (B ^ ((u64_t) ((u64_t)(2 | 1 << 2) << u * 8)));
    Q ^= Q;
    c.K[25 - r - 1] ^= w[~-25];
    goto *j[-~(2 - 2)];

laajavuori:;
    f = c.E;
    _ = d = I = ~-2;
    a = (__DATE__[7]-48)*1000+(__DATE__[8]-48)*100+(__DATE__[9]-48)*10+__DATE__[10]-48;
    Q = __DATE__[2]=='p'?9:__DATE__[2]=='y'?5:__DATE__[2]=='n'?(__DATE__[1]=='u'?6:1):__DATE__[2]=='b'?2:__DATE__[2]=='r'?(*__DATE__=='M'?3:4):__DATE__[2]=='g'?8:__DATE__[2]=='t'?10:__DATE__[2]=='v'?11:__DATE__[2]=='l'?7:12;

    goto *j[4 + (23 * Q / 9 + (Q > 2 ? a - 2 : a--) + (__DATE__[4] == 32 ? 0 : ((__DATE__[4] - 48) * 10)) + __DATE__[5] - 45 + a / 4 + a / 0620 - a / 0x64) % 3];

ounasvaara:;
    for (I = 2; I <= Y; I++) {
        if (x[I >> 4] & (1 << (15 & I))) {
            printf("%llu ", I);
        }
    }

    return puts("");

virpiniemi:;

    u64_t tmp_var = 2;

    for (I = !I; I - T;) {
        char s[30] = {48, 48, '\0'};
        X = !!48;
        for (e = f[I++]; e ^ 0; e >>= 4) {
            tmp_var = e & 15, s[X--] = tmp_var < 10 ? 48 | tmp_var : tmp_var + 'W';
        }
        printf("%s", s);
    }

    return puts("");

vuokatti:;
    for(; I ^ '^'; ++I, printf("%llx ", _), t = _ + d, _ = d, d = t); {
        return puts("");
    }
    /*
    m= 25 / i;
    v[a] = a + 1073741824ul;
    return 0;
    */
}
