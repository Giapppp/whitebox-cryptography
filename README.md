# Whitebox Cryptography

## Introduction

My implementation of SPNbox-8 - a whitebox block cipher and was described at https://www.iacr.org/archive/asiacrypt2016/10031190/10031190.pdf. 

## Features
- White-box S-Box and master key generation
- File encryption and decryption using a white-box SPN
- Keccak/SHAKE128-based key schedule
- AES-like S-Box and Galois Field multiplication tables

## Build Instructions

### Prerequisites
- C++17 compatible compiler (e.g., g++)

### Build
You can build all necessary binaries and generate the S-Box and master key by running:

```sh
./prepare.sh
```

This will:
- Compile `generateSBox` (for S-Box and key generation)
- Compile `WBspn` (main encryption/decryption tool)
- Run `generateSBox` to produce `master_key.bin` and `WB_SBOX.bin`

## Usage

### 1. Generate S-Box and Master Key

This is done automatically by `prepare.sh`, but you can run manually:

```sh
./generateSBox
```
- Outputs: `master_key.bin` and `WB_SBOX.bin`

### 2. Encrypt a File

```sh
./WBspn encrypt <input_plaintext_file> <output_ciphertext_file>
```

### 3. Decrypt a File

```sh
./WBspn decrypt <input_ciphertext_file> <output_plaintext_file>
```

### Notes
- The S-Box (`WB_SBOX.bin`) and master key (`master_key.bin`) must be present in the working directory for encryption/decryption.
- The block size and padding are handled automatically.

## File Structure

- `WBspn.cpp` - Main executable for file encryption/decryption using the white-box SPN
- `generateSBox.cpp` - Generates the white-box S-Box and master key
- `spn.cpp`, `spn.h` - SPN block cipher core logic
- `shake128.cpp`, `shake128.h` - Keccak/SHAKE128 implementation for key scheduling
- `constant.cpp`, `constant.h` - S-Box, inverse S-Box, and Galois Field multiplication tables
- `prepare.sh` - Build and setup script

## To-do lists
- Support SPNbox-16, SPNbox-24, SPNbox-32.
- Clean the code.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.