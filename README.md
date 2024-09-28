# Encrypto

## Overview

**Encrypto** is a simple encryption and decryption tool written in C++. It uses a custom algorithm to transform a file into an encrypted form and then decrypt it back to the original form. The tool is controlled via command line arguments or interactive prompts, making it flexible and easy to use.

## Features

- **Encrypt** a file using a key file.
- **Decrypt** an encrypted file back to its original form using the same key file.
- The encryption process uses a combination of bit manipulation and hex encoding.
- The key is processed into a numeric value which is then used for encryption and decryption.

## Project Structure

- `main.cpp`: Handles user interaction and file operations. Reads the key and text files, and calls the encryption or decryption functions.
- `encrypto.cpp`: Contains the core encryption and decryption logic.
- `encrypto.hpp`: Header file declaring functions used in `encrypto.cpp`.
- `Makefile`: Contains commands to compile, clean, and run the project. There is also a test command to verify functionality.

## Getting Started

### Prerequisites

- **C++ Compiler**: Make sure you have `clang++` installed, or update the `Makefile` to use your preferred compiler.
- **Make**: To use the provided `Makefile`, ensure `make` is installed on your system.

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/DrChrisHax/encrypto.git
   cd encrypto
   ```

2. **Build the project**:
   Run the following command to compile the project:
   ```bash
   make
   ```

3. **Run the project**:
   To run the program with the provided input files:
   ```bash
   ./encrypto
   ```
   **OR**
   To test the program run:
   ```
   make test
   ```
   and verify that plaintext.txt matches text.txt

### Usage

There are two ways to use Encrypto:

1. **Command Line Arguments**:
   ```bash
   ./encrypto <key_file_path> <text_file_path> <1 for encryption / 0 for decryption>
   ```
   - Example:
     ```bash
     ./encrypto key.txt text.txt 1
     ```

2. **Interactive Mode**:
   Simply run the program without any arguments:
   ```bash
   ./encrypto
   ```
   You will be prompted to select encryption or decryption and provide the file paths for the key and text files.

### Makefile Commands

- **Build the project**:
  ```bash
  make
  ```
- **Clean the project**:
  ```bash
  make clean
  ```
  This will remove the executable and any generated text files.
  
- **Run the project**:
  ```bash
  make run
  ```
  This will compile and run the project interactively.

- **Test the project**:
  ```bash
  make test
  ```
  This will compile and run the project with `key.txt` and `text.txt` as input files.

### Key and Text File Format

- The **key file** can be any file. The key can be multiline and will be processed into a 32-bit unsigned integer.
- The **text file** should be the file for encryption or decryption.

### Output

- **Encrypted Text**: The encrypted result is saved to `encrypted.txt`.
- **Decrypted Text**: The decrypted result is saved to `plaintext.txt`.

## Acknowledgments

Created by **Chris Manlove**.
