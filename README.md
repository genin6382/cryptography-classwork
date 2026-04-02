# Running Key Cipher + Rolling Polynomial Hash

Implementation of the Running Key Cipher with a custom Rolling Polynomial Hash for integrity verification (Encrypt-then-MAC).

Name: Vidhu.P
Roll no: 23011102115
Class: IoT-B

---

## Theory

### Running Key Cipher
Similar to the Vigenère cipher, but instead of a short repeating key, it uses a key that is at least as long as the plaintext (classically a passage from a book). Each plaintext character is shifted by the corresponding key character:

```
Encrypt: C = (P + K) mod 26
Decrypt: P = (C - K + 26) mod 26
```

### Rolling Polynomial Hash
A window of size 7 slides across the ciphertext. For each window position, a polynomial hash is computed:

```
H = s[0]*BASE^6 + s[1]*BASE^5 + ... + s[6]*BASE^0  (mod 1e9+7)
```

All window hashes are XOR-folded into a single 64-bit value and returned as a 16-char hex string.

**Why this over SHA?** SHA is a black box for this context. The rolling polynomial hash is built from scratch, the math is transparent, and it demonstrates the core idea of hashing  without any library. It's suited for integrity checking in non-adversarial settings.

---

## Flow

```
plaintext ──► encrypt ──► ciphertext ──► hash ──► tag
                              │                     │
                              └──► verify ──► decrypt ──► plaintext
```

This is the **Encrypt-then-MAC** pattern — the hash acts as a tamper-evident seal on the ciphertext. Decryption only happens if the tag matches.

---

## How to Run

**Using the run script :**
```bash
chmod +x run.sh
./run.sh "<plaintext>" "<key>"
```

**Or manually:**
```bash
g++ -o main main.cpp
./main
# then enter input
```

> Key must be at least as long as the plaintext. Spaces in the key are ignored automatically.

---

## Worked Examples

### Example 1
```
Plaintext : QUANTUM COMPUTING BREAKS CLASSICAL ENCRYPTION
Key       : THEQUICKBROWNFOXJUMPSOVERTHELAZYDOGANDKEEPSRUNNINGFOREVER
Cipher Text : jbednco dfalhywkp ngwofw vsedshadz eafbctiafh
Hash Tag    : 000000002ec9eb81
Decrypted   : quantum computing breaks classical encryption
```

### Example 2
```
Plaintext  : CRYPTOGRAPHY
Key        : THEQUICKBROWNFOXJUMPS
Cipher Text: <run to see output>
Hash Tag   : <run to see output>
Decrypted  : cryptography
```

---

## Files

| File | Description |
|---|---|
| `main.cpp` | Entry point — orchestrates encrypt → hash → verify → decrypt |
| `running_key_cipher.h` | Encrypt and decrypt functions |
| `custom_hash.h` | Rolling polynomial hash — compute and verify |
| `run.sh` | Shell script to pass inputs as command line arguments |