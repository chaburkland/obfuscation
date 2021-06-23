#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define KECCAK_ROUNDS 24
#define SHA3_KECCAK_SPONGE_WORDS (((1600)/8/*bits to byte*/)/sizeof(uint64_t))

static const unsigned int keccakf_rotc[24] = {
    1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62,
    18, 39, 61, 20, 44
};

static const unsigned int keccakf_piln[24] = {
    10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20,
    14, 22, 9, 6, 1
};

static const uint64_t keccakf_rndc[24] = {
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
};

int
determine_program_output_from_date()
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
    );
}

int
fibonacci()
{
    // Iteratively build fibonnaci
    uint64_t last = 1;
    uint64_t last_last = 1;

    for(uint64_t i = 0; i < 93; ++i) {
        printf("%lu ", last);
        uint64_t tmp = last + last_last;
        last = last_last;
        last_last = tmp;
    }

    return puts("");
}

int
bytes_to_hex(const uint8_t *checksum_bytes, uint64_t sha_output_size)
{
    for (uint64_t i = 0; i < sha_output_size; ++i) {
        uint8_t result[2] = "00";
        uint8_t byte = checksum_bytes[i];
        size_t idx = 1;

        while (byte) {
            uint64_t half_byte = byte & 0xF;

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

    for(uint64_t i = 2; i <= binary_size; ++i) {
        x[i >> 4] |= (1 << (i & 0xF));
    }

    uint64_t y = 0;
    for(uint64_t i = 2; i <= (binary_size / 2);) {
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

    // Generate all primes until (binary_size / 16)
    for (uint64_t i = 2; i <= binary_size; ++i) {
        if (x[i >> 4] & (1 << (0xF & i))) {
            printf("%lu ", i);
        }
    }
    free(x);
    return puts("");
}

uint64_t
sha3_rotl_64(uint64_t x, unsigned int y)
{
	return (x << y) | (x >> ((sizeof(uint64_t)*8) - y));
}

void
keccakf(uint64_t *state)
{
    uint64_t bc[5];
    uint64_t t;

    for(uint64_t round = KECCAK_ROUNDS; round--;) {
        /* Theta */
        for(int i = 0; i < 5; ++i) {
            bc[i] = state[i] ^ state[i + 5] ^ state[i + 10] ^ state[i + 15] ^ state[i + 20];
        }

        for(int i = 0; i < 5; ++i) {
            t = bc[(i + 4) % 5] ^ sha3_rotl_64(bc[(i + 1) % 5], 1);
            for(int j = 0; j < 25; j += 5) {
                state[i + j] ^= t;
            }
        }

        /* Rho Pi */
        t = state[1];
        for (int i = 0; i - 24; ++i) {
            uint64_t tmp_idx = keccakf_piln[i];
            bc[0] = state[tmp_idx];
            state[tmp_idx] = sha3_rotl_64(t, keccakf_rotc[i]);
            t = bc[0];
        }

        /* Chi */
        for(int i = 0; i < 25; i += 5) {
            for(int j = 0; j < 5; ++j) {
                bc[j] = state[j + i];
            }
            for(int j = 0; j < 5; ++j) {
                state[i + j] ^= ~bc[(j + 1) % 5] & bc[(j + 2) % 5];
            }
        }

        state[0] ^= keccakf_rndc[round];
    }
}

// Not fully deobfuscated yet
int
sha3_checksum(const char *fp, int binary_size, const uint8_t *binary_bytes)
{
    union sha3_context {
        uint64_t state[25];
        uint8_t checksum_bytes[1];
    } ctx;
    memset(&ctx, 0, sizeof(ctx));

    // 224, 256, 384, 512
    int sha_output_size = atoi(fp) / 8;
    const uint64_t word_capacity = sha_output_size / 4;

    int word_index = 0;
    uint64_t saved = 0;

    for (uint64_t i = 0; i < (binary_size / 8); ++i) {
        uint64_t idx = (uint64_t)-1;
        saved = 0;

        for (uint64_t j = 0; j < 8; ++j) {
            ++idx;
            saved |= (uint64_t)binary_bytes[idx] << 8 * idx;
        }

        ctx.state[word_index] ^= saved;

        if (++word_index == SHA3_KECCAK_SPONGE_WORDS - word_capacity) {
            keccakf(ctx.state);
            word_index = 0;
        }

        binary_bytes += 8;
    }

    ctx.state[word_index] ^= 6;
    ctx.state[24 - word_capacity] ^= 9223372036854775808ULL;

    keccakf(ctx.state);
    return bytes_to_hex(ctx.checksum_bytes, sha_output_size);
}

int
main(int argc, char *argv[])
{
    // argv[0] = executable
    // argv[1] = some number
    // argv[2] = file_to_compute_checksum
    UNUSED(argc);

    // Map binary bytes
    int binary_fileno = open(argv[2], O_RDONLY);
    if (binary_fileno == -1) {
        printf("Cannot open '%s' for reading\n", argv[2]);
        return 1;
    }

    struct stat st;
    if (fstat(binary_fileno, &st)) {
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

    switch (determine_program_output_from_date() % 3)
    {
    case 0:
        return fibonacci();
    case 1:
        return sha3_checksum(argv[1], st.st_size, binary_bytes);
    case 2:
        return primes(st.st_size);
    }
}
