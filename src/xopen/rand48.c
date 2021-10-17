/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2021  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct drand48_data __seed48 = { { 0, 0, 0 }, { 0xe66d, 0xdeec, 0x5, 0xb } };

uint64_t __rand48_step(unsigned short xi[3], unsigned short lc[4])
{
    uint64_t a, x;
    x = xi[0] | (xi[1] + 0U) << 16 | (xi[2] + 0ULL) << 32;
    a = lc[0] | (lc[1] + 0U) << 16 | (lc[2] + 0ULL) << 32;
    x = a * x + lc[3];
    xi[0] = x;
    xi[1] = x >> 16;
    xi[2] = x >> 32;
    return x & 0xffffffffffffull;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Initalization for mrand48 method
int lcong48_r(unsigned short int seed16v[7],  struct drand48_data *buffer)
{
    memcpy(buffer, seed16v, sizeof(struct drand48_data));
    return 0;
}

void lcong48(unsigned short seed16v[7])
{
    lcong48_r(seed16v, &__seed48);
}

// Initialization for lrand48 method
int seed48_r(unsigned short int seed16v[3], struct drand48_data *buffer)
{
    memcpy(buffer, seed16v, sizeof(*seed16v));
    return 0;
}

unsigned short *seed48(unsigned short seed16v[3])
{
    static unsigned short p[3];
    memcpy(p, &__seed48, sizeof p);
    memcpy(&__seed48, seed16v, sizeof p);
    return p;
}

// Initialization for drand48 method
int srand48_r(long int seed, struct drand48_data *buffer)
{
    return seed48_r((unsigned short [3]) {
        0x330e, seed, seed >> 16
    }, buffer);

}

void srand48(long seed)
{
    seed48((unsigned short [3]) {
        0x330e, seed, seed >> 16
    });
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int erand48_r(unsigned short int xsubi[3], struct drand48_data *restrict buffer, double *restrict result)
{
    union {
        uint64_t u;
        double f;
    } x = { 0x3ff0000000000000ULL | __rand48_step(xsubi, buffer->__seed48d) << 4 };
    *result = x.f - 1.0;
    return 0;
}

double erand48(unsigned short int xsubi[3])
{
    double result;
    erand48_r(xsubi, &__seed48, &result);
    return result;
}

int drand48_r(struct drand48_data *restrict buffer, double *restrict result)
{
    return erand48_r(buffer->__seed48i, buffer, result);
}

double drand48(void)
{
    double result;
    erand48_r(__seed48.__seed48i, &__seed48, &result);
    return result;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int nrand48_r(unsigned short int xsubi[3], struct drand48_data *restrict buffer,  long int *restrict result)
{
    *result = __rand48_step(xsubi, buffer->__seed48d) >> 17;
    return 0;
}

long nrand48(unsigned short xsubi[3])
{
    long result;
    nrand48_r(xsubi, &__seed48, &result);
    return result;
}

int lrand48_r(struct drand48_data *restrict buffer, long int *restrict result)
{
    return nrand48_r(buffer->__seed48i, buffer, result);
}

long lrand48(void)
{
    return nrand48(__seed48.__seed48d);
}

int jrand48_r(unsigned short int xsubi[3], struct drand48_data *restrict buffer, long int *restrict result)
{
    *result = __rand48_step(xsubi, __seed48.__seed48d) >> 16;
    return 0;
}

long jrand48(unsigned short xsubi[3])
{
    long result;
    jrand48_r(xsubi, &__seed48, &result);
    return result;
}

int mrand48_r(struct drand48_data *restrict buffer, long int *restrict result)
{
    return jrand48_r(buffer->__seed48i, buffer, result);
}

long mrand48(void)
{
    return jrand48(__seed48.__seed48d);
}
