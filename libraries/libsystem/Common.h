#pragma once

/* Copyright © 2018-2020 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <libsystem/Macros.h>

//#define NULL ((void *)0)

#define let __auto_type const
#define var __auto_type

typedef void s0;
typedef char s8;
typedef short s16;
typedef long s32;
typedef long long s64;

typedef void u0;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef char byte;
typedef unsigned char ubyte;
typedef unsigned char uchar;
typedef unsigned short wchar;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef long off_t;

/* --- Raw memory allocation ------------------------------------------------ */

__attribute__((malloc)) __attribute__((alloc_size(1))) void *malloc(size_t size);
__attribute__((malloc)) __attribute__((alloc_size(1, 2))) void *calloc(size_t, size_t);

void *realloc(void *p, size_t size);

void free(void *);

void malloc_cleanup(void *buffer);

/* --- Loops ---------------------------------------------------------------- */

typedef enum
{
    ITERATION_CONTINUE,
    ITERATION_STOP,
} IterationDecision;