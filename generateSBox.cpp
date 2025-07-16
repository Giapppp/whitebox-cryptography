// generateSBox.cpp - White-box S-Box and master key generator
//
// Generates a random master key and derives a white-box S-Box using the SPN key schedule and AES S-Box.
#include <iostream>
#include <fstream>
#include <random>

#include "shake128.h"
#include "constant.h"

using namespace std;

void key_schedule(  
    unsigned char master_key[16], 
    unsigned char round_key[R_n + 1]) 
{
    vector<unsigned char> master_key_vec;
    vector<unsigned char> round_key_vec;

    master_key_vec.assign(master_key, master_key + 16);
    shake128(master_key_vec, R_n + 1, round_key_vec);
    copy(round_key_vec.begin(), round_key_vec.end(), round_key);
}

int generate_key(unsigned char master_key[16]) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned char> dis(0, 255);

    for (int i = 0; i < 16; i++) {
        master_key[i] = dis(gen);
    }

    ofstream key_file("master_key.bin", ios::binary);
    if (!key_file) {
        cerr << "Error opening file for writing." << endl;
        return -1;
    }
    key_file.write(reinterpret_cast<char*>(master_key), 16);
    key_file.close();

    return 0;
}

int main() {
    unsigned char master_key[16];
    if (generate_key(master_key) != 0) {
        return -1;
    }

    unsigned char round_key[R_n + 1];
    key_schedule(master_key, round_key);

    unsigned char WB_SBOX[256] = {0};
    for (int i = 0; i < 256; i++) {
        WB_SBOX[i] = i ^ round_key[0];
    }

    for (int r = 1; r < R_n + 1; r++) {
        for (int i = 0; i < 256; i++) {
            WB_SBOX[i] = SBOX[WB_SBOX[i]] ^ round_key[r];
        }
    }
    ofstream sbox_file("WB_SBOX.bin", ios::binary);
    if (!sbox_file) {
        cerr << "Error opening file for writing." << endl;
        return -1;
    }
    sbox_file.write(reinterpret_cast<char*>(WB_SBOX), 256);
    sbox_file.close();
    cout << "S-Box generated and saved to sbox.bin" << endl;
    return 0;
}
