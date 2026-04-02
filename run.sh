#!/bin/bash

plaintext="$1"
key="$2"

g++ main.cpp -o cipher_app

if [ $? -eq 0 ]; then
    ./cipher_app << EOF
$plaintext
$key
EOF
fi