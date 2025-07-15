// filepath: shake128.h
#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>

int index(int x, int y);
uint64_t rot64L(uint64_t ac, int l);
uint64_t rot64R(uint64_t ac, int l);
void print_state(uint64_t* A);
void theta(uint64_t* A);
void rho(uint64_t* A);
void pi(uint64_t* A);
void chi(uint64_t* A);
uint64_t rc(int t);
void iota(uint64_t* A, int ir);
void rnd(uint64_t* A, int ir);
void Keccakp(int nr, std::vector<u_char>& S);
void pad0star_1(int x, int m, std::vector<u_char>& out);
void sponge(std::vector<u_char>& N, int d_in_bytes, int r, std::vector<u_char>& out);
void keccak(int c, std::vector<u_char>& S, int d, std::vector<u_char>& out);
void shake128(std::vector<u_char> in, int d, std::vector<u_char>& out);