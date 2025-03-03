#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<unsigned char>> Matrix;

unsigned char inv_s_box[16][16] = {
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};

// Substitute bytes using s_box
const unsigned char s_box[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

// Key scheduling constants (Rcon)
const unsigned char rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

void substituteBytes(Matrix &state, const unsigned char s_box[16][16]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = s_box[state[i][j] >> 4][state[i][j] & 0x0F];
        }
    }
}

void invSubstituteBytes(Matrix &state, const unsigned char inv_s_box[16][16]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = inv_s_box[state[i][j] >> 4][state[i][j] & 0x0F];
        }
    }
}

void shiftRows(Matrix &state) {
    for (int i = 1; i < 4; ++i) {
        rotate(state[i].begin(), state[i].begin() + i, state[i].end());
    }
}

void invShiftRows(Matrix &state) {
    for (int i = 1; i < 4; ++i) {
        rotate(state[i].rbegin(), state[i].rbegin() + i, state[i].rend());
    }
}

void mixColumns(Matrix &state) {
    Matrix temp = state;
    for (int c = 0; c < 4; ++c) {
        state[0][c] = (unsigned char)(0x02 * temp[0][c] ^ 0x03 * temp[1][c] ^ temp[2][c] ^ temp[3][c]);
        state[1][c] = (unsigned char)(temp[0][c] ^ 0x02 * temp[1][c] ^ 0x03 * temp[2][c] ^ temp[3][c]);
        state[2][c] = (unsigned char)(temp[0][c] ^ temp[1][c] ^ 0x02 * temp[2][c] ^ 0x03 * temp[3][c]);
        state[3][c] = (unsigned char)(0x03 * temp[0][c] ^ temp[1][c] ^ temp[2][c] ^ 0x02 * temp[3][c]);
    }
}

void invMixColumns(Matrix &state) {
    Matrix temp = state;
    for (int c = 0; c < 4; ++c) {
        state[0][c] = (unsigned char)(0x0e * temp[0][c] ^ 0x0b * temp[1][c] ^ 0x0d * temp[2][c] ^ 0x09 * temp[3][c]);
        state[1][c] = (unsigned char)(0x09 * temp[0][c] ^ 0x0e * temp[1][c] ^ 0x0b * temp[2][c] ^ 0x0d * temp[3][c]);
        state[2][c] = (unsigned char)(0x0d * temp[0][c] ^ 0x09 * temp[1][c] ^ 0x0e * temp[2][c] ^ 0x0b * temp[3][c]);
        state[3][c] = (unsigned char)(0x0b * temp[0][c] ^ 0x0d * temp[1][c] ^ 0x09 * temp[2][c] ^ 0x0e * temp[3][c]);
    }
}

void addRoundKey(Matrix &state, const Matrix &key) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] ^= key[i][j];
        }
    }
}

Matrix keySchedule(const Matrix &key, int round) {
    Matrix roundKey = key;
    unsigned char temp[4];

    // Copy the last column
    for (int i = 0; i < 4; ++i) {
        temp[i] = roundKey[i][3];
    }

    // Rotate last column (1-byte circular left shift)
    unsigned char firstByte = temp[0];
    for (int i = 0; i < 3; ++i) {
        temp[i] = temp[i + 1];
    }
    temp[3] = firstByte;

    // Substitute using s_box
    for (int i = 0; i < 4; ++i) {
        temp[i] = s_box[temp[i] >> 4][temp[i] & 0x0F];
    }

    // XOR with Rcon for the first byte
    temp[0] ^= rcon[round - 1];

    // Generate new round key
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (j == 0) {
                roundKey[i][j] ^= temp[i];
            } else {
                roundKey[i][j] ^= roundKey[i][j - 1];
            }
        }
    }

    return roundKey;
}

void aesEncrypt(const Matrix &plaintext, const Matrix &key, const unsigned char s_box[16][16]) {
    Matrix state = plaintext;
    Matrix roundKey = key;

    addRoundKey(state, roundKey);

    for (int round = 1; round <= 10; ++round) {
        substituteBytes(state, s_box);
        shiftRows(state);
        if (round < 10) {
            mixColumns(state);
        }
        roundKey = keySchedule(roundKey, round);
        addRoundKey(state, roundKey);
    }

    // Output encrypted data
    for (const auto &row : state) {
        for (unsigned char val : row) {
            cout << hex << setw(2) << setfill('0') << (int)val << " ";
        }
        cout << endl;
    }
}

void aesDecrypt(const Matrix &ciphertext, const Matrix &key, const unsigned char s_box[16][16], const unsigned char inv_s_box[16][16]) {
    Matrix state = ciphertext;
    Matrix roundKey = key;

    vector<Matrix> roundKeys;
    roundKeys.push_back(roundKey);
    for (int round = 1; round <= 10; ++round) {
        roundKey = keySchedule(roundKey, round);
        roundKeys.push_back(roundKey);
    }

    addRoundKey(state, roundKeys[10]);

    for (int round = 9; round >= 0; --round) {
        invShiftRows(state);
        invSubstituteBytes(state, inv_s_box);
        addRoundKey(state, roundKeys[round]);
        if (round > 0) {
            invMixColumns(state);
        }
    }

    // Output decrypted data
    for (const auto &row : state) {
        for (unsigned char val : row) {
            cout << (char)val;
        }
    }
    cout << endl;
}

Matrix convertToHexMatrix(const string &input) {
    Matrix matrix(4, vector<unsigned char>(4));
    for (size_t i = 0; i < input.size(); ++i) {
        matrix[i / 4][i % 4] = static_cast<unsigned char>(input[i]);
    }
    return matrix;
}

int main() {
    cout << "AES-128 Encryption/Decryption" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Choose an option: ";
    int choice;
    cin >> choice;

    string input, keyStr;
    cout << "Enter 16-character key: ";
    cin.ignore();
    getline(cin, keyStr);
    Matrix key = convertToHexMatrix(keyStr);

    if (choice == 1) {
        cout << "Enter plaintext (16 characters): ";
        getline(cin, input);
        Matrix plaintext = convertToHexMatrix(input);

        cout << "Encrypted ciphertext: " << endl;
        aesEncrypt(plaintext, key, s_box);
    } else if (choice == 2) {
        cout << "Enter ciphertext (in hex, 32 characters): ";
        getline(cin, input);
        Matrix ciphertext = convertToHexMatrix(input);

        cout << "Decrypted plaintext: ";
        aesDecrypt(ciphertext, key, s_box, inv_s_box);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

