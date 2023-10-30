#ifndef _DEFINES_H
#define _DEFINES_H

#include "logger.h"
#include <assert.h>

/* UNSIGNED INT TYPES. */

// 8-bit integer
typedef unsigned char u8;

// 16-bit integer
typedef unsigned short u16;

// 32-bit integer
typedef unsigned int u32;

// 64-bit integer
typedef unsigned long long u64;

/* SIGNED INT TYPES. */

// 8-bit integer
typedef signed char i8;

// 16-bit integer
typedef signed short i16;

// 32-bit integer
typedef signed int i32;

// 64-bit integer
typedef signed long long i64;

/* FLOATING POINT TYPES */

// 32-bit floating point number
typedef float f32;

// 64-bit floating point number
typedef double f64;

// Assert u8 to be 1 byte.
static_assert(sizeof(u8) == 1, "Expected u8 to be 1 byte.");

// Assert u16 to be 2 bytes.
static_assert(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");

// Assert u32 to be 4 bytes.
static_assert(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");

// Assert u64 to be 8 bytes.
static_assert(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

// Assert i8 to be 1 byte.
static_assert(sizeof(i8) == 1, "Expected i8 to be 1 byte.");

// Assert i16 to be 2 bytes.
static_assert(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");

// Assert i32 to be 4 bytes.
static_assert(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");

// Assert i64 to be 8 bytes.
static_assert(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

// Assert f32 to be 4 bytes.
static_assert(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");

// Assert f64 to be 8 bytes.
static_assert(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

/**
 * Gets number of arguments when using the __VA_ARGS__ macro
 **/

#define NUMARGS(type, ...) (sizeof((type[]){0.0f, ##__VA_ARGS__}) / sizeof(type) - 1)

/**
 * Gets the number of bytes from amount of gibibytes (GiB) (1024*1024*1024)
 **/

#define GIBIBYTES(amount) ((u64)(amount) * 1024ULL * 1024ULL * 1024ULL)

/**
 * Gets the number of bytes from amount of mebibytes (GiB) (1024*1024*1024)
 **/

#define MEBIBYTES(amount) ((u64)(amount) * 1024ULL * 1024ULL)

/**
 * Gets the number of bytes from amount of kibibytes (GiB) (1024*1024*1024)
 **/

#define KIBIBYTES(amount) ((u64)(amount) * 1024ULL)

/**
 * Gets the number of bytes from amount of gigabytes (GB) (1000*1000*1000)
 **/

#define GIGABYTES(amount) ((u64)(amount) * 1000ULL * 1000ULL * 1000ULL)

/**
 * Gets the number of bytes from amount of megabytes (GB) (1000*1000*1000)
 **/

#define MEGABYTES(amount) ((u64)(amount) * 1000ULL * 1000ULL)

/**
 * Gets the number of bytes from amount of kilobytes (GB) (1000*1000*1000)
 **/

#define KILOBYTES(amount) ((u64)(amount) * 1000ULL)

#endif
