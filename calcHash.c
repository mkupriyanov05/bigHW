#include "calcHash.h"

int fillMessageBlock(char password[100], union messageBlock *msgBlock, enum status *state, uint64_t *numBits) {
    // Variables
    uint64_t numBytes;
    int i;

    // If we've finished padding and processing all the message blocks, exit
    if (*state == FINISH) {
        return 0;
    }

    // Handle our PAD0 and PAD1 states
    // Check if we need another block full of padding
    if (*state == PAD0 || *state == PAD1) {
        // Set the first 56 bytes to all zero bits
        for (i = 0; i < 56; i++) {
            msgBlock->e[i] = 0x00;
        }

        // Set the last 64 bits to an integer (should be big endian)
        msgBlock->s[7] = byteSwap64(*numBits);

        // Set the state to finish
        *state = FINISH;

        // If state is PAD1, set the first bit of msgBlock to 1
        if (*state == PAD1) {
            // 0x80 = 10000000
            msgBlock->e[0] = 0x80;
        }

        // keep the loop in SHA256 going for one more iteration
        return 1;
    }

    // Read bytes instead of characters
    // Read until the end of the file
    numBytes = strlen(password);

    // Keep track of the number of bytes we've read
    *numBits = *numBits + (numBytes * 8);

    if (numBytes < 56) {
        // 0x80 = 10000000
        // Add the one bit, as per the standard before padding with 0s
        msgBlock->e[numBytes] = 0x80;

        // Add 0 bits until the last 64 bits
        while (numBytes < 56) {
            // Add the index into our block
            numBytes = numBytes + 1;

            // Add enough zeroes so that there are 64 bits left at the end
            msgBlock->e[numBytes] = 0x00;
        }

        // Store the length of the file in bits as a (Should be big endian) unsigned 64 bit int
        msgBlock->s[7] = byteSwap64(*numBits);

        // Change the state of our program
        *state = FINISH;
    }
        // Otherwise, check if we can put some padding into this message block
    else if (numBytes < 64) {
        // Set the state to PAD0
        *state = PAD0;

        // 0x80 = 10000000
        // Add the one bit into the current message block
        msgBlock->e[numBytes] = 0x80;

        // Pad the rest of the message block with 0 bits
        while (numBytes < 64) {
            numBytes = numBytes + 1;
            msgBlock->e[numBytes] = 0x00;
        }
    }
}

void calculateHash(char *password)
{
    union messageBlock msgBlock;
    uint64_t numBits = 0;

    enum status state = READ;

    uint32_t K[] =
            {
                    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
                    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
                    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
                    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
                    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
                    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
                    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
                    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
                    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
            };

    // Message schedule
    uint32_t W[64];

    // Working variables
    uint32_t a, b, c, d, e, f, g, h;

    // Temp variables
    uint32_t T1;
    uint32_t T2;

    // Hash values
    // Taken from https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
    uint32_t H[8] = {
            0x6a09e667,
            0xbb67ae85,
            0x3c6ef372,
            0xa54ff53a,
            0x510e527f,
            0x9b05688c,
            0x1f83d9ab,
            0x5be0cd19
    };

    // The current message block

    // For loop to iterate through the message block
    int j;

    while(fillMessageBlock(password, &msgBlock, &state, &numBits))
    {
        for(j=0; j<16; j++)
        {
            if(endianCheck()==true)
            {
                W[j] = msgBlock.t[j];
            }
            else
            {
                // Add the current message block to our message schedule
                // Convert to big endian first
                W[j] = byteSwap32(msgBlock.t[j]);
            }

        }

        for (j=16; j<64; j++)
        {
            // Step 1
            W[j] = sig1(W[j-2]) + W[j-7] + sig0(W[j-15]) + W[j-16];
        }


        // Initalize a..h
        // Step 2
        a=H[0];
        b=H[1];
        c=H[2];
        d=H[3];
        e=H[4];
        f=H[5];
        g=H[6];
        h=H[7];

        // For loop
        // Step 3
        for(j = 0; j < 64; j++)
        {
            // Creating new variables
            T1 = h + SIG1(e) + Ch(e,f,g) + K[j] + W[j];
            T2 = SIG0(a) + Maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }

        // Step 4
        H[0] = a + H[0];
        H[1] = b + H[1];
        H[2] = c + H[2];
        H[3] = d + H[3];
        H[4] = e + H[4];
        H[5] = f + H[5];
        H[6] = g + H[6];
        H[7] = h + H[7];

    }
    char result[100] = "";
    char temp[16];
    for (int i = 0; i < 8; i++) {
        sprintf(temp, "%08llx", H[i]);
        strcat(result, temp);
    }
    strcpy(password, result);
}

// This function is used to handle the opening and reading of files

_Bool endianCheck()
{
    int num = 1 ;
    if(*(char *)&num == 1) {
        return false;
    } else {
        return true;
    }
}

uint32_t sig0(uint32_t x)
{
    // Section 3.2
    return (rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3));
};

uint32_t sig1(uint32_t x)
{
    return (rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10));
};

// Rotate bits right
uint32_t rotr(uint32_t x, uint16_t a)
{
    return (x >> a) | (x << (32 - a));
};

// Shift bits right
uint32_t shr(uint32_t x, uint16_t b)
{
    return (x >> b);
};

uint32_t SIG0(uint32_t x)
{
    return (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22));
};

uint32_t SIG1(uint32_t x)
{
    return (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25));
};

uint32_t Ch(uint32_t x,uint32_t y,uint32_t z)
{
    return ((x & y) ^ (~(x)&z));
};

uint32_t Maj(uint32_t x,uint32_t y,uint32_t z)
{
    return ((x & y) ^ (x & z) ^ (y & z));
};