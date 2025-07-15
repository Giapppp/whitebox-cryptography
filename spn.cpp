#include <iostream>
#include <iterator>
#include <vector>
#include <random>

#include "shake128.h"
#include "constant.h"

using namespace std;

void key_schedule(  
    u_char master_key[16], 
    u_char round_key[R_n + 1]) 
{
    vector<u_char> master_key_vec;
    vector<u_char> round_key_vec;

    master_key_vec.assign(master_key, master_key + 16);
    shake128(master_key_vec, R_n + 1, round_key_vec);
    copy(round_key_vec.begin(), round_key_vec.end(), round_key);
}

void gamma( 
    u_char state[t],        
    u_char master_key[t])
{
    u_char round_key[R_n + 1];
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

void theta( 
    u_char state[t])
{
    u_char new_state[t] = {0};
    for (int j = 0; j < t; j++) {
        for (int i = 0; i < t; i++) {
            new_state[j] ^= GF_MUL[i ^ j][state[i]]; 
        }
    }
    state = new_state;
}

void sigma(
    u_char state[t],
    u_char r
)
{
    for (int i = 0; i <= t; i++) {
        state[i] ^= (r - 1) * t + i + 1;
    }
}

int main() {
    u_char key[16];
    u_char state[16];
    srand(1);
    for (int i = 0; i < 16; i++) {key[i] = rand() % 256; state[i] = rand() % 256; }
    for (int rr = 0; rr < R; rr++) {
        gamma(state, key);
        theta(state);
        sigma(state, rr);
    }

}