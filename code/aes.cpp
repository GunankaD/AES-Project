#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<unsigned char>> Matrix;

// Key scheduling constants (Rcon)
const unsigned char rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

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

// GF(2^8) multiplication function
unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for(counter = 0; counter < 8; counter++) {
        if((b & 1) != 0) {
            p ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if(hi_bit_set != 0) {
            a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */
        }
        b >>= 1;
    }
    return p;
}

void mixColumns(Matrix &state) {
    Matrix temp = state;
    for (int c = 0; c < 4; ++c) {
        state[0][c] = gmul(0x02, temp[0][c]) ^ gmul(0x03, temp[1][c]) ^ temp[2][c] ^ temp[3][c];
        state[1][c] = temp[0][c] ^ gmul(0x02, temp[1][c]) ^ gmul(0x03, temp[2][c]) ^ temp[3][c];
        state[2][c] = temp[0][c] ^ temp[1][c] ^ gmul(0x02, temp[2][c]) ^ gmul(0x03, temp[3][c]);
        state[3][c] = gmul(0x03, temp[0][c]) ^ temp[1][c] ^ temp[2][c] ^ gmul(0x02, temp[3][c]);
    }
}

void invMixColumns(Matrix &state) {
    Matrix temp = state;
    for (int c = 0; c < 4; ++c) {
        state[0][c] = gmul(0x0e, temp[0][c]) ^ gmul(0x0b, temp[1][c]) ^ gmul(0x0d, temp[2][c]) ^ gmul(0x09, temp[3][c]);
        state[1][c] = gmul(0x09, temp[0][c]) ^ gmul(0x0e, temp[1][c]) ^ gmul(0x0b, temp[2][c]) ^ gmul(0x0d, temp[3][c]);
        state[2][c] = gmul(0x0d, temp[0][c]) ^ gmul(0x09, temp[1][c]) ^ gmul(0x0e, temp[2][c]) ^ gmul(0x0b, temp[3][c]);
        state[3][c] = gmul(0x0b, temp[0][c]) ^ gmul(0x0d, temp[1][c]) ^ gmul(0x09, temp[2][c]) ^ gmul(0x0e, temp[3][c]);
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

void aesEncrypt(const Matrix &plaintext, const Matrix &key, const unsigned char s_box[16][16], Matrix &output) {
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

    output = state;

    // // Output encrypted data in hex format
    // for (const auto &row : state) {
    //     for (unsigned char val : row) {
    //         cout << hex << setw(2) << setfill('0') << (int)val;
    //     }
    // }
    // cout << endl;
}

void aesDecrypt(const Matrix &ciphertext, const Matrix &key, const unsigned char s_box[16][16], 
                const unsigned char inv_s_box[16][16], Matrix &output) {
    Matrix state = ciphertext;
    Matrix roundKey = key;

    // Generate all round keys first
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

    output = state;

    // // Output decrypted data
    // for (const auto &row : state) {
    //     for (unsigned char val : row) {
    //         cout << (char)val;
    //     }
    // }
    // cout << endl;
}

// Add padding functions
vector<unsigned char> pkcs7Padding(const string &input) {
    const int blockSize = 16;
    int paddingLength = blockSize - (input.length() % blockSize);
    if (paddingLength == 0) {
        paddingLength = blockSize;
    }
    
    vector<unsigned char> padded(input.begin(), input.end());
    for (int i = 0; i < paddingLength; i++) {
        padded.push_back(paddingLength);
    }
    return padded;
}

string removePadding(const vector<unsigned char> &paddedData) {
    if (paddedData.empty()) return "";
    
    unsigned char lastByte = paddedData.back();
    int paddingLength = static_cast<int>(lastByte);
    
    if (paddingLength > paddedData.size() || paddingLength == 0) {
        return string(paddedData.begin(), paddedData.end());
    }
    
    // Verify padding
    for (int i = 1; i <= paddingLength; i++) {
        if (paddedData[paddedData.size() - i] != paddingLength) {
            return string(paddedData.begin(), paddedData.end());
        }
    }
    
    return string(paddedData.begin(), paddedData.end() - paddingLength);
}

vector<Matrix> splitIntoBlocks(const vector<unsigned char> &data) {
    vector<Matrix> blocks;
    for (size_t i = 0; i < data.size(); i += 16) {
        Matrix block(4, vector<unsigned char>(4));
        for (int j = 0; j < 16 && (i + j) < data.size(); j++) {
            block[j / 4][j % 4] = data[i + j];
        }
        blocks.push_back(block);
    }
    return blocks;
}

vector<unsigned char> matrixToVector(const Matrix &matrix) {
    vector<unsigned char> result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.push_back(matrix[i][j]);
        }
    }
    return result;
}
Matrix convertToHexMatrix(const string &input) {
    Matrix matrix(4, vector<unsigned char>(4));
    for (size_t i = 0; i < min(input.size(), size_t(16)); ++i) {
        matrix[i / 4][i % 4] = static_cast<unsigned char>(input[i]);
    }
    // Pad with zeros if input is less than 16 characters
    for (size_t i = input.size(); i < 16; ++i) {
        matrix[i / 4][i % 4] = 0;
    }
    return matrix;
}

Matrix hexStringToMatrix(const string &hexString) {
    Matrix matrix(4, vector<unsigned char>(4));
    for (size_t i = 0; i < min(hexString.length(), size_t(32)); i += 2) {
        unsigned char byte = stoi(hexString.substr(i, 2), nullptr, 16);
        matrix[i/8][(i/2)%4] = byte;
    }
    return matrix;
}

string matrixToHexString(const Matrix &matrix) {
    stringstream ss;
    for (const auto &row : matrix) {
        for (unsigned char val : row) {
            ss << hex << setw(2) << setfill('0') << (int)val;
        }
    }
    return ss.str();
}

string encryptAES(const string &plaintext, const Matrix &key, const unsigned char s_box[16][16]) {
    // Pad the input
    vector<unsigned char> paddedData = pkcs7Padding(plaintext);
    
    // Split into blocks
    vector<Matrix> blocks = splitIntoBlocks(paddedData);
    
    // Encrypt each block
    stringstream ciphertext;
    for (auto &block : blocks) {
        Matrix encryptedBlock(4, vector<unsigned char>(4));
        aesEncrypt(block, key, s_box, encryptedBlock);
        
        // Convert to hex
        for (const auto &row : encryptedBlock) {
            for (unsigned char val : row) {
                ciphertext << hex << setw(2) << setfill('0') << (int)val;
            }
        }
    }
    
    return ciphertext.str();
}

string decryptAES(const string &ciphertext, const Matrix &key, const unsigned char s_box[16][16], 
                  const unsigned char inv_s_box[16][16]) {
    // Convert hex string to blocks
    vector<Matrix> blocks;
    for (size_t i = 0; i < ciphertext.length(); i += 32) {
        string blockHex = ciphertext.substr(i, 32);
        blocks.push_back(hexStringToMatrix(blockHex));
    }
    
    // Decrypt each block
    vector<unsigned char> decryptedData;
    for (auto &block : blocks) {
        Matrix decryptedBlock(4, vector<unsigned char>(4));
        aesDecrypt(block, key, s_box, inv_s_box, decryptedBlock);
        
        // Append decrypted block to result
        vector<unsigned char> blockData = matrixToVector(decryptedBlock);
        decryptedData.insert(decryptedData.end(), blockData.begin(), blockData.end());
    }
    
    // Remove padding
    return removePadding(decryptedData);
}


int main(int argc, char *argv[]){
    if (argc < 4) { 
        cerr << "Error: Not enough arguments!" << endl; 
        return 1; // Exit with error
    }
    
    string key, input, choice;
    key = argv[1];
    input = argv[2];
    choice = argv[3];

    Matrix encryptedMatrix(4, vector<unsigned char>(4));
    Matrix decryptedMatrix(4, vector<unsigned char>(4));

    Matrix keyMatrix = convertToHexMatrix(key);

    if (choice == "encrypt"){
        string cipherText = encryptAES(input, keyMatrix, s_box);
        cout<<cipherText;
    }
    else{
        string plainText = decryptAES(input, keyMatrix, s_box, inv_s_box);
        cout<<plainText;
    }
    return 0;
}