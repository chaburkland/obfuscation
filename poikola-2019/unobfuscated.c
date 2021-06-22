#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define SPACE ' '
#define ZERO '0'

typedef unsigned long long u64_t;

int
determine_random_label_from_date()
{
    time_t current_time = time(NULL);
    u64_t day = localtime(&current_time)->tm_mday;
    u64_t month = localtime(&current_time)->tm_mon + 1;
    u64_t year = localtime(&current_time)->tm_year + 1900;

    return (
        (23 * month / 9) +
        day -
        45 +
        (month > 2 ? year - 2 : year--) +
        (year / 4) +
        (year / 400) -
        (year / 100)
    ) % 3;
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

    union {
        u64_t K[25];
        unsigned char E[1];
    } c;

    enum LabelEnum {
        laajavuori_label = 0,
        lahti_label = 1,
    };

    u64_t goto_after_ruka = laajavuori_label;

    const unsigned char *f;
    u64_t binary_size, i, A;
    u64_t e = 0;

    u64_t t, y=0, v[5];

    u64_t N[25] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62, 18, 39, 61, 20, 44};

    u64_t T = 0;
    for(u64_t i0 = 0; argv[1][i0]; i0++) {
        T = T * 10 + argv[1][i0] - 48;
    }
    T >>= 3;

    u64_t binary_fileno = open(argv[2], F);
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

    H = binary_size = 12952;
    const unsigned char *binary_bytes = mmap(NULL, binary_size, PROT_READ, MAP_SHARED, binary_fileno, 0);
    memset(&c, 0, 200);

    u64_t r = T / 4;
    unsigned int x[(binary_size / 16) + 1];
    memset(x, 0, (binary_size / 16) + 1);

    for(I = 2; I <= binary_size; ++I) {
        x[I>>4] |= (1 << (I & 0xF));
    }
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

    switch (goto_after_ruka)
    {
    case laajavuori_label:
        goto laajavuori;

    case lahti_label:
        goto lahti;

    }

C:
    for(I = 2; I <= binary_size / 2; y = I * 2) {
        while (y <= binary_size) {
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
            goto_after_ruka = lahti_label;
            goto ruka;
lahti:
            F = !r;
        }
    }

    u64_t B = 0;
    while (e--) {
        B |= (u64_t) *binary_bytes++ << u++ * 8;
    }

    c.K[F] ^= (B ^ ((u64_t) ((u64_t)(2 | 1 << 2) << u * 8)));
    goto_after_ruka = laajavuori_label;
    c.K[25 - r - 1] ^= w[24];

    goto ruka;

laajavuori:;
    f = c.E;
    I = 1;

    // Beginning of the end. All options will enter a label that ends the routine.
    switch (determine_random_label_from_date())
    {
    case 0:
        goto vuokatti;
    case 1:
        goto virpiniemi;
    }

ounasvaara:;
    // Cleaned up 06/21/2021
    // Generate all primes until (binary_size / 16)
    for (u64_t i0 = 2; i0 <= binary_size; ++i0) {
        if (x[i0 >> 4] & (1 << (0xF & i0))) {
            printf("%llu ", i0);
        }
    }
    return puts("");

virpiniemi:
    // Cleaned up 06/21/2021
    for (u64_t i0 = !I; i0 < T; ++i0) {
        char result[2] = {48, 48, '\0'};

        u64_t s_idx = 1;

        for (u64_t i1 = f[i0]; i1 ^ 0; i1 >>= 4) { // Always runs twice
            u64_t tmp_var = i1 & 15;
            if (tmp_var < 10) {
                result[s_idx] = tmp_var | 48;
            }
            else {
                result[s_idx] = tmp_var + 87;
            }
            --s_idx;
        }
        printf("%s", result); // This prints 2 characters at a time
    }

    return puts("");

vuokatti:;
    // Iteratively build fibonnaci
    u64_t last = 1;
    u64_t last_last = 1;

    for(u64_t i0 = 0; i0 < 93; ++i0) {
        printf("%llx ", last);
        u64_t tmp = last + last_last;
        last = last_last;
        last_last = tmp;
    }

    return puts("");
}
