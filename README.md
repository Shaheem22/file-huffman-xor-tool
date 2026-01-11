
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
## Usage
Run the program:
```
./huffxor
```
You will be prompted to provide file paths for each stage of the compression and encryption pipeline:

1. Input file  
Path to the original file you want to compress.

2. Compressed file  
Path where the Huffman-compressed file will be saved.

3. Decompressed file  
Path where the decompressed (restored) file will be written.

4. XOR-encrypted file  
Path where the encrypted compressed file will be stored.

5. XOR-decrypted file  
Path where the decrypted compressed file will be saved before decompression.

6. XOR key  
A user-provided key used for XOR encryption and decryption.

### Example
```
./huffxor
Enter Path to the file to be compressed: test_files/sample.txt
Enter Path for compressed file: compressed.bin
Enter Path for decompressed file: restored.txt
Enter Path for XOR-encrypted file: encrypted.bin
Enter Path for XOR-decrypted file: decrypted.bin
Enter XOR key: mysecret
```
This will compress the input file, encrypt it, decrypt it, and restore the original file using the same XOR key.

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

