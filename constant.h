#pragma once
#include <iostream>

extern const u_char R = 10;
extern const u_char R_n = 64;
extern const u_char n_in = 8;
extern const u_char n = 128;
extern const u_char k = 128;
extern const u_char t = n / n_in;
extern const unsigned char SBOX[256];
extern const unsigned char SBOX_INV[256];
extern const unsigned char GF_MUL[t][256];