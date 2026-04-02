#include <iostream>  // for input and output
#include <algorithm> // for erase and remove functions

#include "running_key_cipher.h" // custom header file for encryption and decryption functions
#include "custom_hash.h"        // custom header file for that implements polynomial rolling hash function

using namespace std;

int main() {
    string plain_text, key;

    cout << "Enter the plaintext: ";
    getline(cin, plain_text);

    cout << "Enter the key: ";
    getline(cin, key);

    // remove spaces from key
    key.erase(remove(key.begin(), key.end(), ' '), key.end());

    if (plain_text.length() > key.length()) {
        cout << "ERROR: The key must be at least as long as the plaintext." << endl;
        return 1;
    }

    // Encrypt
    string cipher_text = encrypt(plain_text, key);
    cout << "\nCipher Text : " << cipher_text << endl;

    // Hash the ciphertext 
    string hash = compute_hash(cipher_text);
    cout << "Hash Tag    : " << hash << endl;

    // Verify before decrypting
    if (!verify_hash(cipher_text, hash)) {
        cout << "\nERROR: Integrity check failed. Message may have been tampered!" << endl;
        return 1;
    }

    // Decrypt 
    string decrypted_text = decrypt(cipher_text, key);
    cout << "Decrypted   : " << decrypted_text << endl;

    return 0;
}