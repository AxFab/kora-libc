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
#ifndef __COMPLEX_H
#define __COMPLEX_H 1

#include <bits/cdefs.h>

#ifndef __C99
# define  __STDC_NO_COMPLEX__  1
#else

#define complex  _Complex
#define imaginary _Imaginary

#define _Complex_I  (0.0f+1.0fi)

#if defined(_Imaginary_I)
# define I _Imaginary_I
#else
# define I _Complex_I
#endif

#define __CPX(n)  \
    double complex n(double complex z); \
    float complex n ## f(float complex z); \
    long double complex n ## l(long double complex z);

#if defined __C11
#define __CMPLX(x, y, t)  ((t complex)((t)(x) + I * (t)(y)))
#define CMPLX(x, y)  __CMPLX(x, y, double)
#define CMPLXF(x, y)  __CMPLX(x, y, float)
#define CMPLXL(x, y)  __CMPLX(x, y, long double)
#endif

__STDC_GUARD

// Trigonometric functions
__CPX(cacos)
__CPX(casin)
__CPX(catan)
__CPX(ccos)
__CPX(csin)
__CPX(ctan)

// Hyperbolic functions
__CPX(cacosh)
__CPX(casinh)
__CPX(catanh)
__CPX(ccosh)
__CPX(csinh)
__CPX(ctanh)

// Exponential and logarithmic functions
__CPX(cexp)
__CPX(clog)

// Power and absolute-value functions
__CPX(cabs)
__CPX(cpow)
__CPX(csqrt)

// Manipulation functions
__CPX(carg)
__CPX(cimag)
__CPX(conj)
__CPX(cproj)
__CPX(creal)

__STDC_END

#if !defined __cplusplus
#define __CGET(x, t, i)  \
    (+(union { _Complex t __z; t __xy[2]; }){(_Complex t)(x)}.__xy[i])
#define creal(x) __CGET(x, double, 0)
#define crealf(x) __CGET(x, float, 0)
#define creall(x) __CGET(x, long double, 0)
#define cimag(x) __CGET(x, double, 1)
#define cimagf(x) __CGET(x, float, 1)
#define cimagl(x) __CGET(x, long double, 1)
#endif


#endif  /* __STDC_*__ */

#endif  /* __COMPLEX_H */
