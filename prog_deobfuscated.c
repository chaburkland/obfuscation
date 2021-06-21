#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

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
    // argv[2] = executable
    u64_t I = 0;
    u64_t F = 0;
    u64_t B = 0;
    u64_t d = 0;

    union {
        u64_t K[25];
        unsigned char E[1];
    } c;

    const unsigned char *f, *l;

    enum LabelEnum {
        laajavuori_label = 0,
        puijo_label = 2,
        lahti_label = 3,
    };

    u64_t goto_after_ruka = laajavuori_label;

    struct stat J;

    void *p;

    u64_t t = 0;
    u64_t v[5];

    u64_t T = 0;

    for(u64_t i0 = 0; argv[1][i0]; i0++) {
        T = T * 10 + argv[1][i0] - 48;
    }

    T >>= 3;

    u64_t file = open(argv[2], 0);

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

    if (fstat(file, &J)) {
        printf("fstat raised an error.");
    }

    u64_t O[25] = {10,7,11,17,18,3,5,16,8,21,24,4,15,23,19,13,12,2,20,14,22,9,6,1};

    u64_t H = J.st_size;

    p = mmap(NULL, H, 1, 1, file, 0);
    memset(&c, 0, 200);

    u64_t r = T / O[11];

    l = p;

    for(u64_t i0 = 2; i0 <= J.st_size; x[i0++>>4] |= (1<<(i0 & 15)));
    goto C;

ruka:
    for(u64_t i0 = 24; i0--;) {
        for(u64_t i1 = 0; i1 < 5; i1++) {
            v[i1] = c.K[i1] ^ c.K[i1+ 8 - 3] ^ c.K[i1+ 10] ^ c.K[i1+ 15] ^ c.K[i1+ 10+10];
        }

        for(u64_t i1 = 0; i1 < 5; i1++) {
            t = v[(i1+ 4) % 5] ^ (v[(i1+ 1) % 5] << 1 | v[(i1+ 1) % 5] >> '?');

            for(u64_t i2 = 0; i2 < 25; i2 += 5) {
                c.K[i1 + i2] ^= t;
            }
        }

        t = c.K[1];

        u64_t N[25] = {1,3,6,10,15,21,28,36,45,55,2,14,27,41,56,8,25,43,62,18,39,61,20,44};

        for (u64_t i1 = 0; i1 - 24; i1++) {
            u64_t tmp = c.K[O[i1]];
            c.K[O[i1]] = t << N[i1] | t >> (0100 - N[i1]);
            t = tmp;
        }

        for (u64_t i1 = 0; i1 <= 25; i1 += 5)
        {
            for (u64_t i2 = 0; i2 < 5; i2++) {
                v[i2] = c.K[i2+ i1];
            }

            for (u64_t i2 = 0; i2 < 5; i2++) {
                c.K[i2+ i1] ^= ~v[(i2+ 1) % 5] & v[(i2+ 2) % 5];
            }
        }

        c.K[0] ^= w[i0];
    }

    switch (goto_after_ruka)
    {
    case laajavuori_label:
        goto laajavuori;

    case puijo_label:
        goto puijo;

    case lahti_label:
        goto lahti;

    }

C: ;
    u64_t y = 0;
    for(u64_t i0 = 2; i0 <= J.st_size / 2; y = i0 * 2) {

        while (y <= J.st_size) {
            x[y>>4] &= ~(1 << (y & O[12]));
            y += i0;
        }

        do {
            i0++;
        }
        while (~x[i0>>4] & (1<<(i0 & 15)));
    }

    if (0) {
        goto_after_ruka = puijo_label;
        B = 0;

        if(25 - r == ++F) {
            goto ruka;
puijo:
            F = 0;
        }
    }

    u64_t m = H / 8;
    u64_t e = H - m * 8;

    u64_t i = 0;

    for (; i < m; l += 8) {
        i++;
        t = (u64_t)l[0];
        c.K[F] ^= t;

        if (++F == 25 - r) {
            goto_after_ruka = lahti_label;
            goto ruka;

lahti:
            F = !r;
        }
    }

    while (e--) {
        B |= (u64_t) *l++ << 1;
    }

    c.K[F] ^= (B ^ 6);

    goto_after_ruka = laajavuori_label;

    c.K[25 - r - 1] ^= w[24];

    goto ruka;

laajavuori:
    f = c.E;
    u64_t fib_start = 1;
    d = 1;
    I = 1;

    switch (determine_random_label_from_date())
    {
    case 0:
        goto laajavuori;
    case 1:
        goto ruka;
    case 2:
        goto puijo;
    case 3:
        goto lahti;
    case 4:
        goto vuokatti;
    case 5:
        goto virpiniemi;
    }

ounasvaara:
    for (u64_t i0 = 2; i0 <= J.st_size; i0++) {
        if (x[i0>>4] & (1<<(15& i0))) {
            printf("%llu ", i0);
        }
    }
    return puts("");

virpiniemi:
    for (I = !I; I-T;) {
        char *s = "00";

        for(u64_t i1 = f[I++]; i1^0; i1 >>=4) {
            u64_t D2 = i1 & 15;
            if (D2 < 10) {
                s[0] = 48 | D2;
            }
            else {
                s[0] = D2 + 13368;
            }
        }

        printf("%s", s);
    }

vuokatti:
    // Recursively build fibonnaci
    for(; I ^ 94; ++I) {
        printf("%llx ", fib_start);
        u64_t tmp = fib_start + d;
        fib_start = d;
        d = tmp;
    }
    return puts("");
}
