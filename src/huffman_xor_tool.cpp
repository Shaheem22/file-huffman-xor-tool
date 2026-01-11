#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BinaryTree {
public:
    char value;         
    int freq;          
    BinaryTree* left;   
    BinaryTree* right;  

    BinaryTree(char val, int f) {
        value = val;
        freq = f;
        left = nullptr;
        right = nullptr;
    }

    ~BinaryTree() {
        delete left;
        delete right;
    }
};

void custom_swap(BinaryTree*& a, BinaryTree*& b) {
    BinaryTree* temp = a;
    a = b;
    b = temp;
}

class MinHeap {
private:
    BinaryTree** heap; 
    int capacity;      
    int size;          

    void resize() {
        capacity *= 2;
        BinaryTree** newHeap = new BinaryTree*[capacity];
        for (int i = 0; i < size; ++i)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
    }

    void heapifyDown(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left]->freq < heap[smallest]->freq)
            smallest = left;

        if (right < size && heap[right]->freq < heap[smallest]->freq)
            smallest = right;

        if (smallest != idx) {
            custom_swap(heap[idx], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int idx) {
        if (idx && heap[idx]->freq < heap[(idx - 1) / 2]->freq) {
            custom_swap(heap[idx], heap[(idx - 1) / 2]);
            heapifyUp((idx - 1) / 2);
        }
    }

public:
    MinHeap() : capacity(10), size(0) {
        heap = new BinaryTree*[capacity];
    }

    ~MinHeap() {
        for (int i = 0; i < size; ++i) {
            delete heap[i];
        }
        delete[] heap;
    }

    void push(BinaryTree* node) {
        if (size == capacity)
            resize();
        heap[size] = node;
        heapifyUp(size++);
    }

    BinaryTree* pop() {
        if (size == 0)
            return nullptr;
        BinaryTree* root = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return root;
    }

    int getSize() const {
        return size;
    }
};

class HuffmanCode {
private:
    string path;           
    MinHeap heap;
    int freq[256] = {0};    
    string codes[256];   
    BinaryTree* root;   

    void __frequency_from_text(const string& text) {
        for (char c : text) {
            freq[static_cast<unsigned char>(c)]++;
        }
    }

    void __Build_heap() {
        for (int i = 0; i < 256; ++i) {
            if (freq[i] > 0) {
                heap.push(new BinaryTree(i, freq[i]));
            }
        }
    }

    void __Build_Binary_Tree() {
        while (heap.getSize() > 1) {
            BinaryTree* left = heap.pop();
            BinaryTree* right = heap.pop();

            int combined_freq = left->freq + right->freq;
            BinaryTree* new_node = new BinaryTree('\0', combined_freq);
            new_node->left = left;
            new_node->right = right;

            heap.push(new_node);
        }
        root = heap.pop();
    }

    void __Build_Binary_Code_Helper(BinaryTree* root, string curr_bits) {
        if (!root)
            return;

        if (root->value != '\0') {
            codes[static_cast<unsigned char>(root->value)] = curr_bits;
            return;
        }

        __Build_Binary_Code_Helper(root->left, curr_bits + "0");
        __Build_Binary_Code_Helper(root->right, curr_bits + "1");
    }

    void __Build_Binary_Code() {
        __Build_Binary_Code_Helper(root, "");
    }

    string __Build_encoded_text(const string& text) {
        string encoded_text;
        for (char c : text)
            encoded_text += codes[static_cast<unsigned char>(c)];
        return encoded_text;
    }

    void __write_to_file(const string& output_path, const string& encoded_text) {
        ofstream outfile(output_path, ios::binary);
        if (!outfile.is_open()) {
            cerr << "Failed to open output file." << endl;
            return;
        }

        string buffer;
        for (char bit : encoded_text) {
            buffer += bit;
            if (buffer.size() == 8) {
                char byte = 0;
                for (int i = 0; i < 8; ++i) {
                    if (buffer[i] == '1')
                        byte |= (1 << (7 - i));
                }
                outfile.put(byte);
                buffer.clear();
            }
        }

        if (!buffer.empty()) {
            char byte = 0;
            for (size_t i = 0; i < buffer.size(); ++i) {
                if (buffer[i] == '1')
                    byte |= (1 << (7 - i));
            }
            outfile.put(byte);
        }

        outfile.close();
    }

    string __read_from_file(const string& input_path) {
        ifstream infile(input_path, ios::binary);
        if (!infile.is_open()) {
            cerr << "Failed to open input file." << endl;
            return "";
        }

        string encoded_text;
        char byte;
        while (infile.get(byte)) {
            for (int i = 7; i >= 0; --i) {
                encoded_text += ((byte >> i) & 1) ? '1' : '0';
            }
        }

        infile.close();
        return encoded_text;
    }

    string __Decoded_text(const string& encoded_text) {
        if (!root) {
            cerr << "Error: Huffman tree not built." << endl;
            return "";
        }

        BinaryTree* current = root;
        string decoded_text;

        for (char bit : encoded_text) {
            if (bit == '0')
                current = current->left;
            else
                current = current->right;

            if (!current) {
                cerr << "Error: Decoding encountered null pointer." << endl;
                return "";
            }

            if (current->left == nullptr && current->right == nullptr) {
                decoded_text += current->value;
                current = root;
            }
        }

        return decoded_text;
    }

    void xorFile(const string& inputPath, const string& outputPath, const string& key) {
        ifstream inFile(inputPath, ios::binary);
        ofstream outFile(outputPath, ios::binary);

        if (!inFile.is_open() || !outFile.is_open()) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }

        size_t keyLength = key.size();
        char byte;
        size_t keyIndex = 0;

        while (inFile.get(byte)) {
            byte ^= key[keyIndex];
            outFile.put(byte);
            keyIndex = (keyIndex + 1) % keyLength;
        }

        inFile.close();
        outFile.close();

        cout << "XOR operation completed. Output written to: " << outputPath << endl;
    }

public:
    HuffmanCode(const string& p) : path(p), root(nullptr) {}

    ~HuffmanCode() {
        delete root;
    }

    void compression(const string& output_path) {
        ifstream file(path);
        string text((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()))
;
        __frequency_from_text(text);
        __Build_heap();
        __Build_Binary_Tree();
        __Build_Binary_Code();

        string encoded_text = __Build_encoded_text(text);
        __write_to_file(output_path, encoded_text);

        cout << "Compression done. Output written to: " << output_path << endl;
    }

    void decompression(const string& input_path, const string& output_path) {
        string encoded_text = __read_from_file(input_path);
        string decoded_text = __Decoded_text(encoded_text);

        ofstream outfile(output_path);
        if (!outfile.is_open()) {
            cerr << "Failed to open output file." << endl;
            return;
        }

        outfile << decoded_text;
        outfile.close();

        cout << "Decompression done. Output written to: " << output_path << endl;
    }

    void xorEncryption(const string& inputFile, const string& outputFile, const string& key) {
        xorFile(inputFile, outputFile, key);
    }
};

int main() {
    string input_path, compressed_path, decompressed_path, xor_encrypted_path, xor_decrypted_path;
    string xor_key;

    cout << "Enter Path to the file to be compressed: ";
    getline(cin, input_path);

    cout << "Enter Path for compressed file: ";
    getline(cin, compressed_path);

    cout << "Enter Path for decompressed file: ";
    getline(cin, decompressed_path);

    cout << "Enter Path for XOR-encrypted file: ";
    getline(cin, xor_encrypted_path);

    cout << "Enter Path for XOR-decrypted file: ";
    getline(cin, xor_decrypted_path);

    cout << "Enter XOR key: ";
    getline(cin, xor_key);

    HuffmanCode h(input_path);
    h.compression(compressed_path);
    h.decompression(xor_decrypted_path, decompressed_path);

    h.xorEncryption(compressed_path, xor_encrypted_path, xor_key);
    h.xorEncryption(xor_encrypted_path, xor_decrypted_path, xor_key);

    return 0;
}

