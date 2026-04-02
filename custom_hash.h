// This file implements a custom polynomial rolling hash 
#ifndef CUSTOM_HASH_H
#define CUSTOM_HASH_H

#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>

using namespace std;

// base and mod values for the polynomial hash
#define BASE 131
#define MOD  1000000007

// converts the hash number to a hex string
string to_hex(uint64_t val) {
    stringstream ss;
    ss << hex << setfill('0') << setw(16) << val;
    return ss.str();
}

// rolling polynomial hash function
// slides a window of size 7 over the string
// for each window: H = s[0]*BASE^6 + s[1]*BASE^5 + ... + s[6]*BASE^0  (mod MOD)
// all window hashes are XOR-ed together to get the final hash
uint64_t rolling_hash_window(const string& s) {
    int n = s.length();
    int w = 7; // window size

    if (n == 0) return 0;

    // if string is shorter than window, just hash the whole string
    if (n < w) w = n;

    // precompute BASE^(w-1) % MOD  —  needed to remove leftmost char while sliding
    uint64_t lead = 1;
    for (int i = 0; i < w - 1; i++) {
        lead = (lead * BASE) % MOD;
    }

    // compute hash of first window
    uint64_t h = 0;
    for (int i = 0; i < w; i++) {
        h = (h * BASE + (unsigned char)s[i]) % MOD;
    }

    uint64_t combined = h; // start XOR accumulation

    // slide the window across the rest of the string
    for (int i = w; i < n; i++) {
        // remove leftmost character of previous window
        h = (h + MOD - (unsigned char)s[i - w] * lead % MOD) % MOD;
        // add new rightmost character
        h = (h * BASE + (unsigned char)s[i]) % MOD;

        combined ^= h; // XOR fold
    }

    return combined;
}

// returns a 16 character hex string hash of the input
string compute_hash(const string& input) {
    uint64_t h = rolling_hash_window(input);
    return to_hex(h);
}

// checks if the hash of ciphertext matches the given tag
// used in Encrypt-then-MAC to detect tampering before decrypting
bool verify_hash(const string& ciphertext, const string& tag) {
    return compute_hash(ciphertext) == tag;
}

#endif