
# Huffman + XOR File Tool (C++)

Compresses files using Huffman coding and applies XOR encryption using a user-provided key.

## Features
- File-to-file processing
- Huffman encode/decode
- XOR encrypt/decrypt with user key
- Standard library only (`iostream`, `fstream`, `string`, etc.)

## Build & Run
```bash
g++ -std=c++17 -O2 -o huffxor src/huffman_xor_tool.cpp
./huffxor

```

## Project Structure
```
file-huffman-xor-tool/
├── src/ # Huffman + XOR implementation
├── test_files/ # Small sample input files
└── README.md

```

## Future Improvements
- Replace XOR with AES for real encryption
- Add a proper file header (store original size, tree metadata, checksums)
- Add corruption/integrity detection
- Add automated tests for encode/decode correctness
- Add performance benchmarking for larger files

