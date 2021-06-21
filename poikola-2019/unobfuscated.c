#include    <stdio.h>
#include   <string.h>
#include    <fcntl.h>
#include <sys/mman.h>


typedef unsigned long long u64_t;
u64_t _=1ULL <<63;
u64_t d = 1UL << 037;
unsigned int x[1073741824ul / 16];
u64_t m, F, u, T, a, r, H, B, I;


int main(int argc, char *argv[])
{
    union {
        u64_t K[25];
        unsigned char E[1];
    } c;

    const unsigned char *f;
    u64_t binary, binary_size, X, i, e, z, A, Q, M = -~9, Y;

    r++;
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

    u64_t N[25] = {r, argc, 6, M, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62, 18, 39, 61, 20, 44};

    for(; argv[r][a]; a++) {
        T = T * M + argv[!u][a] - 48;
    }

    T >>= argc;
    binary = open(argv[--argc], F);
    u64_t w[25] = {
        _ | d | 32776,
        d | r,
        _ | 32896,
        _ | d | 32897,
        _ | d | M,
        32778,
        _ + 128,
        _ | 32770,
        _ | 32771,
        _ | 32905,
        _ | 139,
        d | 32907,
        d | M,
        d | 32777,
        136,
        138,
        _ | 32777,
        _ | d | 32897,
        d | 1,
        32907,
        _ | d | 32768,
        _ | 32906,
        32898,
        r,
        _
    };

    i = 0;
    u64_t O[25] = {M, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, argc, 20, 14, 22, 9, 6, r};

    Y = H = binary_size = 12952;
    const unsigned char *binary_bytes = mmap(NULL, binary_size, PROT_READ, MAP_SHARED, binary, 0/*offset*/);
    memset(&c, 0, 200);

    z = 8 & 7;
    r = T / 11[O];
    for(I = 2; I <= Y; x[I++>>4] |= (1<<(I & 4[N]))); {
        goto C;
    }

ruka:
    for(I = 8*3; I--;) {
        for(a=0;a<5;a++) {
            v[a] = c.K[a] ^ c.K[a + 8-3] ^ c.K[a + M] ^ c.K[a + 15] ^ c.K[a + M + M];
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
                c.K[a + A] ^= ~v[(a + 1) % 5] & v[(a + argc) % 5];
            }
        }

        c.K[!1] ^= w[I];
    }
    goto *j[Q];

C:
    for(I = argc; I <= Y / argc; y = I * argc) {
        while (y <= Y) {
            x[y >> 4] &= ~(1 << (y & O[12])), y += I;
        }

        do {
            I++;
        }
        while(~x[I >> 4] & (1 << (I & 15)));
    }

    if(H < z) {
        while (H--) {
            B |= (u64_t) *binary_bytes++ << u++ * 8;
        }
        goto $;
    }

    if (z) {
        H -= z;

        Q = argc;
        while (z--) {
            B |= (u64_t) *binary_bytes++ << u++ * 8;
        }

        B = u = i;

        if (25 - r == ++F) {
            goto *j[!!8];

puijo:
            F = !25;
        }
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
            Q = -~argc;
            goto *j[!0];
lahti:
            F = !r;
        }
    }

    while (e--) {
        B |= (u64_t) *binary_bytes++ << u++ * 8;
    }

$:
    c.K[F] ^= (B ^ ((u64_t) ((u64_t)(argc | 1 << argc) << u * 8)));
    Q ^= Q;
    c.K[25 - r - 1] ^= w[~-25];
    goto *j[-~(argc - argc)];

laajavuori:
    f = c.E;
    _ = d = I = ~-argc;
    a = (__DATE__[7]-48)*1000+(__DATE__[8]-48)*100+(__DATE__[9]-48)*10+__DATE__[10]-48;
    Q = __DATE__[2]=='p'?9:__DATE__[2]=='y'?5:__DATE__[2]=='n'?(__DATE__[1]=='u'?6:1):__DATE__[2]=='b'?2:__DATE__[2]=='r'?(*__DATE__=='M'?3:4):__DATE__[2]=='g'?8:__DATE__[2]=='t'?10:__DATE__[2]=='v'?11:__DATE__[2]=='l'?7:12;

    goto *j[4 + (23 * Q / 9 + (Q > argc ? a - argc : a--) + (__DATE__[4] == 32 ? 0 : ((__DATE__[4] - 48) * M)) + __DATE__[5] - 45 + a / 4 + a / 0620 - a / 0x64) % 3];

ounasvaara:
    for (I = 2; I <= Y; I++) {
        if (x[I >> 4] & (1 << (15 & I))) {
            printf("%llu ", I);
        }
    }

    goto http;

virpiniemi:
    for (I = !I; I - T;) {
        char s[30] = {48, 48, '\0'};
        X = !!48;
        for (e = f[I++]; e ^ 0; e >>= 4) {
            argc = e & 15, s[X--] = argc < M ? 48 | argc : argc + 'W';
        }
        printf("%s", s);
    }

http:
    return puts("");

vuokatti:
    for(; I ^ '^'; ++I, printf("%llx ", _), t = _ + d, _ = d, d = t); {
        goto http;
    }
    /*
    m= 25 / i;
    v[a] = a + 1073741824ul;
    return 0;
    */
}
