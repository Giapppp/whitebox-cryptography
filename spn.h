#pragma once
// spn.h - Substitution-Permutation Network (SPN) block cipher interface
//
// Declares the core SPN round functions and key schedule.
#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include "shake128.h"
#include "constant.h"

// Key schedule: derives round keys from the master key
void key_schedule(unsigned char master_key[16], unsigned char round_key[R_n + 1]);
// Gamma: S-Box and key mixing layer
void gamma(unsigned char state[t], unsigned char master_key[t]);
// Theta: Linear diffusion layer
void theta(unsigned char state[t]);
// Sigma: Round constant addition
void sigma(unsigned char state[t], unsigned char r);
