#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <stdint.h>
#include <sys/stat.h>

#define UNUSED(x) (void)(x)
#define KECCAK_ROUNDS 24

typedef unsigned long long u64_t;

static const unsigned keccakf_rotc[24] = {
    1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62,
    18, 39, 61, 20, 44
};

static const unsigned keccakf_piln[24] = {
    10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20,
    14, 22, 9, 6, 1
};

// Fully de-obfuscated 06/21/2021
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

// Fully de-obfuscated 06/21/2021
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

// Fully de-obfuscated 06/22/2021
int
bytes_to_hex(const uint8_t *checksum_bytes, u64_t sha_output_size)
{
    for (u64_t i = 0; i < sha_output_size; ++i) {
        uint8_t result[2] = "00";
        uint8_t byte = checksum_bytes[i];
        size_t idx = 1;

        while (byte) {
            u64_t half_byte = byte & 0xF;

            if(half_byte < 10) {
                result[idx] = '0' + half_byte;
            } else {
                result[idx] = 'a' + half_byte - 10;
            }
            --idx;
            byte >>= 4;
        }
        printf("%s", result); // This prints 2 characters at a time
    }

    return puts("");
}

int
primes(int binary_size)
{
    // VERY fast prime implementation
    unsigned int *x = calloc((binary_size / 16) + 1, sizeof(unsigned int));

    for(u64_t i = 2; i <= binary_size; ++i) {
        x[i >> 4] |= (1 << (i & 0xF));
    }

    u64_t y = 0;
    for(u64_t i = 2; i <= (binary_size / 2);) {
        while (y <= binary_size) {
            x[y >> 4] &= ~(1 << (y & 0xF));
            y += i;
        }

        do {
            i++;
        }
        while(~x[i >> 4] & (1 << (i & 0xF)));

        y = i * 2;
    }

    // Cleaned up 06/21/2021
    // Generate all primes until (binary_size / 16)
    for (u64_t i = 2; i <= binary_size; ++i) {
        if (x[i >> 4] & (1 << (0xF & i))) {
            printf("%llu ", i);
        }
    }
    free(x);
    return puts("");
}

void
keccakf(u64_t *s, u64_t t, u64_t *w)
{
    u64_t bc[5];
    for(u64_t round = KECCAK_ROUNDS; round--;) {
        /* Theta */
        for(int i = 0; i < 5; ++i) {
            bc[i] = s[i] ^ s[i + 5] ^ s[i + 10] ^ s[i + 15] ^ s[i + 20];
        }

        for(u64_t i = 0; i < 5; ++i) {
            t = bc[(i + 4) % 5] ^ (bc[(i + 1) % 5] << 1 | bc[(i + 1) % 5] >> 63);
            for(u64_t j = 0; j < 25; j += 5) {
                s[i + j] ^= t;
            }
        }
        t = s[1];
        for (u64_t j = 0; j - 24; ++j) {
            u64_t tmp_idx = keccakf_piln[j];
            *bc = s[tmp_idx];
            s[tmp_idx] = t << keccakf_rotc[j] | t >> (64 - keccakf_rotc[j]);
            t = *bc;
        }

        for(u64_t j = 0; j < 25; j += 5) {
            for(u64_t k = 0; k < 5; ++k) {
                bc[k] = s[k + j];
            }
            for(u64_t k = 0; k < 5; ++k) {
                s[k + j] ^= ~bc[(k + 1) % 5] & bc[(k + 2) % 5];
            }
        }

        s[0] ^= w[round];
    }
}

int main(int argc, char *argv[])
{
    // argv[0] = executable
    // argv[1] = some number
    // argv[2] = compiled_binary
    UNUSED(argc);

    // Map binary bytes
    int binary_fileno = open(argv[2], O_RDONLY);
    if (binary_fileno == -1) {
        printf("Cannot open '%s' for reading\n", argv[2]);
        return 1;
    }

    struct stat st;
    if(fstat(binary_fileno, &st)) {
        close(binary_fileno);
        printf("Cannot determine size of '%s'\n", argv[2]);
        return 1;
    }

    const uint8_t *binary_bytes = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, binary_fileno, 0);
    close(binary_fileno);
    if (binary_bytes == NULL) {
        printf("Cannot memory-map '%s'\n", argv[2]);
        return 1;
    }

    // switch (determine_random_label_from_date())
    // {
    // case 0:
    //     return fibonacci();
    // case 2:
    //     return primes(st.st_size);
    // }

    // Arrays
    unsigned int _[810];
    memset(_, 0, sizeof(unsigned int) * 810); // This memset is integral to SHA. WHY???
    UNUSED(_);

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

    // Contains information need for SHA only!
    union ULL_Union {
        u64_t s[25];
        uint8_t checksum_bytes[1];
    } c;
    memset(&c, 0, sizeof(u64_t)*5);

    // 224, 256, 384, 512
    u64_t sha_output_size = atoi(argv[1]) / 8;
    const u64_t size_div_4 = sha_output_size / 4;

    u64_t F = 0;
    u64_t t = 0;

    for (u64_t i = 0; i < (st.st_size / 8); ++i) {
        u64_t S = (u64_t)-1;
        t = 0;

        for (u64_t j = 0; j < 8; ++j) {
            ++S;
            t |= (u64_t)binary_bytes[S] << 8 * S;
        }

        c.s[F] ^= t;

        if (++F == 25 - size_div_4) {
            keccakf(c.s, t, w);
            F = 0;
        }

        binary_bytes += 8;
    }

    c.s[F] ^= 6;
    c.s[24 - size_div_4] ^= w[24];

    keccakf(c.s, t, w);
    return bytes_to_hex(c.checksum_bytes, sha_output_size);
}
