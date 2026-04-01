//This file implements the running key cipher encryption and decryption functions.
#include<string>
using namespace std;


//helper function to get cipher character by adding ascii values of plain character and key character
char get_cipher_char(char plain_char, char key_char) {
    return ((plain_char - 'a') + (key_char - 'a')) % 26 + 'a';
}

//function to encrypt the plaintext using the key
string encrypt(string plaintext, string key) {
    string cipher_text;
    string::iterator it1 , it2;

    for (it1 = plaintext.begin(), it2 = key.begin(); it1 != plaintext.end() && it2 != key.end(); ++it1, ++it2) {
        if (!isalpha(*it1)) {
            cipher_text += *it1;
        } 
        else {
            cipher_text += get_cipher_char(tolower(*it1), tolower(*it2));
        }
    }

    return cipher_text;
}

//helper function to get decrypted character by subtracting ascii value of key character from cipher character
char get_decrypted_char(char cipher_char, char key_char) {
    return ((cipher_char - 'a') - (key_char - 'a') + 26) % 26 + 'a';
}

//function to decrypt the cipher text using the key
string decrypt(string cipher_text, string key) {
    string decrypted_text;
    string::iterator it1 , it2;

    for (it1 = cipher_text.begin(), it2 = key.begin(); it1 != cipher_text.end() && it2 != key.end(); ++it1, ++it2) {
        if (!isalpha(*it1)) {
            decrypted_text += *it1;
        } 
        else {
            decrypted_text += get_decrypted_char(tolower(*it1), tolower(*it2));
        }
    }

    return decrypted_text;
}