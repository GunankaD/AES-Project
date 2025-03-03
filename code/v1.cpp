#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<unsigned char>> Matrix;

// Substitute bytes using s_box
const unsigned char s_box[16][16] = {
    // ... (fill in with actual s_box values from your image)
};

// Key scheduling constants and method
const unsigned char rcon[10] = {
    // ... (fill in with actual Rcon values)
};

void substituteBytes(Matrix &state) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = s_box[state[i][j] >> 4][state[i][j] & 0x0F];
        }
    }
}

void shiftRows(Matrix &state) {
    for (int i = 1; i < 4; ++i) {
        rotate(state[i].begin(), state[i].begin() + i, state[i].end());
    }
}

void mixColumns(Matrix &state) {
    // Implement your MixColumns transformation here
    // Example matrix multiplication by a fixed matrix for AES
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
    // Implement your key scheduling algorithm here
    return roundKey;
}

Matrix stringToMatrix(const string &input) {
    Matrix matrix(4, vector<unsigned char>(4));
    for (int i = 0; i < 16; ++i) {
        matrix[i % 4][i / 4] = input[i];
    }
    return matrix;
}

string matrixToString(const Matrix &matrix) {
    string output;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            output += matrix[j][i];
        }
    }
    return output;
}

void encrypt(Matrix &state, const Matrix &key) {
    Matrix roundKey = key;
    addRoundKey(state, roundKey);

    for (int round = 1; round <= 10; ++round) {
        substituteBytes(state);
        shiftRows(state);
        if (round < 10) {
            mixColumns(state);
        }
        roundKey = keySchedule(roundKey, round);
        addRoundKey(state, roundKey);
    }
}

void decrypt(Matrix &state, const Matrix &key) {
    // Implement decryption
}

int main() {
    cout << "AES-128 Encryption and Decryption Program\n";
    cout << "1. Encrypt\n2. Decrypt\nChoose an option: ";
    int choice;
    cin >> choice;

    string input, keyInput;
    cout << "Enter 16-byte input (plaintext or ciphertext): ";
    cin >> input;
    cout << "Enter 16-byte key: ";
    cin >> keyInput;

    Matrix state = stringToMatrix(input);
    Matrix key = stringToMatrix(keyInput);

    if (choice == 1) {
        encrypt(state, key);
        cout << "Encrypted ciphertext: " << matrixToString(state) << endl;
    } else if (choice == 2) {
        decrypt(state, key);
        cout << "Decrypted plaintext: " << matrixToString(state) << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
