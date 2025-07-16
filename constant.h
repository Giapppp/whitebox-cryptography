#pragma once
// constant.h - Global constants and lookup tables for whitebox SPN
//
// Defines round counts, block/key sizes, and declares S-Box and Galois Field tables.

constexpr unsigned char R = 10;      // Number of rounds for white-box SPN
constexpr unsigned char R_n = 64;    // Number of rounds for key schedule
constexpr unsigned char n_in = 8;    // Input size per S-Box
constexpr unsigned char n = 128;     // Block size in bits
constexpr unsigned char k = 128;     // Key size in bits
constexpr unsigned char t = n / n_in;// Number of S-Boxes per block

// AES S-Box and its inverse (256 elements each)
extern const unsigned char SBOX[256];
extern const unsigned char SBOX_INV[256];
// Galois Field multiplication table for MixColumns-like operation
extern const unsigned char GF_MUL[16][256];