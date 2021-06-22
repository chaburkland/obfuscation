#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

# define BINARY_SIZE 12952

typedef unsigned long long u64_t;

int
determine_random_label_from_date()
{
    time_t current_time = time(NULL);
    int day = localtime(&current_time)->tm_mday;
    int month = localtime(&current_time)->tm_mon + 1;
    int year = localtime(&current_time)->tm_year + 1900;

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

int
fibonacci()
{
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

int
virpiniemi(const unsigned char *f, u64_t T)
{
    // Cleaned up 06/21/2021
    for (u64_t i0 = 0; i0 < T; ++i0) {
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
}

int
laajavuori(const unsigned char *f, u64_t T, unsigned int *x)
{
    // Beginning of the end. All options will enter a label that ends the routine.
    switch (determine_random_label_from_date())
    {
    case 0:
        return fibonacci();
    case 1:
        return virpiniemi(f, T);
    }

    // Cleaned up 06/21/2021
    // Generate all primes until (BINARY_SIZE / 16)
    for (u64_t i0 = 2; i0 <= BINARY_SIZE; ++i0) {
        if (x[i0 >> 4] & (1 << (0xF & i0))) {
            printf("%llu ", i0);
        }
    }
    return puts("");
}

int main(int argc, char *argv[])
{
    // argv[0] = executable
    // argv[1] = some number
    // argv[2] = compiled_binary
    u64_t F = 0;
    u64_t u = 0;

    union {
        u64_t K[25];
        unsigned char E[1];
    } c;

    enum LabelEnum {
        call_laajavuori = 0,
        goto_lahti_label = 1,
    };

    u64_t do_after_ruka = call_laajavuori;

    const unsigned char *f;
    u64_t e = 0;

    u64_t t = 0;
    u64_t y = 0;
    u64_t v[5];

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

    u64_t i = 0;
    u64_t O[25] = {10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1};

    const unsigned char *binary_bytes = mmap(NULL, BINARY_SIZE, PROT_READ, MAP_SHARED, binary_fileno, 0);
    memset(&c, 0, 200);

    u64_t r = T / 4;
    unsigned int x[(BINARY_SIZE / 16) + 1];
    memset(x, 0, (BINARY_SIZE / 16) + 1);

    for(u64_t i0 = 2; i0 <= BINARY_SIZE; ++i0) {
        x[i0 >> 4] |= (1 << (i0 & 0xF));
    }
    goto C;

ruka:
    for(u64_t i0 = 24; i0--;) {
        for(u64_t i1 = 0; i1 < 5; ++i1) {
            v[i1] = c.K[i1] ^ c.K[i1 + 5] ^ c.K[i1 + 10] ^ c.K[i1 + 15] ^ c.K[i1 + 20];
        }
        for(u64_t i1 = 0; i1 < 5; ++i1) {
            t = v[(i1 + 4) % 5] ^ (v[(i1 + 1) % 5] << 1 | v[(i1 + 1) % 5] >> 63);
            for(u64_t i2 = 0; i2 < 25; i2 += 5) {
                c.K[i1 + i2] ^= t;
            }
        }
        t = c.K[1];
        for (u64_t i1 = 0; i1 - 24; ++i1) {
            u64_t tmp_idx = O[i1];
            *v = c.K[tmp_idx];
            c.K[tmp_idx] = t << N[i1] | t >> (0100 - N[i1]);
            t = *v;
        }

        for(u64_t i1 = 0; i1 < 25; i1 += 5) {
            for(u64_t i2 = 0; i2 < 5; ++i2) {
                v[i2] = c.K[i2 + i1];
            }
            for(u64_t i2 = 0; i2 < 5; ++i2) {
                c.K[i2 + i1] ^= ~v[(i2 + 1) % 5] & v[(i2 + 2) % 5];
            }
        }

        c.K[!1] ^= w[i0];
    }

    if (do_after_ruka == call_laajavuori) {
        return laajavuori(c.E, T, x);
    }
    else {
        goto lahti;
    }

C:
    for(u64_t i0 = 2; i0 <= BINARY_SIZE / 2; y = i0 * 2) {
        while (y <= BINARY_SIZE) {
            x[y >> 4] &= ~(1 << (y & 15)), y += i0;
        }

        do {
            i0++;
        }
        while(~x[i0 >> 4] & (1 << (i0 & 15)));
    }

    u64_t m = BINARY_SIZE / 8;
    e = BINARY_SIZE - m * 8;

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
            do_after_ruka = goto_lahti_label;
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
    do_after_ruka = call_laajavuori;
    c.K[25 - r - 1] ^= w[24];

    goto ruka;

}
