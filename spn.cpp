// spn.cpp - Substitution-Permutation Network (SPN) block cipher implementation
//
// Implements the core SPN round functions and key schedule for whitebox cryptography.
#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include "shake128.h"
#include "constant.h"

using namespace std;

// Key schedule: derive round keys from the master key using SHAKE128
void key_schedule(unsigned char master_key[16], unsigned char round_key[R_n + 1]) {
    vector<unsigned char> master_key_vec;
    vector<unsigned char> round_key_vec;
    master_key_vec.assign(master_key, master_key + 16);
    shake128(master_key_vec, R_n + 1, round_key_vec);
    copy(round_key_vec.begin(), round_key_vec.end(), round_key);
}

// Gamma: S-Box and key mixing layer
void gamma(unsigned char state[t], unsigned char master_key[t]) {
    unsigned char round_key[R_n + 1];
    key_schedule(master_key, round_key);
    for (int i = 0; i < t; i++) {
        state[i] ^= round_key[0];
    }
    for (int r = 1; r < R_n + 1; r++) {
        for (int i = 0; i < t; i++) {
            state[i] = SBOX[state[i]] ^ round_key[r];
        }
    }
}

// Theta: Linear diffusion layer
void theta(unsigned char state[t]) {
    unsigned char new_state[t] = {0};
    for (int j = 0; j < t; j++) {
        for (int i = 0; i < t; i++) {
            new_state[j] ^= GF_MUL[i ^ j][state[i]];
        }
    }
    // Copy new_state back to state
    for (int i = 0; i < t; i++) {
        state[i] = new_state[i];
    }
}

// Sigma: Round constant addition
void sigma(unsigned char state[t], unsigned char r) {
    for (int i = 0; i < t; i++) {
        state[i] ^= (r - 1) * t + i + 1;
    }
}

// Example usage of the SPN (for testing)
void example(unsigned char key[16], unsigned char state[16]) {
    srand(1);
    for (int i = 0; i < 16; i++) {
        key[i] = rand() % 256;
        state[i] = rand() % 256;
    }
    for (int rr = 0; rr < R; rr++) {
        gamma(state, key);
        theta(state);
        sigma(state, rr);
    }
}