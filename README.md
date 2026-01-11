
# Huffman + XOR File Tool (C++)

Compresses files using Huffman coding and applies XOR encryption using a user-provided key.

## Features
- File-to-file processing
- Huffman encode/decode
- XOR encrypt/decrypt with user key
- Standard library only (`iostream`, `fstream`, `string`, etc.)

## Build & Run
```bash
g++ -std=c++17 -O2 -o huffxor src/main.cpp
./huffxor
