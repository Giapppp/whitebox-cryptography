// WBspn.cpp - Main executable for white-box SPN encryption/decryption
//
// Loads the white-box S-Box, performs file encryption and decryption using the white-box SPN block cipher.
#include <iostream>
#include <fstream>
#include <vector> // Added for vector
#include <iterator> // Added for istreambuf_iterator

using namespace std;

#include "spn.h"
#include "constant.h"
#include "shake128.h"

unsigned char WB_SBOX[256] = {0};
unsigned char WB_SBOX_INV[256] = {0};

void WBgamma(
    unsigned char state[t],
    unsigned char sbox[256]
)
{
    for (int i = 0; i < t; i++) {
        state[i] = sbox[state[i]];
    }
}

int encrypt_block(unsigned char state[t]) {
    for (int rr = 1; rr <= R; rr++) {
        WBgamma(state, WB_SBOX);
        theta(state); 
        sigma(state, rr);
    }
    return 0;
}

int decrypt_block(unsigned char state[t]) {
    for (int rr = R; rr >= 1; rr--) {
        sigma(state, rr);
        theta(state);
        WBgamma(state, WB_SBOX_INV);
    }
    return 0;
}

int encrypt(string plaintext_file, string ciphertext_file) {
    // Open plaintext file for reading
    ifstream infile(plaintext_file, ios::binary);
    if (!infile) {
        cerr << "Error opening plaintext file." << endl;
        return 1;
    }
    // Read all bytes into a vector
    vector<unsigned char> plaintext((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    infile.close();

    // Pad plaintext to a multiple of t
    size_t orig_size = plaintext.size();
    size_t pad_len = t - (orig_size % t);
    if (pad_len != t) {
        plaintext.insert(plaintext.end(), pad_len, 0);
    }

    // Generate vector of ciphertext
    vector<unsigned char> ciphertext(plaintext.size(), 0);

    // Encrypt each block
    for (size_t i = 0; i < plaintext.size(); i += t) {
        unsigned char block[t];
        for (int j = 0; j < t; ++j) block[j] = plaintext[i + j];
        if (encrypt_block(block) != 0) {
            cerr << "Encryption failed for block at offset " << i << endl;
            return 1;
        }
        // Copy encrypted block to ciphertext
        for (int j = 0; j < t; ++j) ciphertext[i + j] = block[j];
    }
    // Write ciphertext to file
    ofstream outfile(ciphertext_file, ios::binary);
    if (!outfile) {
        cerr << "Error opening ciphertext file for writing." << endl;
        return 1;
    }
    outfile.write(reinterpret_cast<const char*>(ciphertext.data()), ciphertext.size());
    if (!outfile) {
        cerr << "Error writing to ciphertext file." << endl;
        return 1;
    }
    outfile.close();
    return 0;
}

int decrypt(string ciphertext_file, string plaintext_file) {
    // Open ciphertext file for reading
    ifstream infile(ciphertext_file, ios::binary);
    if (!infile) {
        cerr << "Error opening ciphertext file." << endl;
        return 1;
    }
    // Read all bytes into a vector
    vector<unsigned char> ciphertext((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    infile.close();
    
    // Generate vector of plaintext
    vector<unsigned char> plaintext(ciphertext.size(), 0);

    // Decrypt each block
    for (size_t i = 0; i < ciphertext.size(); i += t) {
        unsigned char block[t];
        for (int j = 0; j < t; ++j) block[j] = ciphertext[i + j];
        if (decrypt_block(block) != 0) {
            cerr << "Decryption failed for block at offset " << i << endl;
            return 1;
        }
        // Copy decrypted block to plaintext
        for (int j = 0; j < t; ++j) plaintext[i + j] = block[j];
    }
    // Write plaintext to file
    ofstream outfile(plaintext_file, ios::binary);
    if (!outfile) {
        cerr << "Error opening plaintext file for writing." << endl;
        return 1;
    }
    outfile.write(reinterpret_cast<const char*>(plaintext.data()), plaintext.size());
    if (!outfile) {
        cerr << "Error writing to plaintext file." << endl;
        return 1;
    }
    outfile.close();
    return 0;
}

void print_usage(const char* prog_name) {
    cerr << "Usage: " << prog_name << " <mode> <input_file> <output_file>" << endl;
    cerr << "  mode: 'encrypt' or 'decrypt'" << endl;
}

int main(int argc, char* argv[]) {
    // 1. Validate argument count
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    // 2. Load the white-box S-box table
    ifstream sbox_file("WB_SBOX.bin", ios::binary);
    if (!sbox_file) {
        cerr << "Error: S-Box table 'WB_SBOX.bin' not found." << endl;
        return 1;
    }
    sbox_file.read(reinterpret_cast<char*>(WB_SBOX), 256);
    // Check that all 256 bytes were successfully read
    if (sbox_file.gcount() != 256) {
        cerr << "Error: S-Box table 'WB_SBOX.bin' is incomplete." << endl;
        sbox_file.close();
        return 1;
    }
    sbox_file.close();

    // 3. Programmatically create the inverse S-Box for decryption
    for (int i = 0; i < 256; i++) {
        WB_SBOX_INV[WB_SBOX[i]] = i;
    }
    
    // 4. Parse arguments and execute the requested mode
    string mode = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];
    int result = 1; // Default to error

    if (mode == "encrypt") {
        cout << "Encrypting '" << input_file << "' to '" << output_file << "'..." << endl;
        result = encrypt(input_file, output_file);
        if (result == 0) {
            cout << "Encryption successful." << endl;
        } else {
            cerr << "Encryption failed." << endl;
        }
    } else if (mode == "decrypt") {
        cout << "Decrypting '" << input_file << "' to '" << output_file << "'..." << endl;
        result = decrypt(input_file, output_file);
        if (result == 0) {
            cout << "Decryption successful." << endl;
        } else {
            cerr << "Decryption failed." << endl;
        }
    } else {
        cerr << "Error: Invalid mode '" << mode << "'." << endl;
        print_usage(argv[0]);
        return 1;
    }

    return result;
}