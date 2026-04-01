#include<string> //for strings
#include<iostream> //for input and output
#include<algorithm> // for erase and remove functions

#include "running_key_cipher.h" // custom header file for encryption and decryption functions ( present in running_key_cipher.h)
using namespace std;

int main(){
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

    string cipher_text = encrypt(plain_text, key);
    cout << "Cipher Text: " << cipher_text << endl;
    string decrypted_text = decrypt(cipher_text, key);
    cout << "Decrypted Text: " << decrypted_text << endl;

    return 0;
}