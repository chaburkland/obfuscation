#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

# define BINARY_SIZE 12952
#define UNUSED(x) (void)(x)

typedef unsigned long long u64_t;

int
determine_random_label_from_date()
{
    time_t current_time = time(NULL);
    int day = localtime(&current_time)->tm_mday;
    int month = localtime(&current_time)->tm_mon + 1;
    int year = localtime(&current_time)->tm_year + 1900;
    int offset = -2;

    if (month <= 2) {
        --year;
        offset = -1;
    }

    return (
        (23 * month / 9)
        + day
        - 45
        + year
        + offset
        + (year / 4)
        + (year / 400)
        - (year / 100)
    ) % 3;
}

int
fibonacci()
{
    // Iteratively build fibonnaci
    u64_t last = 1;
    u64_t last_last = 1;

    for(u64_t i = 0; i < 93; ++i) {
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
    for (u64_t i = 0; i < T; ++i) {
        char result[2] = {48, 48};

        u64_t s_idx = 1;

        for (u64_t j = f[i]; j ^ 0; j >>= 4) { // Always runs twice
            u64_t tmp_var = j & 0xF;
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
    for (u64_t i = 2; i <= BINARY_SIZE; ++i) {
        if (x[i >> 4] & (1 << (0xF & i))) {
            printf("%llu ", i);
        }
    }
    return puts("");
}

void
init(unsigned int *x)
{
    u64_t y = 0;
    for(u64_t i = 2; i <= (BINARY_SIZE / 2);) {
        while (y <= BINARY_SIZE) {
            x[y >> 4] &= ~(1 << (y & 0xF));
            y += i;
        }

        do {
            i++;
        }
        while(~x[i >> 4] & (1 << (i & 0xF)));

        y = i * 2;
    }
}

void
main_loop(u64_t *v, u64_t *K, u64_t t, u64_t *O, u64_t *N, u64_t *w)
{
    for(u64_t i = 24; i--;) {
        for(u64_t j = 0; j < 5; ++j) {
            v[j] = K[j] ^ K[j + 5] ^ K[j + 10] ^ K[j + 15] ^ K[j + 20];
        }
        for(u64_t j = 0; j < 5; ++j) {
            t = v[(j + 4) % 5] ^ (v[(j + 1) % 5] << 1 | v[(j + 1) % 5] >> 63);
            for(u64_t k = 0; k < 25; k += 5) {
                K[j + k] ^= t;
            }
        }
        t = K[1];
        for (u64_t j = 0; j - 24; ++j) {
            u64_t tmp_idx = O[j];
            *v = K[tmp_idx];
            K[tmp_idx] = t << N[j] | t >> (64 - N[j]);
            t = *v;
        }

        for(u64_t j = 0; j < 25; j += 5) {
            for(u64_t k = 0; k < 5; ++k) {
                v[k] = K[k + j];
            }
            for(u64_t k = 0; k < 5; ++k) {
                K[k + j] ^= ~v[(k + 1) % 5] & v[(k + 2) % 5];
            }
        }

        K[0] ^= w[i];
    }
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    // argv[0] = executable
    // argv[1] = some number
    // argv[2] = compiled_binary
    union ULL_Union {
        u64_t K[25];
        unsigned char E[1];
    } c;

    u64_t t = 0;
    u64_t v[5];

    u64_t N[25] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62, 18, 39, 61, 20, 44};

    u64_t T = 0;
    for(u64_t i = 0; argv[1][i]; i++) {
        T = T * 10 + argv[1][i] - 48;
    }
    T >>= 3;

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

    u64_t O[25] = {10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1};

    u64_t binary_fileno = open(argv[2], O_RDONLY);
    const unsigned char *binary_bytes = mmap(NULL, BINARY_SIZE, PROT_READ, MAP_SHARED, binary_fileno, 0);
    memset(&c, 0, sizeof(u64_t)*5);

    u64_t r = T / 4;
    unsigned int x[(BINARY_SIZE / 16) + 1];
    memset(x, 0, sizeof(x[0]) * ((BINARY_SIZE / 16) + 1));

    for(u64_t i = 2; i <= BINARY_SIZE; ++i) {
        x[i >> 4] |= (1 << (i & 0xF));
    }

    init(x);
    u64_t F = 0;

    for (u64_t i = 0; i < (BINARY_SIZE / 8); ++i) {
        u64_t S = (u64_t)-1;
        t = 0;

        for (u64_t j = 0; j < 8; ++j) {
            ++S;
            t |= (u64_t)binary_bytes[S] << 8 * S;
        }

        c.K[F] ^= t;

        if (++F == 25 - r) {
            main_loop(v, c.K, t, O, N, w);
            F = !r;
        }

        binary_bytes += 8;
    }

    c.K[F] ^= 6;
    c.K[24 - r] ^= w[24];

    main_loop(v, c.K, t, O, N, w);
    return laajavuori(c.E, T, x);
}
