// shake128.h - Keccak/SHAKE128 permutation and hash interface
//
// Provides Keccak-p permutation, SHAKE128, and related utilities for key scheduling.
#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>

// Indexing and rotation helpers
int index(int x, int y);
uint64_t rot64L(uint64_t ac, int l);
uint64_t rot64R(uint64_t ac, int l);

// Keccak permutation steps
void print_state(uint64_t* A);
void theta(uint64_t* A);
void rho(uint64_t* A);
void pi(uint64_t* A);
void chi(uint64_t* A);
uint64_t rc(int t);
void iota(uint64_t* A, int ir);
void rnd(uint64_t* A, int ir);
void Keccakp(int nr, std::vector<unsigned char>& S);

// SHAKE128 and sponge construction
void pad0star_1(int x, int m, std::vector<unsigned char>& out);
void sponge(std::vector<unsigned char>& N, int d_in_bytes, int r, std::vector<unsigned char>& out);
void keccak(int c, std::vector<unsigned char>& S, int d, std::vector<unsigned char>& out);
void shake128(std::vector<unsigned char> in, int d, std::vector<unsigned char>& out);